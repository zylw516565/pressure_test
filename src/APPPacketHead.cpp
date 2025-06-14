///@file     APPPacketHead.cpp
///@brief    App 消息包
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     


#include "APPPacketHead.h"
#include "CommunicationCommon.h"
//#include "Server.h"

#ifdef WIN32
#include <winsock2.h>
#else
#include <stddef.h>
#include <arpa/inet.h>
#endif

const int INT_SIZE = sizeof(int);
const int SHORT_SIZE = sizeof(short);

/**********************************************************************************/
// 函数：EnCodeAppPacketHead
// 功能：App 消息头编码
// 输入： stAppPacketHead  App 消息头
// 输出： pEncodeBuffer    编码结果
// 返回值： int 成功返回0，否则返回失败
// 备注：  外部保证编码结果区域的长度大于等于PACKET_HEAD_LEN
// 修改记录：
// 2015-01-10         tangjie                  App 消息包
// 2015-01-30         tangjie                  修改Bit位顺序，bit0为最低位  
/**********************************************************************************/
int EnCodeAppPacketHead(const APPPacketHead& stAppPacketHead, char* pEncodeBuffer)
{
    if (NULL == pEncodeBuffer)
    {
        return 1;
    }

    ENCODE_VALUE_8(stAppPacketHead.m_cPreFlag[0], pEncodeBuffer);
    pEncodeBuffer++;
    ENCODE_VALUE_8(stAppPacketHead.m_cPreFlag[1], pEncodeBuffer);
    pEncodeBuffer++;
    ENCODE_VALUE_32(stAppPacketHead.m_uPacketLen, pEncodeBuffer);
    pEncodeBuffer += INT_SIZE;
    ENCODE_VALUE_16(stAppPacketHead.m_uHeadLen, pEncodeBuffer);
    pEncodeBuffer += SHORT_SIZE;
    ENCODE_VALUE_8(stAppPacketHead.m_cVersion, pEncodeBuffer);
    pEncodeBuffer++;
    //组合加密方式和登录标志
    char cTmp = (stAppPacketHead.m_cEncrypt & 0x07) | ((stAppPacketHead.m_cLog << 3) & 0x08) | ((stAppPacketHead.m_cPublicKey << 4) & 0xF0); 
    ENCODE_VALUE_8(cTmp, pEncodeBuffer);
    pEncodeBuffer++;
    ENCODE_VALUE_8(stAppPacketHead.m_cMsgType, pEncodeBuffer);
    pEncodeBuffer++;
    ENCODE_VALUE_16(stAppPacketHead.m_uMsgFuncNo, pEncodeBuffer);
    pEncodeBuffer += SHORT_SIZE;
    ENCODE_VALUE_16(stAppPacketHead.m_uMsgID, pEncodeBuffer);
    pEncodeBuffer += SHORT_SIZE;
    memcpy(pEncodeBuffer, stAppPacketHead.m_cSession, APP_PACKET_SESSION_LEN);
    pEncodeBuffer += APP_PACKET_SESSION_LEN;
    ENCODE_VALUE_32(stAppPacketHead.m_nErrorCode, pEncodeBuffer);
    pEncodeBuffer += INT_SIZE;
    ENCODE_VALUE_32(stAppPacketHead.m_uMsgLen, pEncodeBuffer);
    pEncodeBuffer += INT_SIZE;
    ENCODE_VALUE_16(stAppPacketHead.m_uMsgNum, pEncodeBuffer);
    pEncodeBuffer += SHORT_SIZE;
    
    return 0;
}

/**********************************************************************************/
// 函数：DeCodeAppPacketHead
// 功能：App 消息头解码
// 输入： pBuffer          编码结果
// 输出： stAppPacketHead  App 消息头
// 返回值： int 成功返回0，否则返回失败
// 备注：  
// 修改记录：
// 2015-01-10         tangjie                  App 消息包   
// 2015-01-30         tangjie                  修改Bit位顺序，bit0为最低位  
/**********************************************************************************/
int DeCodeAppPacketHead(const char* pBuffer, APPPacketHead& stAppPacketHead)
{
    if (NULL == pBuffer)
    {
        return 1;
    }

    DECODE_VALUE_8(stAppPacketHead.m_cPreFlag[0], pBuffer);
    pBuffer++;
    DECODE_VALUE_8(stAppPacketHead.m_cPreFlag[1], pBuffer);
    pBuffer++;
    DECODE_VALUE_32(stAppPacketHead.m_uPacketLen, pBuffer);
    pBuffer += INT_SIZE;
    DECODE_VALUE_16(stAppPacketHead.m_uHeadLen, pBuffer);
    pBuffer += SHORT_SIZE;
    DECODE_VALUE_8(stAppPacketHead.m_cVersion, pBuffer);
    pBuffer++;
    //拆分加密方式和登录标志
    char cTmp = 0; 
    DECODE_VALUE_8(cTmp, pBuffer);
    pBuffer++;
    stAppPacketHead.m_cEncrypt = (cTmp & 0x07);
    stAppPacketHead.m_cLog = (cTmp & 0x08) >> 3;
    stAppPacketHead.m_cPublicKey = (cTmp & 0xF0) >> 4;

    DECODE_VALUE_8(stAppPacketHead.m_cMsgType, pBuffer);
    pBuffer++;
    DECODE_VALUE_16(stAppPacketHead.m_uMsgFuncNo, pBuffer);
    pBuffer += SHORT_SIZE;
    DECODE_VALUE_16(stAppPacketHead.m_uMsgID, pBuffer);
    pBuffer += SHORT_SIZE;
    memcpy(stAppPacketHead.m_cSession, pBuffer, APP_PACKET_SESSION_LEN);
    pBuffer += APP_PACKET_SESSION_LEN;
    DECODE_VALUE_32(stAppPacketHead.m_nErrorCode, pBuffer);
    pBuffer += INT_SIZE;
    DECODE_VALUE_32(stAppPacketHead.m_uMsgLen, pBuffer);
    pBuffer += INT_SIZE;
    DECODE_VALUE_16(stAppPacketHead.m_uMsgNum, pBuffer);
    pBuffer += SHORT_SIZE;

    if (0 != stAppPacketHead.m_uMsgNum)
    {
        // 暂时不支持拆包
        return 1;
    }

    // 包体长度必须等于（包总长度-包头前置长度-包头长度）
    if (stAppPacketHead.m_uMsgLen != (stAppPacketHead.m_uPacketLen - stAppPacketHead.m_uHeadLen - APP_PACKET_PRE_LEN))
    {
        return 2;
    }

    return 0;
}

