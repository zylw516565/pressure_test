///@file     CommunicationCommon.h
///@brief    通讯公共属性定义
///@author   tangjie
///@date     2015-01-04
///@version  v1.0.0.0
///@note     

#ifndef COMMUNICATION_COMMON_H
#define COMMUNICATION_COMMON_H

#ifdef WIN32  //Windows

#define COMMUNICATION_EXPORT __declspec(dllexport)

#else           //Linux

#define COMMUNICATION_EXPORT

#endif

// Tcp 客户端 最大连接数量
#define UTIL_TCP_CLIENT_MAX_CONNECT_NUM  1024

// Tcp 服务端 最大连接数量
#define UTIL_TCP_SERVER_MAX_CONNECT_NUM  1024

// 默认发送缓冲区大小 64K
#define UTIL_TCP_SEND_BUFFER_SIZE 64 * 1024
// 默认接收缓冲区大小 64K
#define UTIL_TCP_RECV_BUFFER_SIZE 64 * 1024

///@class  TCP_SERVER_OPT [CommunicationCommon.h]
///@brief  Tcp 服务属性
///@author tangjie
///@note   
enum TCP_SERVER_OPT
{
    TCP_SERVER_OPT_NODELAY,                 // 禁止发送合并的Nagle算法,0 否 1 是
    TCP_SERVER_OPT_SENDBUFSIZE,             // 连接发送缓存区大小
    TCP_SERVER_OPT_RECVBUFSIZE,             // 连接接收缓存区大小
};


///@struct st_ConnectRecvData [CommunicationCommon.h]
///@brief  数据接收缓存区
///@author tangjie
///@note   
typedef struct st_ConnectRecvData 
{
    int                             m_nID;                // 连接ID
    void*                           m_pHandle;            // 连接管理句柄
    unsigned int                    m_nLen;               // 接收缓冲区总长度
    unsigned int                    m_nRecvLen;           // 已接收数据长度
    long long                       m_nRecvTime;          // 接收数据时间
    char*                           m_pData;              // 接收缓冲区
}ConnectRecvData;


///@enum   TCP_STATUS [CommunicationCommon.h]
///@brief  Tcp 连接状态
///@author tangjie
///@note   
enum TCP_STATUS
{
    TCP_STATUS_ACCEPT,       // 服务器接收到 新连接
    TCP_STATUS_CONNECT,      // 客户端已经连接到服务器
    TCP_STATUS_CLOSE,        // 客户端与服务器断开连接
    TCP_STATUS_FAIL,         // 客户端连接服务器失败
    TCP_STATUS_DELETE,       // 连接删除，释放资源
};

///TCP客户端的连接状态变化回调
///@param [in]    nConnectID       连接ID
///@param [in]    pIp              连接对应的服务IP
///@param [in]    nPort            连接对应的服务端口
///@param [in]    nStatus          连接状态，具体见 TCP_STATUS
///@param [in]    pAddition        附加参数，由创建连接时传入
///return void
///@note  不要在通知函数中处理复杂逻辑，避免阻塞其它连接的处理
typedef void (*TcpClientStatus)(int nConnectID, const char* pIp, unsigned short nPort, int nStatus, void* pAddition);

///TCP服务器的连接状态回调，包括accept和close
///@param [in]    nConnectID       连接ID
///@param [in]    pIp              连接对应的IP
///@param [in]    nPort            连接对应的端口
///@param [in]    nStatus          连接状态，具体见 TCP_STATUS
///@param [in]    pAddition        附加参数，由创建连接时传入
///return void
///@note  不要在通知函数中处理复杂逻辑，避免阻塞其它连接的处理
typedef void (*TcpServerStatus)(int nConnectID, const char* pIp, unsigned short nPort, int nStatus, void* pAddition);

///@enum   TCP_DATA_TYPE [CommunicationCommon.h]
///@brief  Tcp 数据处理类型
///@author tangjie
///@note 
enum TCP_DATA_TYPE
{
    TCP_RECV_DATA,           // 接收到数据
    TCP_SEND_SUCC,           // 发送数据成功
    TCP_SEND_FAIL,           // 发送数据失败
};

///TCP客户端数据处理通知，包括接收、发送数据处理
///@param [in]    nConnectID       连接ID 
///@param [in]    pData            接收时为接收到的数据，发送时为发送的数据
///@param [in]    nDataLen         连接时为接收到的数据长度，发送时为发送的数据长度
///@param [in]    nDataType        数据处理类型，具体见 TCP_DATA_TYPE
///@param [in]    pAddition        附加参数，由创建连接时传入
///return void
///@note  不要在通知函数中处理复杂逻辑，避免阻塞其它连接的处理
typedef void (*TcpClientData)(int nConnectID, const char* pData, int nDataLen, int nDataType, void* pAddition);

///TCP服务器数据处理通知，包括接收、发送数据处理
///@param [in]    nConnectID       连接ID 
///@param [in]    pData            接收时为接收到的数据，发送时为发送的数据
///@param [in]    nDataLen         连接时为接收到的数据长度，发送时为发送的数据长度
///@param [in]    nDataType        数据处理类型，具体见 TCP_DATA_TYPE
///@param [in]    pAddition        附加参数，由创建连接时传入
///return void
///@note  不要在通知函数中处理复杂逻辑，避免阻塞其它连接的处理
typedef void (*TcpServerData)(int nConnectID, const char* pData, int nDataLen, int nDataType, void* pAddition);

// 网络序字节转换定义
#define ENCODE_VALUE_8(v, b) do { *(char*)(b) = (v); }while(0);

#define ENCODE_VALUE_16(v, b) do { short uTmp16 = htons(v);\
    *(short*)(b) = uTmp16;\
}while(0);

#define ENCODE_VALUE_32(v, b) do { int uTmp32 = htonl(v);\
    *(int*)(b) = uTmp32;\
}while(0);

#define DECODE_VALUE_8(v, b) do { (v) = *(char*)(b);}while(0);

#define DECODE_VALUE_16(v, b) do { short uTmp16 = *(short*)(b);\
    (v) = ntohs(uTmp16);\
}while(0);

#define DECODE_VALUE_32(v, b) do { int uTmp32 = *(int*)(b);\
    (v) = ntohl(uTmp32);\
}while(0);



#endif  /*COMMUNICATION_COMMON_H*/