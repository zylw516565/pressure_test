#pragma once

#include "TCUCodec.h"
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/noncopyable.h>
#include <muduo/net/EventLoopThreadPool.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/BlockingQueue.h>

#include <utils/CommonUtil.h>
#include "DCMPacketHead.h"


#include <set>
#include <mutex>
#include <atomic>
#include <thread>

class SSLClient;

class SSLConnection;
using SSLConnectionPtr = std::shared_ptr<SSLConnection>;

class TCU : muduo::noncopyable
{
public:
  TCU(muduo::net::EventLoop* loop,
            const muduo::net::InetAddress& serverAddr);

  ~TCU();

  bool init(const ConfigParam& stParam);
  void uninit();

  bool isRunning(){ return isRunning_;}
private:

  void onConnected(const muduo::net::TcpConnectionPtr& conn);
  void onDisconnect(const muduo::net::TcpConnectionPtr& conn);
  void onMessage(const muduo::net::TcpConnectionPtr& conn,
      const LYDCMMsgHeadPtr& spPacketHead,
      const std::string& msgBody,
      muduo::Timestamp receiveTime);

  //ssl
  void onSSLConnection(const SSLConnectionPtr& conn);
  void onSSLMessage(const SSLConnectionPtr& conn, muduo::net::Buffer* buf, muduo::Timestamp time);

  void sendHeartBeatOnTcp(const muduo::net::TcpConnectionPtr& conn);
  void sendHeartBeatOnSsl(const SSLConnectionPtr& sslConn);

  void handleTimeout();

  void doLogin();

  void autoSendVehData(const muduo::net::TcpConnectionPtr& conn);

  void sendVehData();

  void sendVehDataManually();

  void quit();

  //************************

  void makeZNALoginReq();

  void makeDataByCmdType();

  void makeZNAVehicleData();

  void appendTail(char* pRspMsg, unsigned int uRspMsgLen);

  void makeZNAHeartBeatReq();

  static void consoleThreadProc();
  static void backendThreadProc(void* userp);

  muduo::net::EventLoop* loop_;

  std::unique_ptr<muduo::net::TcpClient> tcpClient_;
  muduo::net::TcpConnectionPtr tcpConn_;

  std::unique_ptr<SSLClient> sslClient_;
  SSLConnectionPtr sslConn_;

  TCUCodecPtr spCodec_;

  int  timeout_;
  std::atomic<int>  totalPressureTime_;   //压测总时长,单位为秒
  std::atomic<int64_t> pressureStartTime_;//压测开始时间,单位为微秒

  std::string  loginData_;                //登录请求
  std::string  vehData_;                  //整车数据请求
  std::string  heartBeatReq_;             //心跳请求

  std::atomic<int> totalReqCount_;        //use atomic
  std::atomic<int> totalRspCount_;        //use atomic

  std::atomic_int  sessionId_{};
  muduo::net::InetAddress  serverAddr_;      //连接地址

  static bool isRunning_;           //运行标志
  static bool isExit_   ;           //退出标志
  static muduo::BlockingQueue<std::string> queue_;
  std::unique_ptr<std::thread>     spConsoleThread_;
  std::unique_ptr<std::thread>     spBackendThread_;
};
