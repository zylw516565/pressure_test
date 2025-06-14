///@file     APPPacketHead.h
///@brief    App 消息包
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     

#ifndef APP_PACKET_HEAD_H
#define APP_PACKET_HEAD_H

#include "APPCommon.h"
#include <memory.h>

#ifdef _WIN32  //Windows
#define APP_PACKET_EXPORT __declspec(dllexport)
#else           //Linux
#define APP_PACKET_EXPORT
#endif

// Session 长度
#define APP_PACKET_SESSION_LEN  46

// 默认包长度
#define DEFAULT_APP_PACKET_LEN 1024

// 告警的最大包长度： 8K = 8192
#define WARING_APP_PACKET_LEN 8192

// 支持最大包长度：64K = 65536
#define MAX_APP_PACKET_LEN 65536

// 包前置标志长度:LY
#define APP_PACKET_PRE_FLAG_1  'L'
#define APP_PACKET_PRE_FLAG_2  'Y'
#define APP_PACKET_PRE_FLAG_LEN  2

// 包头前置长度:前置标志+消息包长度（四字节）(APP_PACKET_PRE_FLAG_LEN + 4)
#define APP_PACKET_PRE_LEN  6

// 消息包头长度，包括前置部分
#define APP_PACKET_HEAD_TOTAL_LEN 71

// 消息包头长度，不包括前置部分
#define APP_PACKET_HEAD_LEN 65

///@class  APPPacketHead [APPPacketHead.h]
///@brief  App 消息头
///@author tangjie
///@note   
struct APPPacketHead
{                                             
    char                                m_cPreFlag[APP_PACKET_PRE_FLAG_LEN];// 前置部分，包头前置标志：LY
    unsigned int                        m_uPacketLen;                       // 前置部分，包长度
    unsigned short                      m_uHeadLen;                         // 包头长度
    unsigned char                       m_cVersion;                         // 版本号
    unsigned char                       m_cEncrypt;                         // 加密方式(Bit0-2)： 0 表示未加密；加密方式与登录标志发送时共用一个字节
    unsigned char                       m_cLog;                             // 登录标志(Bit3)： 0 表示已登录，1 表示未登录
    unsigned char                       m_cPublicKey;                       // 公匙（bit4-7）:当加密方式不为0时才有用
    unsigned char                       m_cMsgType;                         // 消息类型号
    unsigned short                      m_uMsgFuncNo;                       // 消息功能号
    unsigned short                      m_uMsgID;                           // 消息ID
    char                                m_cSession[APP_PACKET_SESSION_LEN]; // 会话ID
    int                                 m_nErrorCode;                       // 错误码
    unsigned int                        m_uMsgLen;                          // 消息包体总长度
    unsigned short                      m_uMsgNum;                          // 消息包序号，不拆包情况下为0

    ///构造函数
    ///return
    APPPacketHead()
    {
        m_cPreFlag[0] = APP_PACKET_PRE_FLAG_1;
        m_cPreFlag[1] = APP_PACKET_PRE_FLAG_2;
        m_cVersion = 0;
        m_cEncrypt = 0;
        m_cLog = 0;
        m_cPublicKey = 0;
        memset(m_cSession, 0, APP_PACKET_SESSION_LEN);
        m_nErrorCode = 0;
        m_uMsgNum = 0;
    }

    ///拷贝构造函数
    ///@param [in]    stAppPacketHead  App 消息头
    ///return
    APPPacketHead(const APPPacketHead& stAppPacketHead)
    {
        m_cPreFlag[0] = stAppPacketHead.m_cPreFlag[0];
        m_cPreFlag[1] = stAppPacketHead.m_cPreFlag[1];
        m_uPacketLen = stAppPacketHead.m_uPacketLen;
        m_uHeadLen = stAppPacketHead.m_uHeadLen;
        m_cVersion = stAppPacketHead.m_cVersion;
        m_cEncrypt = stAppPacketHead.m_cEncrypt;
        m_cLog = stAppPacketHead.m_cLog;
        m_cPublicKey = stAppPacketHead.m_cPublicKey;
        m_cMsgType = stAppPacketHead.m_cMsgType;
        m_uMsgFuncNo = stAppPacketHead.m_uMsgFuncNo;
        m_uMsgID = stAppPacketHead.m_uMsgID;
        memcpy(m_cSession, stAppPacketHead.m_cSession, APP_PACKET_SESSION_LEN);
        m_nErrorCode = stAppPacketHead.m_nErrorCode;
        m_uMsgLen = stAppPacketHead.m_uMsgLen;
        m_uMsgNum = stAppPacketHead.m_uMsgNum;
    }

    ///赋值操作符
    ///@param [in]    stAppPacketHead  App 消息头
    ///return APPPacketHead& 
    APPPacketHead& operator = (const APPPacketHead& stAppPacketHead)
    {
        m_cPreFlag[0] = stAppPacketHead.m_cPreFlag[0];
        m_cPreFlag[1] = stAppPacketHead.m_cPreFlag[1];
        m_uPacketLen = stAppPacketHead.m_uPacketLen;
        m_uHeadLen = stAppPacketHead.m_uHeadLen;
        m_cVersion = stAppPacketHead.m_cVersion;
        m_cEncrypt = stAppPacketHead.m_cEncrypt;
        m_cLog = stAppPacketHead.m_cLog;
        m_cPublicKey = stAppPacketHead.m_cPublicKey;
        m_cMsgType = stAppPacketHead.m_cMsgType;
        m_uMsgFuncNo = stAppPacketHead.m_uMsgFuncNo;
        m_uMsgID = stAppPacketHead.m_uMsgID;
        memcpy(m_cSession, stAppPacketHead.m_cSession, APP_PACKET_SESSION_LEN);
        m_nErrorCode = stAppPacketHead.m_nErrorCode;
        m_uMsgLen = stAppPacketHead.m_uMsgLen;
        m_uMsgNum = stAppPacketHead.m_uMsgNum;

        return *this;
    }
};



#ifdef __cplusplus
extern "C"{
#endif

///App 消息头编码
///@param [in]    stAppPacketHead  App 消息头
///@param [inout] pEncodeBuffer    编码结果
///return int 成功返回0，否则返回失败
///@note  外部保证编码结果区域的长度大于等于PACKET_HEAD_LEN
APP_PACKET_EXPORT int EnCodeAppPacketHead(const APPPacketHead& stAppPacketHead, char* pEncodeBuffer);


///App 消息头解码
///@param [in]    pBuffer          编码结果
///@param [inout] stAppPacketHead  App 消息头
///return int 成功返回0，否则返回失败
///@note  
APP_PACKET_EXPORT int DeCodeAppPacketHead(const char* pEncodeBuffer, APPPacketHead& stAppPacketHead);

#ifdef __cplusplus
}
#endif

#endif  /*APP_PACKET_HEAD_H*/