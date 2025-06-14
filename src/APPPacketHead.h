///@file     APPPacketHead.h
///@brief    App ��Ϣ��
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

// Session ����
#define APP_PACKET_SESSION_LEN  46

// Ĭ�ϰ�����
#define DEFAULT_APP_PACKET_LEN 1024

// �澯���������ȣ� 8K = 8192
#define WARING_APP_PACKET_LEN 8192

// ֧���������ȣ�64K = 65536
#define MAX_APP_PACKET_LEN 65536

// ��ǰ�ñ�־����:LY
#define APP_PACKET_PRE_FLAG_1  'L'
#define APP_PACKET_PRE_FLAG_2  'Y'
#define APP_PACKET_PRE_FLAG_LEN  2

// ��ͷǰ�ó���:ǰ�ñ�־+��Ϣ�����ȣ����ֽڣ�(APP_PACKET_PRE_FLAG_LEN + 4)
#define APP_PACKET_PRE_LEN  6

// ��Ϣ��ͷ���ȣ�����ǰ�ò���
#define APP_PACKET_HEAD_TOTAL_LEN 71

// ��Ϣ��ͷ���ȣ�������ǰ�ò���
#define APP_PACKET_HEAD_LEN 65

///@class  APPPacketHead [APPPacketHead.h]
///@brief  App ��Ϣͷ
///@author tangjie
///@note   
struct APPPacketHead
{                                             
    char                                m_cPreFlag[APP_PACKET_PRE_FLAG_LEN];// ǰ�ò��֣���ͷǰ�ñ�־��LY
    unsigned int                        m_uPacketLen;                       // ǰ�ò��֣�������
    unsigned short                      m_uHeadLen;                         // ��ͷ����
    unsigned char                       m_cVersion;                         // �汾��
    unsigned char                       m_cEncrypt;                         // ���ܷ�ʽ(Bit0-2)�� 0 ��ʾδ���ܣ����ܷ�ʽ���¼��־����ʱ����һ���ֽ�
    unsigned char                       m_cLog;                             // ��¼��־(Bit3)�� 0 ��ʾ�ѵ�¼��1 ��ʾδ��¼
    unsigned char                       m_cPublicKey;                       // ���ף�bit4-7��:�����ܷ�ʽ��Ϊ0ʱ������
    unsigned char                       m_cMsgType;                         // ��Ϣ���ͺ�
    unsigned short                      m_uMsgFuncNo;                       // ��Ϣ���ܺ�
    unsigned short                      m_uMsgID;                           // ��ϢID
    char                                m_cSession[APP_PACKET_SESSION_LEN]; // �ỰID
    int                                 m_nErrorCode;                       // ������
    unsigned int                        m_uMsgLen;                          // ��Ϣ�����ܳ���
    unsigned short                      m_uMsgNum;                          // ��Ϣ����ţ�����������Ϊ0

    ///���캯��
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

    ///�������캯��
    ///@param [in]    stAppPacketHead  App ��Ϣͷ
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

    ///��ֵ������
    ///@param [in]    stAppPacketHead  App ��Ϣͷ
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

///App ��Ϣͷ����
///@param [in]    stAppPacketHead  App ��Ϣͷ
///@param [inout] pEncodeBuffer    ������
///return int �ɹ�����0�����򷵻�ʧ��
///@note  �ⲿ��֤����������ĳ��ȴ��ڵ���PACKET_HEAD_LEN
APP_PACKET_EXPORT int EnCodeAppPacketHead(const APPPacketHead& stAppPacketHead, char* pEncodeBuffer);


///App ��Ϣͷ����
///@param [in]    pBuffer          ������
///@param [inout] stAppPacketHead  App ��Ϣͷ
///return int �ɹ�����0�����򷵻�ʧ��
///@note  
APP_PACKET_EXPORT int DeCodeAppPacketHead(const char* pEncodeBuffer, APPPacketHead& stAppPacketHead);

#ifdef __cplusplus
}
#endif

#endif  /*APP_PACKET_HEAD_H*/