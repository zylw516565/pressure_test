#include "TCU.h"

#include "DCMPacketHead.h"
#include "APPCommon.h"
#include <muduo/base/Logging.h>
#include <common/ConfigFile.h>
#include <utils/PB2JSONHelper.h>
#include "zna_protocol_message.pb.h"
#include <base/SSLClient.h>

#include <sys/time.h>

#include <iostream>

using namespace muduo;
using namespace muduo::net;

using namespace std::placeholders;

bool TCU::isRunning_ = false;           //运行标志
bool TCU::isExit_    = false;           //退出标志
BlockingQueue<std::string> TCU::queue_;

TCU::TCU(EventLoop* loop, const InetAddress& serverAddr)
    :loop_(loop),
    tcpClient_(nullptr),
    tcpConn_(nullptr),
    sslClient_(nullptr),
    sslConn_(nullptr),
    spCodec_(nullptr),
    timeout_(0),
    totalPressureTime_(0),
    pressureStartTime_(0),
    loginData_(""),
    vehData_(""),
    heartBeatReq_(""),
    totalReqCount_(0),
    totalRspCount_(0),
    sessionId_(0),
    serverAddr_(serverAddr),
    spConsoleThread_(nullptr),
    spBackendThread_(nullptr)
{
}

TCU::~TCU()
{
    // uninit();
}

bool TCU::init(const ConfigParam& stParam)
{
    timeout_ = stParam.timeout;
    totalPressureTime_ = stParam.totalPressureTime;
    LOG_INFO << "timeout_(" << timeout_ << ") "
             << "totalPressureTime_(" << totalPressureTime_.load() << ")";

    //启动超时检测处理
    loop_->runAfter(stParam.timeout, std::bind(&TCU::handleTimeout, this));

    //构造测试数据
    makeDataByCmdType();

    //添加OpenSSL认证支持 ///
    if(ConfigFile::instance().isUseSSL()) {
      LOG_INFO << "Use SSL !!!";
      SSLContext context{
        ConfigFile::instance().getCACert(),
        ConfigFile::instance().getPrivateKey(),
        ConfigFile::instance().getCertFile(),
      };

      sslClient_.reset(new SSLClient(loop_, serverAddr_, "TCU", context));
      sslClient_->setConnectionCallback(std::bind(&TCU::onSSLConnection, this, _1));
      sslClient_->setMessageCallback(std::bind(&TCU::onSSLMessage, this, _1, _2, _3));
      sslClient_->enableRetry();
      sslClient_->connect();
    } else {
      LOG_INFO << "Not use SSL !!!";
      tcpClient_.reset(new TcpClient(loop_, serverAddr_, "TCU"));
      tcpClient_->setConnectionCallback(std::bind(&TCU::onConnected, this, _1));
      tcpClient_->enableRetry();
      tcpClient_->connect();
    }

    if(!ConfigFile::instance().isPressureMode())
    {
        spConsoleThread_.reset(new std::thread(consoleThreadProc));
        spBackendThread_.reset(new std::thread(std::bind(&TCU::backendThreadProc, this)));
    }
    return true;
}

void TCU::uninit()
{
    isExit_ = true;

    if(spConsoleThread_){
        if (spConsoleThread_->joinable())
            spConsoleThread_->join();
    }

    if(spBackendThread_){
        if (spBackendThread_->joinable())
            spBackendThread_->join();
    }

    quit();
}

void TCU::onConnected(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
      tcpConn_ = conn;
        LOG_INFO << "client connected: " << conn->peerAddress().toIpPort().c_str();
        ++sessionId_;
        conn->setTcpNoDelay(true);

        spCodec_.reset(new TCUCodec(conn,
                                         sessionId_,
                                         std::bind(&TCU::onMessage, this, _1, _2, _3, _4)));

        conn->setMessageCallback(std::bind(&TCUCodec::onMessage, spCodec_.get(), _1, _2, _3));
        LOG_INFO << "Send login data:(" << loginData_.c_str() << ")";
        conn->send(loginData_);
    }
    else
    {
      tcpConn_.reset();
      onDisconnect(conn);
    }
}

void TCU::onMessage(const TcpConnectionPtr& conn,
                          const LYDCMMsgHeadPtr& spPacketHead,
                          const std::string& msgBody,
                          Timestamp receiveTime)
{
    if (nullptr == conn){
        LOG_ERROR << "onMessage failed !!! nullptr == conn";
        return;
    }

    if (nullptr == spPacketHead){
        LOG_ERROR << "onMessage failed !!! nullptr == spPacketHead";
        return;
    }
    
    if (msgBody.empty()){
        LOG_ERROR << "onMessage failed !!! msgBody is empty";
        return;
    }

    //TCU登录响应
    if (LY_DCM_MSG_SERVER_LOGIN_RSP == spPacketHead->m_uMsgID
        || LY_DCM_MSG_SERVER_NISSAN_LOGIN_RSP == spPacketHead->m_uMsgID
        || LY_DCM_MSG_SERVER_NISSAN_RSA_LOGIN_RSP == spPacketHead->m_uMsgID)
    {
        zna::protocol::LoginRsp objLoginRsp;
        if (!objLoginRsp.ParseFromString(msgBody))
        {
            LOG_ERROR << "LoginRsp::ParseFromString failed!!!";
            return;
        }

        if (objLoginRsp.has_errcode()
            && objLoginRsp.has_time_stamp())
        {
            if (0 == objLoginRsp.errcode())
            {
                LOG_INFO << "Login success !!! errcode(" << objLoginRsp.errcode() << ") "
                         << "time_stamp(" << objLoginRsp.time_stamp() << ")";

                if(ConfigFile::instance().isPressureMode())
                {
                    LOG_INFO << "PressureMode: Please wait !!! Pressure Testing......";
                    //利用写完成回调,不断发送整车数据
                    // conn->setWriteCompleteCallback(std::bind(&TCU::autoSendVehData, this, conn));

                    autoSendVehData(conn);
                    //记录压测开始时间
                    pressureStartTime_.store(Timestamp::now().microSecondsSinceEpoch());
                    //保持心跳
                    loop_->runEvery(3, std::bind(&TCU::sendHeartBeatOnTcp, this, conn));
                    //运行指定时长然后退出
                    loop_->runAfter(totalPressureTime_.load(), std::bind(&TCU::quit, this));
                }
                else
                {
                    LOG_INFO << "ManualMode: Please send data manually !";
                }
            }
            else
            {
                LOG_ERROR << "Login failed !!! errcode(" << objLoginRsp.errcode() << ") "
                          << "time_stamp(" << objLoginRsp.time_stamp() << ")";
                return;
            }
        }
    }
    //整车数据响应包
    else if (LY_DCM_MSG_SERVER_NISSAN_DATA_RSP_NEW == spPacketHead->m_uMsgID)
    {
        zna::protocol::Vehicle_InfoRsp vehInfoRsp;
        if (!vehInfoRsp.ParseFromString(msgBody))
        {
            LOG_ERROR << "Vehicle_InfoRsp::ParseFromString failed!!!";
            return;
        }

        if (vehInfoRsp.has_errcode()
            && vehInfoRsp.has_time_stamp())
        {
            if (0 == vehInfoRsp.errcode())
            {
                totalRspCount_++;

                autoSendVehData(conn);
                LOG_DEBUG << "vehInfoRsp success !!! errcode(" << vehInfoRsp.errcode() << ") "
                         << "time_stamp(" << vehInfoRsp.time_stamp() << ") "
                         << "totalRspCount(" << totalRspCount_.load() << ")";
            }
            else
            {
                LOG_ERROR << "vehInfoRsp failed !!! errcode(" << vehInfoRsp.errcode() << ") "
                          << "time_stamp(" << vehInfoRsp.time_stamp() << ") "
                          << "totalRspCount(" << totalRspCount_.load() << ")";
                return;
            }
        }
    }
}

void TCU::onSSLConnection(const SSLConnectionPtr& conn)
{
  sslConn_ = conn;
  LOG_INFO << "Send login data:(" << loginData_.c_str() << ")";
  sslConn_->send(loginData_.data(), loginData_.length());
}

void TCU::onSSLMessage(const SSLConnectionPtr& conn, Buffer* buf, Timestamp time)
{
  LOG_DEBUG << "onSSLMessage recv data: " << buf->peek()
            << " readableBytes(" << buf->readableBytes() << ")";

  while (buf->readableBytes() > 0)
  {
      // 一般长度65535以内，加个9，以便以后扩展,某些
      if (buf->readableBytes() == 0 || buf->readableBytes() > 965535)
      {
          LOG_ERROR << "Invalid len (" << buf->readableBytes() << ")";
          return;
      }

      if (buf->readableBytes() < 2)
      {
          LOG_ERROR << "Invalid len (" << buf->readableBytes() << ")";
          return;
      }

      if ((LY_PACKET_PRE_FLAG_1 != buf->peek()[0])
          || (LY_PACKET_PRE_FLAG_2 != buf->peek()[1])
          )
      {
          LOG_ERROR << "Is not LYDCMPacket!!! (" << buf->peek()[0] << ") "
                    << "(" << buf->peek()[1] << ")";
          return;
      }

      if (buf->readableBytes() < 4)
      {
          LOG_ERROR << "Invalid msg; no packetLen field. len:" << buf->readableBytes();
          return;
      }

      //消息不完整,继续收包.
      unsigned short packetLen = *(unsigned short*)(buf->peek() + LY_PACKET_PRE_FLAG_LEN);
      if (buf->readableBytes() < packetLen)
      {
          LOG_ERROR << "Incomplete packet, recvLen(" << buf->readableBytes() << ") "
                    << "requireLen(" << packetLen << ")";
          return;
      }

      if (packetLen < LY_PACKET_HEAD_LEN + LY_PACKET_CRC_LEN + LY_PACKET_END_FLAG_LEN)
      {
          LOG_ERROR << "Invalid msg; recvLen(" << packetLen << ") "
          << "< minRequireLen(" << (LY_PACKET_HEAD_LEN + LY_PACKET_CRC_LEN + LY_PACKET_END_FLAG_LEN) << ")";
          return;
      }

      // CRC16校验消息
      unsigned short uCalcCrc16 = UtilGenCRC16(buf->peek(), (packetLen - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN));
      unsigned short uReqCrc16 = *(unsigned short*)(buf->peek() + packetLen - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN);
      if (uCalcCrc16 != uReqCrc16)
      {
          LOG_ERROR << "Crc16 is error(" << uCalcCrc16 << " " << uReqCrc16 << ")";
          return;
      }

      // 解析消息包头
      LYDCMMsgHeadPtr  spPacketHead(new LYDCMMsgHead);
      DeCodeLYDCMMsgHead(buf->peek(), (*spPacketHead.get()));

      //取包体
      string msgBody;
      int bodyLen = packetLen - LY_PACKET_HEAD_LEN - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN;
      msgBody.assign((buf->peek() + LY_PACKET_HEAD_LEN), bodyLen);

      do {
        if (nullptr == conn){
            LOG_ERROR << "onMessage failed !!! nullptr == conn";
            break;
        }

        if (nullptr == spPacketHead){
            LOG_ERROR << "onMessage failed !!! nullptr == spPacketHead";
            break;
        }
        
        if (msgBody.empty()){
            LOG_ERROR << "onMessage failed !!! msgBody is empty";
            break;
        }

        char szMsgId[32];
        snprintf(szMsgId,  sizeof szMsgId, "0x%X", spPacketHead->m_uMsgID);
        LOG_DEBUG << "MsgID(" << string(szMsgId) << ")";
        //TCU登录响应
        if (LY_DCM_MSG_SERVER_LOGIN_RSP == spPacketHead->m_uMsgID
            || LY_DCM_MSG_SERVER_NISSAN_LOGIN_RSP == spPacketHead->m_uMsgID
            || LY_DCM_MSG_SERVER_NISSAN_RSA_LOGIN_RSP == spPacketHead->m_uMsgID)
        {
          zna::protocol::LoginRsp objLoginRsp;
          if (!objLoginRsp.ParseFromString(msgBody))
          {
              LOG_ERROR << "LoginRsp::ParseFromString failed!!!";
              break;
          }

          if (objLoginRsp.has_errcode()
              && objLoginRsp.has_time_stamp())
          {
              if (0 == objLoginRsp.errcode())
              {
                  LOG_INFO << "Login success !!! errcode(" << objLoginRsp.errcode() << ") "
                          << "time_stamp(" << objLoginRsp.time_stamp() << ")";

                  if(ConfigFile::instance().isPressureMode())
                  {
                      LOG_INFO << "PressureMode: Please wait !!! Pressure Testing......";
                      //利用写完成回调,不断发送整车数据
                      // conn->setWriteCompleteCallback(std::bind(&TCU::autoSendVehData, this, conn));

                      //记录压测开始时间
                      pressureStartTime_.store(Timestamp::now().microSecondsSinceEpoch());
                      //保持心跳
                      loop_->runEvery(3, std::bind(&TCU::sendHeartBeatOnSsl, this, conn));
                      //运行指定时长然后退出
                      loop_->runAfter(totalPressureTime_.load(), std::bind(&TCU::quit, this));
                  }
                  else
                  {
                      LOG_INFO << "ManualMode: Please send data manually !";
                  }
              }
              else
              {
                  LOG_ERROR << "Login failed !!! errcode(" << objLoginRsp.errcode() << ") "
                            << "time_stamp(" << objLoginRsp.time_stamp() << ")";
                  break;
              }
          }
        }
        //心跳响应
        else if (LY_DCM_MSG_SERVER_NISSAN_HEARTBEAT_RSP == spPacketHead->m_uMsgID) {
          zna::protocol::HeartbeatRsp heartbeatRsp;
          if (!heartbeatRsp.ParseFromString(msgBody))
          {
              LOG_ERROR << "HeartbeatRsp::ParseFromString failed!!!";
              break;
          }

          if(heartbeatRsp.has_errcode()
             && heartbeatRsp.has_time_stamp()) {
            if(0 == heartbeatRsp.errcode()) {
                LOG_DEBUG << "HeartbeatRsp success !!! errcode(" << heartbeatRsp.errcode() << ") "
                          << "time_stamp(" << heartbeatRsp.time_stamp() << ") ";
            } else {
                LOG_ERROR << "HeartbeatRsp failed !!! errcode(" << heartbeatRsp.errcode() << ") "
                          << "time_stamp(" << heartbeatRsp.time_stamp() << ") ";
                          break;
            }
          }
        }
        //整车数据响应包
        else if (LY_DCM_MSG_SERVER_NISSAN_DATA_RSP_NEW == spPacketHead->m_uMsgID)
        {
          zna::protocol::Vehicle_InfoRsp vehInfoRsp;
          if (!vehInfoRsp.ParseFromString(msgBody))
          {
              LOG_ERROR << "Vehicle_InfoRsp::ParseFromString failed!!!";
              break;
          }

          if (vehInfoRsp.has_errcode()
              && vehInfoRsp.has_time_stamp())
          {
              if (0 == vehInfoRsp.errcode())
              {
                  totalRspCount_++;

                  LOG_DEBUG << "vehInfoRsp success !!! errcode(" << vehInfoRsp.errcode() << ") "
                          << "time_stamp(" << vehInfoRsp.time_stamp() << ") "
                          << "totalRspCount(" << totalRspCount_.load() << ")";
              }
              else
              {
                  LOG_ERROR << "vehInfoRsp failed !!! errcode(" << vehInfoRsp.errcode() << ") "
                            << "time_stamp(" << vehInfoRsp.time_stamp() << ") "
                            << "totalRspCount(" << totalRspCount_.load() << ")";
                  break;
              }
          }
        }
      }while(0);

      buf->retrieve(packetLen);
  };
}

void TCU::onDisconnect(const TcpConnectionPtr& conn)
{
  LOG_WARN << conn->localAddress().toIpPort() << "<--->" << conn->peerAddress().toIpPort() << ": disconnected";

  #if 1
  int64_t totalBytesRead = 0;
  int64_t totalMessagesRead = 0;
  LOG_WARN << totalBytesRead << " total bytes read";
  LOG_WARN << totalMessagesRead << " total messages read";
  LOG_WARN << (static_cast<double>(totalBytesRead) / static_cast<double>(totalMessagesRead)) << " average message size";
  LOG_WARN << (static_cast<double>(totalBytesRead) / (timeout_ * 1024 * 1024)) << " MiB/s throughput";
  #endif
}

void TCU::quit()
{
    handleTimeout();

    totalPressureTime_ = Timestamp::now().microSecondsSinceEpoch() - pressureStartTime_;
    LOG_INFO << "TotalReqCount(" << totalReqCount_.load() << ") "
             << "TotalRspCount(" << totalRspCount_.load() << ") "
             << "QPS(" << (totalReqCount_.load() * 1e6) / (totalPressureTime_.load()) << ") "
             << "totalPressureTime_(" << static_cast<double>(totalPressureTime_.load() / 1e6) << " s)";

    loop_->queueInLoop(std::bind(&EventLoop::quit, loop_));
}

void TCU::handleTimeout()
{
  if(ConfigFile::instance().isUseSSL()) {
    if(!sslClient_->sslConnection()) {
      LOG_WARN << sslClient_->name().c_str() << " is timeout, stop it !!!";
      sslClient_->stop();
    }
  } else {
    if(!tcpClient_->connection()) {
      LOG_WARN << tcpClient_->name().c_str() << " is timeout, stop it !!!";
      tcpClient_->stop();
    } else {
      if(!tcpClient_->connection()->connected()) {
        LOG_WARN << tcpClient_->name().c_str() << " is timeout, stop it !!!";
        tcpClient_->stop();
      }
    }
  }
}

void TCU::doLogin()
{
    LOG_INFO << "Send login data:(" << loginData_.c_str() << ")";
    if(ConfigFile::instance().isUseSSL()) {
      if(sslConn_)
        sslConn_->send(loginData_.data(), loginData_.length());
    } else {
      if(tcpConn_)
        tcpConn_->send(loginData_);
    }
}

void TCU::autoSendVehData(const muduo::net::TcpConnectionPtr& conn)
{
    totalReqCount_++;
    makeZNAVehicleData();
    if(conn) {
      conn->send(vehData_);
    }
}

void TCU::sendVehData()
{
    totalReqCount_++;
    makeZNAVehicleData();

    LOG_INFO << "sendVehData data:" << vehData_.c_str();
    if(ConfigFile::instance().isUseSSL()) {
      if(sslConn_)
        sslConn_->send(vehData_.data(), vehData_.length());
    } else {
      if(tcpConn_)
        tcpConn_->send(vehData_);
    }
}

void TCU::sendVehDataManually()
{
    ConfigFile::instance().init();
    sendVehData();
}

void TCU::makeDataByCmdType()
{
    makeZNALoginReq();
    makeZNAVehicleData();
}

void TCU::makeZNALoginReq()
{
    zna::protocol::LoginReq objLoginReq;

    string strLoginReq = ConfigFile::instance().getLoginJson();
    PB2JSONHelper::JsonString2Message(strLoginReq, objLoginReq);

    //更新时间戳
    struct timeval tv;
    gettimeofday(&tv, NULL);
    objLoginReq.set_time_stamp(static_cast<unsigned int>(tv.tv_sec));

    string strPBBody;
    if (!objLoginReq.SerializeToString(&strPBBody))
    {
        LOG_ERROR << "LoginReq SerializeToString failed !!!";
        return;
    }

    LYDCMMsgHead stPacketReq;
    stPacketReq.m_uPacketLen = LY_PACKET_HEAD_LEN + LY_PACKET_TAIL_LEN - LY_PACKET_TIME_LEN + strPBBody.size();
    stPacketReq.m_uMsgID = LY_DCM_MSG_NISSAN_TBOX_LOGIN_REQ;
    stPacketReq.m_cSecretFlag = ENCRYPT_FLAG_NO_ENCRYPT;
    stPacketReq.m_uVersion = VERSION_NISSANTBOX_NUMBER_01; //TODO:确认version值是多少,从配置中读取version.

    string msgBody;
    if (static_cast<int>(msgBody.capacity()) < stPacketReq.m_uPacketLen)
    {
        msgBody.resize(stPacketReq.m_uPacketLen);
    }

    EnCodeLYDCMMsgHead(stPacketReq, (char*)msgBody.data());       // 编码消息头
    memcpy((char*)msgBody.data() + LY_PACKET_HEAD_LEN, strPBBody.c_str(), strPBBody.size());
    appendTail((char*)msgBody.data(), stPacketReq.m_uPacketLen);  // 添加消息尾部

    //string内容正确但length不对，恢复一下其length
    loginData_.append(msgBody.c_str(), stPacketReq.m_uPacketLen);
    return;
}

void TCU::makeZNAVehicleData()
{
    zna::protocol::Vehicle_Info objVehicleInfo;
    string strJson = ConfigFile::instance().getJsonConfig();
    PB2JSONHelper::JsonString2Message(strJson, objVehicleInfo);

    //压测工具每次发请求自动更新采集时间,单位:毫秒
    objVehicleInfo.set_collect_time(static_cast<google::protobuf::uint32>(Timestamp::now().microSecondsSinceEpoch()/1000));
    LOG_DEBUG << "Vehicle_Info collect_time(" << objVehicleInfo.collect_time() << ")";

    string strPBBody;
    if (!objVehicleInfo.SerializeToString(&strPBBody))
    {
        LOG_ERROR << "Vehicle_Info SerializeToString failed !!!";
        return;
    }

    LYDCMMsgHead stPacketReq;
    stPacketReq.m_uPacketLen = LY_PACKET_HEAD_LEN + LY_PACKET_TAIL_LEN - LY_PACKET_TIME_LEN + strPBBody.size();
    stPacketReq.m_uMsgID = LY_DCM_MSG_NISSAN_TBOX_DATA_NEW;
    stPacketReq.m_cSecretFlag = ENCRYPT_FLAG_NO_ENCRYPT;
    stPacketReq.m_uVersion = VERSION_NISSANTBOX_NUMBER_10; //TODO:确认version值是多少,从配置中读取version.

    string msgBody;
    if (static_cast<int>(msgBody.capacity()) < stPacketReq.m_uPacketLen)
    {
        msgBody.resize(stPacketReq.m_uPacketLen);
    }

    EnCodeLYDCMMsgHead(stPacketReq, (char*)msgBody.data());       // 编码消息头
    memcpy((char*)msgBody.data() + LY_PACKET_HEAD_LEN, strPBBody.c_str(), strPBBody.size());
    appendTail((char*)msgBody.data(), stPacketReq.m_uPacketLen);  // 添加消息尾部

    //string内容正确但length不对，恢复一下其length
    vehData_.append(msgBody.c_str(), stPacketReq.m_uPacketLen);
    return;
}

void TCU::appendTail(char* pRspMsg, unsigned int uRspMsgLen)
{
    // 计算CRC16
    unsigned short uCalcCrc16 = UtilGenCRC16(pRspMsg, uRspMsgLen - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN);
    *(unsigned short*)(pRspMsg + uRspMsgLen - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN) = uCalcCrc16;
    // 加上结束域
    *(pRspMsg + uRspMsgLen - LY_PACKET_END_FLAG_LEN) = LY_PACKET_END_FLAG_1;
    *(pRspMsg + uRspMsgLen - LY_PACKET_END_FLAG_LEN + 1) = LY_PACKET_END_FLAG_2;
}

void TCU::sendHeartBeatOnTcp(const TcpConnectionPtr& conn)
{
  makeZNAHeartBeatReq();
  if(conn) conn->send(heartBeatReq_);
}

void TCU::sendHeartBeatOnSsl(const SSLConnectionPtr& sslConn)
{
  LOG_INFO << "sendHeartBeatOnSsl";
  makeZNAHeartBeatReq();
  if(sslConn) {
    LOG_INFO << "sslConn->send " << "heartBeatReq_:("
    << heartBeatReq_.data() << ")";
    sslConn->send(heartBeatReq_.data(), heartBeatReq_.length());
  }
}

void TCU::makeZNAHeartBeatReq()
{
    heartBeatReq_.clear();
    zna::protocol::HeartbeatReq objHeartbeatReq;

    //更新时间戳
    struct timeval tv;
    gettimeofday(&tv, NULL);
    objHeartbeatReq.set_time_stamp(static_cast<unsigned int>(tv.tv_sec));

    string strPBBody;
    if (!objHeartbeatReq.SerializeToString(&strPBBody))
    {
        LOG_ERROR << "HeartbeatReq SerializeToString failed !!!";
        return;
    }

    LYDCMMsgHead stPacketReq;
    stPacketReq.m_uPacketLen = LY_PACKET_HEAD_LEN + LY_PACKET_TAIL_LEN - LY_PACKET_TIME_LEN + strPBBody.size();
    stPacketReq.m_uMsgID = LY_DCM_MSG_NISSAN_TBOX_HEARTBEAT_REQ;
    stPacketReq.m_cSecretFlag = ENCRYPT_FLAG_NO_ENCRYPT;
    stPacketReq.m_uVersion = VERSION_NISSANTBOX_NUMBER_01; //TODO:确认version值是多少,从配置中读取version.

    string msgBody;
    if (static_cast<int>(msgBody.capacity()) < stPacketReq.m_uPacketLen)
    {
        msgBody.resize(stPacketReq.m_uPacketLen);
    }

    EnCodeLYDCMMsgHead(stPacketReq, (char*)msgBody.data());       // 编码消息头
    memcpy((char*)msgBody.data() + LY_PACKET_HEAD_LEN, strPBBody.c_str(), strPBBody.size());
    appendTail((char*)msgBody.data(), stPacketReq.m_uPacketLen);  // 添加消息尾部

    //string内容正确但length不对，恢复一下其length
    heartBeatReq_.append(msgBody.c_str(), stPacketReq.m_uPacketLen);
    return;
}

void TCU::consoleThreadProc()
{
    isRunning_ = true;

    while (true)
    {
        if (isExit_)
            return;

        if (getchar() == '\n')
        {
            queue_.put("c");
        }
    }// end outer-while-loop

    isRunning_ = false;
}

void TCU::backendThreadProc(void* userp)
{
    TCU* owner = static_cast<TCU*>(userp);
    isRunning_ = true;

    while (true)
    {
        if (isExit_)
            return;

        queue_.take();
        owner->sendVehDataManually();
    }// end outer-while-loop

    isRunning_ = false;
}