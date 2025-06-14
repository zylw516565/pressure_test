#pragma once

#include <muduo/net/TcpConnection.h>
#include <muduo/net/Buffer.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/noncopyable.h>
#include <utils/CommonUtil.h>
#include "DCMPacketHead.h"

#include <assert.h>
#include <atomic>


class TCUCodec : muduo::noncopyable
{
public:
    typedef std::function<void(const muduo::net::TcpConnectionPtr&, 
                                 const LYDCMMsgHeadPtr&,
                                 const std::string&,
                                 muduo::Timestamp)> LYMessageCallback;

    TCUCodec(const muduo::net::TcpConnectionPtr& conn,
             const int sessionid,
             const LYMessageCallback& cb);

    void onMessage(const muduo::net::TcpConnectionPtr& conn,
                   muduo::net::Buffer* buf,
                   muduo::Timestamp);

    int64_t bytesRead() const { return bytesRead_; }

    int64_t messagesRead() const { return messagesRead_; }

    void sendPackage(const std::string& strPackageData);

private:
    std::weak_ptr<muduo::net::TcpConnection>    tmpConn_;
    int32_t                         m_id;    //session id
    LYMessageCallback               messageCallback_;

    int64_t bytesRead_;
    int64_t bytesWritten_;
    int64_t messagesRead_;
};

typedef std::shared_ptr<TCUCodec> TCUCodecPtr;