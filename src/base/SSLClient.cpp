#include "SSLClient.h"

#include "muduo/base/Logging.h"

void DefaultSSLConnectionCb(const SSLConnectionPtr& conn)
{
    LOG_TRACE << "SSL connection established";
}

void DefaultSSLMessageCb(const SSLConnectionPtr&, Buffer* buf, Timestamp)
{
    buf->retrieveAll();
}

SSLClient::SSLClient(EventLoop* loop, const InetAddress& serverAddr, const string& name, const SSLContext& context) :
    loop_(loop),
    client_(loop, serverAddr, name),
    context_(context),
    connection_cb_(DefaultSSLConnectionCb),
    message_cb_(DefaultSSLMessageCb)
{
    client_.setConnectionCallback(std::bind(&SSLClient::onTcpConnection, this, _1));
    client_.setMessageCallback(std::bind(&SSLClient::onTcpMessage, this, _1, _2, _3));
}

SSLClient::~SSLClient()
    {}

void SSLClient::connect() 
{
    LOG_INFO << "SSLClient::connect";
    client_.connect();
}

void SSLClient::disconnect()
{
    client_.disconnect();
}

void SSLClient::stop() 
{
    client_.stop();   
}

void SSLClient::enableRetry()
{
  client_.enableRetry();
}

void SSLClient::onTcpConnection(const TcpConnectionPtr& conn)
{
    LOG_INFO << conn->localAddress().toIpPort() << " -> "
             << conn->peerAddress().toIpPort() << " is "
             << (conn->connected() ? "UP" : "DOWN");

    if (conn->connected())
    {
        conn_.reset(new SSLConnection(conn, SSLConnection::ConnectionType::kClient, context_));
        conn_->setConnectionCallback(connection_cb_);
        conn_->setMessageCallback(message_cb_);
        conn_->handshake();
    }
    else
    {
        conn_.reset();
    }
}

void SSLClient::onTcpMessage(const TcpConnectionPtr& conn, Buffer* buf, Timestamp time)
{
    conn_->onTcpMessage(buf, time);
}