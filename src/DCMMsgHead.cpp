///@file     DCMMsgHead.cpp
///@brief    DCM��Ϣͷ����
///@author   jiangxiaobao
///@date     2015-01-30
///@version  v1.0.0.0
///@note 

#include <stdlib.h>
#include "DCMPacketHead.h"


#ifdef WIN32
#include <WinSock2.h>
#else
#include <stddef.h>
#include <arpa/inet.h>
#endif

const int INT_SIZE = sizeof(int);
const int SHORT_SIZE = sizeof(short);
const int CHAR_SIZE = sizeof(char);

// *******************�µ�Э��***************************
/**********************************************************************************/
// ������EnCodeLYDCMMsgHead
// ���ܣ�DCM��Ϣͷ����
// ���룺    stDCMMsgHead       ��Ϣͷ
// �����    pEncodeBuffer      ������
// ����ֵ�� int �ɹ�����0�����򷵻�ʧ��
// ��ע��  �ⲿ��֤����������ĳ��ȴ��ڵ�����Ϣͷ��
// �޸ļ�¼��
// 2015-10-15         jiangxiaobao                  ����                
/**********************************************************************************/
int EnCodeLYDCMMsgHead(const LYDCMMsgHead& stDCMMsgHead, char* pEncodeBuffer)
{
    if (NULL == pEncodeBuffer)
    {
        return 1;
    }

    *pEncodeBuffer = stDCMMsgHead.m_cPreFlag[0];
    pEncodeBuffer++;
    *pEncodeBuffer = stDCMMsgHead.m_cPreFlag[1];
    pEncodeBuffer++;
    *(unsigned short*)pEncodeBuffer = stDCMMsgHead.m_uPacketLen;
    pEncodeBuffer += SHORT_SIZE;
    *(unsigned short*)pEncodeBuffer = stDCMMsgHead.m_uVersion;
    pEncodeBuffer += SHORT_SIZE;
    *(unsigned short*)pEncodeBuffer = stDCMMsgHead.m_uMsgID;
    pEncodeBuffer += SHORT_SIZE;
    *pEncodeBuffer = stDCMMsgHead.m_cSecretFlag;

    return 0;
}

/**********************************************************************************/
// ������DeCodeLYDCMMsgHead
// ���ܣ�DCM��Ϣͷ����
// ���룺  pDecodeBuffer           ������
// �����  stDCMMsgHead            ��Ϣͷ
// ����ֵ�� int �ɹ�����0�����򷵻�ʧ��
// ��ע��  
// �޸ļ�¼��
// 2015-10-15         jiangxiaobao                  ����                
/**********************************************************************************/
int DeCodeLYDCMMsgHead(const char* pDecodeBuffer, LYDCMMsgHead& stDCMMsgHead)
{
    if (NULL == pDecodeBuffer)
    {
        return 1;
    }

    stDCMMsgHead.m_cPreFlag[0] = *pDecodeBuffer;
    pDecodeBuffer++;
    if (LY_PACKET_PRE_FLAG_1 != stDCMMsgHead.m_cPreFlag[0])
    {
        return 2;
    }
    stDCMMsgHead.m_cPreFlag[1] = *pDecodeBuffer;
    pDecodeBuffer++;
    if (LY_PACKET_PRE_FLAG_2 != stDCMMsgHead.m_cPreFlag[1])
    {
        return 3;
    }
    stDCMMsgHead.m_uPacketLen = *(unsigned short*)pDecodeBuffer;
    pDecodeBuffer += SHORT_SIZE;
    stDCMMsgHead.m_uVersion = *(unsigned short*)pDecodeBuffer;
    pDecodeBuffer += SHORT_SIZE;
    stDCMMsgHead.m_uMsgID = *(unsigned short*)pDecodeBuffer;
    pDecodeBuffer += SHORT_SIZE;
    stDCMMsgHead.m_cSecretFlag = *pDecodeBuffer;

    return 0;
}

/**********************************************************************************/
// ������EnCodeYZDCMPacketHead
// ���ܣ�DCM��Ϣͷ����
// ���룺stYZPacketHead   ��Ϣͷ
// �����pEnCodeBuffer    ������
// ����ֵ��int �ɹ�����0�����򷵻�ʧ��
// ��ע��   
// �޸ļ�¼��
// 2015-02-04         tangjie                  DCM ״̬���ݹ���              
/**********************************************************************************/
int EnCodeYZDCMPacketHead(const YZDCMPacketHead& stYZPacketHead, char* pEnCodeBuffer)
{
    *pEnCodeBuffer = stYZPacketHead.m_cPreFlag[0];
    pEnCodeBuffer++;
    *pEnCodeBuffer = stYZPacketHead.m_cPreFlag[1];
    pEnCodeBuffer++;
    *(unsigned short*)pEnCodeBuffer = stYZPacketHead.m_uPacketLen;
    pEnCodeBuffer += SHORT_SIZE;
    *(unsigned short*)pEnCodeBuffer = stYZPacketHead.m_uMsgID;
    pEnCodeBuffer += SHORT_SIZE;
    *pEnCodeBuffer = stYZPacketHead.m_cPublicKey;
    return 0;
}

/**********************************************************************************/
// ������DeCodeYZDCMPacketHead
// ���ܣ�DCM��Ϣͷ����
// ���룺pDecodeBuffer    ����
// �����stYZPacketHead   ��Ϣͷ
// ����ֵ��int �ɹ�����0�����򷵻�ʧ��
// ��ע��   
// �޸ļ�¼��
// 2015-02-04         tangjie                  DCM ״̬���ݹ���              
/**********************************************************************************/
int DeCodeYZDCMPacketHead(const char* pDecodeBuffer, YZDCMPacketHead& stYZPacketHead)
{
    stYZPacketHead.m_cPreFlag[0] = *pDecodeBuffer;
    pDecodeBuffer++;
    if (YZ_PACKET_PRE_FLAG_1 != stYZPacketHead.m_cPreFlag[0])
    {
        return 1;
    }
    stYZPacketHead.m_cPreFlag[1] = *pDecodeBuffer;
    pDecodeBuffer++;
    if (YZ_PACKET_PRE_FLAG_2 != stYZPacketHead.m_cPreFlag[1])
    {
        return 2;
    }
    stYZPacketHead.m_uPacketLen = *(unsigned short*)pDecodeBuffer;
    pDecodeBuffer += SHORT_SIZE;
    stYZPacketHead.m_uMsgID = *(unsigned short*)pDecodeBuffer;
    pDecodeBuffer += SHORT_SIZE;
    stYZPacketHead.m_cPublicKey = *pDecodeBuffer;

    return 0;
}

