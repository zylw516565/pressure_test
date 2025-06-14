#pragma once
#include "SSLConnection.h"
#include "muduo/net/TcpClient.h"

using namespace muduo;
using namespace muduo::net;

class SSLClient : noncopyable
{
public:
    SSLClient(EventLoop* loop,
              const InetAddress& serverAddr,
              const string& name,
              const SSLContext& context);

    ~SSLClient();

    void connect();
    void disconnect();
    void stop();
    void enableRetry();

    SSLConnectionPtr sslConnection() const
    {
      return conn_;
    }

    void setConnectionCallback(SSLConnectionCallback cb)
    {
        connection_cb_ = std::move(cb);
    }

    void setMessageCallback(SSLMessageCallback cb)
    {
        message_cb_ = std::move(cb);
    }

    // void setWriteCompleteCallback(WriteCompleteCallback cb)
    // {
    //     writeCompleteCallback_ = std::move(cb);
    // }
    const string& name() const{return client_.name();}

private:
    void onTcpConnection(const TcpConnectionPtr& conn);

    void onTcpMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time);
private:
    EventLoop* loop_;
    TcpClient client_;
    SSLConnectionPtr conn_;
    SSLContext context_;

    SSLConnectionCallback connection_cb_;
    SSLMessageCallback message_cb_;
};