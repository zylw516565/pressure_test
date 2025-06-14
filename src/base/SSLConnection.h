#pragma once

#include "muduo/net/TcpConnection.h"

#include <openssl/ssl.h>

using namespace muduo;
using namespace muduo::net;

class SSLConnection;

using SSLConnectionPtr = std::shared_ptr<SSLConnection>;
using SSLConnectionCallback = std::function<void (const SSLConnectionPtr&)>;
using SSLMessageCallback = std::function<void (const SSLConnectionPtr&,
                                               Buffer*,
                                               Timestamp)>;

struct SSLContext
{
    string ca_path;
    string private_key_path;
    string crt_path;
};

class SSLConnection : noncopyable,
                      public std::enable_shared_from_this<SSLConnection>
{
public:
    enum class ConnectionType
    {
        kClient,
        kServer
    };

    SSLConnection(const TcpConnectionPtr& conn, ConnectionType type, const SSLContext& context);

    ~SSLConnection();

    void send(const void* message, int len);

    void handshake();

    TcpConnectionPtr getTcpConnection() { return conn_; };

    void onTcpMessage(Buffer* buf, Timestamp time);

    void setConnectionCallback(const SSLConnectionCallback& cb)
    {
        connection_cb_ = cb;
    }

    void setMessageCallback(const SSLMessageCallback& cb)
    {
        message_cb_ = cb;
    }

private:
    TcpConnectionPtr conn_;
    ConnectionType type_;
    SSLConnectionCallback connection_cb_;
    SSLMessageCallback message_cb_;

    SSL_CTX* ctx_;
    SSL* ssl_;
    BIO* internal_bio_;
    BIO* network_bio_;
    Buffer send_buffer_;
    Buffer recv_buffer_;
};
