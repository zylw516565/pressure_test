#include "muduo/base/Logging.h"
#include "muduo/net/Buffer.h"

#include "SSLConnection.h"
#include <utils/CommonUtil.h>

#include <openssl/err.h>

SSLConnection::SSLConnection(const TcpConnectionPtr &conn, ConnectionType type, const SSLContext& context) :
    conn_(conn),
    type_(type)
{
    SSL_library_init();
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    LOG_INFO << context.ca_path.c_str();
    LOG_INFO << context.crt_path.c_str();
    LOG_INFO << context.private_key_path.c_str();
    ctx_ = SSL_CTX_new(SSLv23_method());
    SSL_CTX_set_verify_depth(ctx_,0);
    if (!context.crt_path.empty())
    {
        if (SSL_CTX_use_certificate_file(ctx_, context.crt_path.c_str(), SSL_FILETYPE_PEM) <= 0)
        {
            if(ERR_get_error() == 336245134){
                //临时降低证书安全级别
                SSL_CTX_set_verify_depth(ctx_,1);
                if (SSL_CTX_use_certificate_file(ctx_, context.crt_path.c_str(), SSL_FILETYPE_PEM) <= 0){
                    LOG_FATAL << ERR_error_string(ERR_get_error(), NULL);
                }
            }
            else{
                LOG_FATAL << ERR_error_string(ERR_get_error(), NULL);
            }
            
        }
    }

    if (SSL_CTX_use_PrivateKey_file(ctx_, context.private_key_path.c_str(), SSL_FILETYPE_PEM) <= 0)
    {
        LOG_FATAL << ERR_error_string(ERR_get_error(), NULL);
    }

    if (!SSL_CTX_load_verify_locations(ctx_, context.ca_path.c_str(), NULL))
    {
        LOG_FATAL << ERR_error_string(ERR_get_error(), NULL);
    }

    ssl_ = SSL_new(ctx_);
    BIO_new_bio_pair(&internal_bio_, 0, &network_bio_, 0);
    SSL_set_bio(ssl_, internal_bio_, internal_bio_);
    
    if (type_ == ConnectionType::kClient)
    {
        SSL_set_connect_state(ssl_);
    }

}

SSLConnection::~SSLConnection()
{
    SSL_free(ssl_);
    BIO_free(network_bio_); 
}

void SSLConnection::handshake()
{
    int ret;
    ret = SSL_do_handshake(ssl_);
    LOG_INFO << "SSL_do_handshake: " << ret;
    if (ret == 1)
    {
        LOG_INFO << "SSL handshake finished";
        connection_cb_(shared_from_this());
    }
    else
    {
        LOG_TRACE << SSL_get_error(ssl_,ret);
        send(NULL, 0);
    }

}

void SSLConnection::send(const void* message, int len)
{
    if (conn_)
    {
        if (message != NULL && len != 0)
        {
            int ret = 0;
            int offset = 0;
            int bytes_to_write = len;
            while (bytes_to_write)
            {
                ret = SSL_write(ssl_, (char*)message + offset, len - offset);
                if (ret > 0)
                {
                    offset += ret;
                    if(offset == len)
                    {
                        break;
                    }
                    bytes_to_write -= ret;
                }
                else
                {
                    LOG_FATAL << SSL_get_error(ssl_, ret);
                }
            }
        }

        int bytes_to_read = 0;
        while ((bytes_to_read = BIO_pending(network_bio_)) > 0)
        {
            send_buffer_.ensureWritableBytes(bytes_to_read);
            int read = BIO_read(network_bio_, send_buffer_.beginWrite(), send_buffer_.writableBytes());
            send_buffer_.hasWritten(read);

            if (send_buffer_.readableBytes() > 0)
            {
                conn_->send(&send_buffer_);
            }
        }
    }
}

void SSLConnection::onTcpMessage(Buffer* buf, Timestamp time)
{
    int ret,ret2 = 0;
    //TODO:need a while loop
    ret = BIO_write(network_bio_, buf->peek(), buf->readableBytes());
    buf->retrieveAll();
    LOG_DEBUG << "BIO_write: " << ret;

    if (!SSL_is_init_finished(ssl_))
    {
        handshake();
    }
    else
    {
        do
        {
            if (recv_buffer_.writableBytes() < 1024 * 4)
            {
                recv_buffer_.ensureWritableBytes(1024 * 4);
            }

            ret = SSL_read(ssl_, (void *)(recv_buffer_.beginWrite()), recv_buffer_.writableBytes());
            if(0 >= ret)
            {
                int err = SSL_get_error(ssl_, ret);
                LOG_TRACE << "SSL_read: " << ret << " err:" << err;
            }
            else
            {
                ret2 += ret;
                // string raw2 = ::ToHexString((uint8_t*)recv_buffer_.peek(),0, ret2);
                // LOG_INFO <<"SSL_read recv data(" << ret << "):" << raw2;
                recv_buffer_.hasWritten(ret);
            }
        } while (ret > 0);

        //TODO:ret < 0
        message_cb_(shared_from_this(), &recv_buffer_, Timestamp::now());
    }
}