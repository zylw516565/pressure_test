#include "TCUCodec.h"

#include <muduo/base/Logging.h>

#include "APPCommon.h"
#include "zna_protocol_message.pb.h"

using namespace muduo;
using namespace muduo::net;

using namespace zna::protocol;

TCUCodec::TCUCodec(const TcpConnectionPtr& conn,
                   const int sessionid,
                   const LYMessageCallback& cb)
    :tmpConn_(conn)
    ,m_id(sessionid)
    ,messageCallback_(cb)
{
}

void TCUCodec::sendPackage(const std::string& strPackageData)
{
    if (strPackageData.empty())
        return;

    //TODO: 这些Session和connection对象的生命周期要好好梳理一下
    if (tmpConn_.expired())
    {
        //FIXME: 出现这种问题需要排查
        LOG_ERROR << "Tcp connection is destroyed , but why TcpSession is still alive ?";
        return;
    }

    TcpConnectionPtr conn = tmpConn_.lock();
    if (conn)
    {
        LOG_INFO << "Send data, package length: " << strPackageData.length();
        conn->send(strPackageData);
    }
}

void TCUCodec::onMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp receiveTime)
{
    ++messagesRead_;
    bytesRead_ += buf->readableBytes();
    bytesWritten_ += buf->readableBytes();
    LOG_DEBUG << "onVehicleData recv data: " << buf->peek();

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
        LYDCMMsgHeadPtr  spPacketHeadPtr(new LYDCMMsgHead);
        DeCodeLYDCMMsgHead(buf->peek(), (*spPacketHeadPtr.get()));

        //取包体
        string msgBody;
        int bodyLen = packetLen - LY_PACKET_HEAD_LEN - LY_PACKET_CRC_LEN - LY_PACKET_END_FLAG_LEN;
        msgBody.assign((buf->peek() + LY_PACKET_HEAD_LEN), bodyLen);

        if (messageCallback_)
        {
            messageCallback_(conn, spPacketHeadPtr, msgBody, receiveTime);
        }
        else
        {
            LOG_ERROR << "messageCallback_ is nullptr";
        }

        buf->retrieve(packetLen);
    }
}
