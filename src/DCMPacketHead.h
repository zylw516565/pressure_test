///@file     DCMPacketHead.h
///@brief    DCM ��Ϣ��
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     

#ifndef DCM_PACKET_HEAD_H
#define DCM_PACKET_HEAD_H

#include <memory.h>
#include <memory>

// DCM ����
#ifndef DCM_TYPE_LY
#define DCM_TYPE_LY     0   //(NET_PACKET_TYPE_LY_TCU)         // �����Զ���Э�� TCU (0)
#endif
#ifndef DCM_TYPE_YZ
#define DCM_TYPE_YZ     1   //(NET_PACKET_TYPE_YZ_OBD)         // Ԫ��OBDЭ�� (1)
#endif


//////////////////////////////////////////////////////////////////////////////////////
// ��������Э�鶨��
// ��Ϣ��ͷβ��ʶ

/*********����Э�����**********/
/*
#define LY_DCM_PACKET_FLAG 0xF5
//ת���õ���ʶ
#define LY_ESCAPE_CHARACTER_FLAG1   0xf4
#define LY_ESCAPE_CHARACTER_FLAG2   0xf5
#define LY_ESCAPE_CHARACTER_FLAG21   0x01
#define LY_ESCAPE_CHARACTER_FLAG22   0x02
// �����Ϣ����
#define MAX_LY_DCM_PACKET_LEN 128
//��Ϣͷ����
#define  LY_DCM_PACKET_HEAD_LEN 13

///�Ƿ�����Э����Ϣ
///@param [in]    pData            ��������
///return bool ����������Э�鷵��true�����򷵻�false
///@note 
inline bool IsLYDCMPacket(const char* pData)
{
    return (LY_DCM_PACKET_FLAG == pData[0]);
}

///@class  LYDCMErrorCode [DCMPacketHead.h]
///@brief  DCM ������
///@author tangjie
///@note   
enum LYDCMErrorCode
{
    LY_DCM_ERROR_OK = 0,                     // �ɹ�/ȷ��
    LY_DCM_ERROR_FAILD = 1,                  // ʧ��
    LY_DCM_ERROR_MSG_ERROR = 2,              // ��Ϣ����
    LY_DCM_ERROR_NOT_SUPPORT = 3,            // ��֧��
};

///@enum   LYDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM ��Ϣ����
///@author tangjie
///@note   
enum LYDCMMSGTYPE
{
    LY_DCM_MSG_DCM_COM_RSP         = 0x0001,                 // ͨ��Ӧ����Ϣ �ն˷��� 
    LY_DCM_MSG_DCM_QUERY_PARAM_RSP = 0x0006,                 // ����Ӧ����Ϣ �ն˷��� 
    LY_DCM_MSG_DCM_DATA_REPORT     = 0x0007,                 // ����������Ϣ���� �ն˷��� 
    LY_DCM_MSG_DCM_QUERY_DATA_RSP  = 0x0008,                 // ��ѯ������ϢӦ�� �ն˷��� 
    LY_DCM_MSG_DCM_DATA_REISSUE    = 0x0009,                 // ���ݲ��� �ն˷��� 

    LY_DCM_MSG_SERVER_COM_RSP      = 0x8001,                 // ͨ��Ӧ����Ϣ ����˷���
    LY_DCM_MSG_SERVER_SET_PARAM    = 0x8005,                 // �����ն˲��� ����˷���
    LY_DCM_MSG_SERVER_QUERY_PARAM  = 0x8006,                 // ��ѯ�ն˲��� ����˷���
    LY_DCM_MSG_SERVER_QUERY_DATA   = 0x8008,                 // ��ѯ������Ϣ ����˷���
};

//�ն�ID����
#define TERMINAL_ID_LEN  6


struct LYDCMMsgHead
{
    unsigned short         m_uMsgId;            //��ϢID
    unsigned short         m_uMsgLen;           //��Ϣ����
    char                   m_sTerminalId[TERMINAL_ID_LEN];       //�ն�ID
    unsigned short         m_uMsgSequenceNum;   //��Ϣ��ˮ��
    unsigned char          m_cPublicKey;        //����

    //���캯��
    LYDCMMsgHead()
    {
        m_uMsgId = 0;
        m_uMsgLen = 0;
        memset(m_sTerminalId, 0, TERMINAL_ID_LEN);
        m_uMsgSequenceNum = 0;
        m_cPublicKey = 1;            // 1 �����������ԿΪ������
    }
};


//DCM��Ϣͷ����
//@param [in]    stDCMMsgHead       ��Ϣͷ
//@param [out]   pEncodeBuffer      ������
//return int �ɹ�����0�����򷵻�ʧ��
//@note  �ⲿ��֤����������ĳ��ȴ��ڵ�����Ϣͷ��
int EnCodeLYDCMMsgHead(const LYDCMMsgHead& stDCMMsgHead, char* pEncodeBuffer);


//DCM��Ϣͷ����
//@param [in]    pDecodeBuffer          ������
//@param [out]   stDCMMsgHead            ��Ϣͷ
//return int �ɹ�����0�����򷵻�ʧ��
//@note  
int DeCodeLYDCMMsgHead(const char* pDecodeBuffer, LYDCMMsgHead& stDCMMsgHead);

//DCM��Ϣͷ������չ
//@param [in]    pszMsg                  ��Ϣ
//@param [out]   stDCMMsgHead            ��Ϣͷ
//return int �ɹ�����0�����򷵻�ʧ��
//@note  
int DeCodeLYDCMMsgHeadEx(const char* pszMsg, unsigned int nMsgLen, LYDCMMsgHead& stDCMMsgHead);
*/

// ��������Э�鶨�壨��20151014��
// ��Ϣ��ͷβ��ʶ
#define LY_PACKET_PRE_FLAG_1 'l'
#define LY_PACKET_PRE_FLAG_2 'y'
#define LY_PACKET_PRE_FLAG_LEN  2

// ֡�ֽڳ���
#define LY_DCM_FRAME_LEN  2 

// ��ͷǰ�ó���
#define LY_PACKET_PRE_LEN (LY_PACKET_PRE_FLAG_LEN + LY_DCM_FRAME_LEN)

// ��ͷ���ȣ���ͷ+֡��+Э��汾(2�ֽ�)+ҵ�����ͣ�2�ֽڣ�+���ܱ�ʶ��1�ֽڣ�
#define LY_PACKET_HEAD_LEN (LY_PACKET_PRE_LEN + 5)

// CRC 16У���볤�� ��2�ֽڣ�
#define LY_PACKET_CRC_LEN 2

// �����򳤶ȣ�2�ֽڣ�
#define LY_PACKET_END_FLAG_LEN 2

// ������
#define LY_PACKET_END_FLAG_1 0xBB
#define LY_PACKET_END_FLAG_2 0x66
//ʱ������ȣ�4�ֽڣ�
#define LY_PACKET_TIME_LEN 4
// ��β���ȣ�ʱ�����4�ֽڣ� + CRC16У���루2�ֽڣ�+ ������2�ֽڣ�
#define LY_PACKET_TAIL_LEN (LY_PACKET_TIME_LEN + LY_PACKET_CRC_LEN + LY_PACKET_END_FLAG_LEN)

// �����Ϣ����
#define MAX_LY_DCM_PACKET_LEN 65535 
// Ĭ����Ϣ����
#define DEFAULT_LY_DCM_PACKET_LEN 256 

// ���ڵ�¼��Сʱ��(��)
#define LIMIT_LOGIN_EXPIRE_MIN 90


///�Ƿ�����Э����Ϣ
///@param [in]    pData            ��������
///return bool ����������Э�鷵��true�����򷵻�false
///@note 
inline bool IsLYDCMPacket(const char* pData)
{
    return (LY_PACKET_PRE_FLAG_1 == pData[0]);
}

///@class  LYDCMErrorCode [DCMPacketHead.h]
///@brief  DCM ������
///@note   
// enum LYDCMErrorCode
// {
//     LY_DCM_ERROR_OK = 0,                     // �ɹ�/ȷ��
//     LY_DCM_ERROR_FAILD = 1,                  // ʧ��
//     LY_DCM_ERROR_MSG_ERROR = 2,              // ��Ϣ����
//     LY_DCM_ERROR_NOT_SUPPORT = 3,            // ��֧��
// };

///@class  LYTBOXErrorCode [DCMPacketHead.h]
///@brief  DCM ������
///@note   
enum LYTBOXErrorCode
{
    LY_TBOX_ERROR_OK                        = 0x00,      // �ɹ�/ȷ��
    LY_TBOX_ERROR_VERSION_ERR               = 0x01,      // Э��汾����
    LY_TBOX_ERROR_BUSINESS_TYPE_ERR         = 0x02,      // ҵ������δ����
    LY_TBOX_ERROR_ENCRYPT_INDISTINGUISHABLE = 0x03,      // ���ܱ�ʶδ��ʶ�� (���ܱ�ʶ���ڶ��巶Χ��)
    LY_TBOX_ERROR_INVALID_DATA              = 0x04,      // ������Ч (ҵ������ݲ����Ϲ�����Ҫ��:��Э���ֶγ��ȴ����)
    LY_TBOX_ERROR_DEVICE_BUSY               = 0x05,      // �豸��æ (���ƽ̨��T-BOX���ڴ�����������,���������Ҫ�ط�)
    LY_TBOX_ERROR_RC4_EXCEPTION             = 0x06,      // RC4�쳣(RC4����/��ʧ/������)
    LY_TBOX_EEROR_NOT_SUPPORT_UPDATE        = 0x07,      // ��֧������
    LY_TBOX_EEROR_CRC16_CHECK_ERR           = 0x08,      // CRCУ�����
    LY_TBOX_ERROR_RSA_EXCEPTION             = 0x09,      // RSA�쳣(RSA����/��ʧ/������)
    LY_TBOX_EEROR_RSA_DECRYPT_ERR           = 0x0A,      // RSA���ܴ��� (����ʧ��/����Դ���Ȳ���)
    LY_TBOX_EEROR_NOT_LOGIN                 = 0x0B,      // δ��¼(δע��(��ŵTBOX))
    LY_TBOX_ERROR_DB_ERROR                  = 0x0C,      // ���ݿ����ʧ��
    LY_TBOX_ERROR_RSA_GEN_FAIL              = 0x0D,      // RSA����ʧ��
	LY_TBOX_ERROR_AES_EXCEPTION             = 0x0E,      // RSA�쳣(RSA����/��ʧ/������)
    LY_TBOX_EEROR_AES_DECRYPT_ERR           = 0x0F,      // RSA���ܴ��� (����ʧ��/����Դ���Ȳ���)

    // TODO: ���´����벻Ӧ����һ���ģ������Ų�����
	LY_TBOX_ERROR_PROTOBUF_PARSE_ERROR = 49,             //protobuf��������
    // ��¼���̴�����***begin***
    LY_TBOX_EEROR_LOGIN_DCMNO_ERR = 50,                  // DCM��Ŵ���(�����ɼ��ַ�)
    LY_TBOX_EEROR_LOGIN_MSG_LEN_ERR = 51,                // ��Ϣ���ȴ���
    LY_TBOX_EEROR_NISSAN_LOGIN_4CODE_ERR = 52,           // ����У�����
    LY_TBOX_EEROR_LOGIN_VIN_ERR = 53,                    // VIN�����(�����ɼ��ַ�)
    LY_TBOX_EEROR_LOGIN_DASN_ERR = 54,                   // DASN����(�����ɼ��ַ�)
    LY_TBOX_EEROR_LOGIN_ICCID_ERR = 55,                  // ICCID����(�����ɼ��ַ�)
    LY_TBOX_EEROR_LOGIN_EXPIRE_REQ = 56,                 // ���ڵ�¼����(TCU��¼ʱ����ϵ�ǰʱ��̫��)
    LY_TBOX_EEROR_LOGIN_INVALID_CERT = 57,               // ֤���ѵ���
    // ��¼���̴�����***end***

    // ����RC4���̴�����***begin***
    LY_TBOX_EEROR_RSA_DISENABLE = 60,                      // RSAû�յ���Ӧ
    LY_TBOX_EEROR_RC4_LEN_ERR  = 61,                       // RC4���Ȳ�ƥ��
    LY_TBOX_EEROR_RC4_TOO_LONG = 62,                       // RC4���ȳ�����Χ
    LY_TBOX_EEROR_RC4_CRC_ERR  = 63,                       // RSA���ܺ������CRCУ�����
    // ����RC4���̴�����***end***
    
    // ���ݰ����̴�����***begin***
    LY_TBOX_EEROR_PACK_PACK_CRC_ERR = 70,                  // �����ڵ�CRCУ�����
    LY_TBOX_EEROR_PACK_FORWORD_ERR = 71,                   // ת��ʧ��
    // ���ݰ����̴�����***end***

    // ��������״̬������***begin***
    LY_TBOX_EEROR_BLUETOOTH_FORWORD_ERR = 50,             // ת��ʧ��
    // ��������״̬������***end***

    // ����Χ������������***begin***
    LY_TBOX_EEROR_FENCEALERT_FORWORD_ERR = 50,             // ����Χ������ ת��ʧ��
    // ����Χ������������***end***

    // Rena Register������***begin***
    LY_TBOX_EEROR_RENA_REGISTER_DCMNO_ERR = 50,             // DCM��Ŵ���
    // Rena Register������***end***

    // Rena Data ������***begin***
    LY_TBOX_ERROR_RENA_DATA_PACK_ERR = 50,                        // �ְ�����
    LY_TBOX_EEROR_RENA_DATA_PACK_INDEX_ERR = 51,                  // �ְ���Ŵ���
    LY_TBOX_EEROR_RENA_DATA_PACK_LEN_ERR = 52,                    // �ְ����ȴ���
    // Rena Data������***end***

    // T-BOX����EBD״̬(0x040E)������***begin***
    LY_TBOX_EEROR_EBD_STA_EBDNO_ERR = 50,               // DCMΪ�ջ��߸�ʽ����
    LY_TBOX_EEROR_EBD_STA_VIN_ERR = 51,                 // VIN��Ϊ�ջ��߸�ʽ����
    // T-BOX����EBD״̬(0x040E)������***end***

};

// TBOX�� (TBOX����ŵTCU���ղ�TCU) Э��汾

// ֧�ֵİ汾��
enum SUPPORT_TBOX_VERSION
{
    VERSION_TBOX_NUMBER_NULL               = 0x0200,        // �汾NULL  ���ڿ�ʼλ�ñȽ�
    VERSION_TBOX_NUMBER_1                  = 0x0201,        // �汾1
    VERSION_TBOX_NUMBER_2                  = 0x0202,        // �汾2
    VERSION_TBOX_NUMBER_3                  = 0x0203,        // �汾3
    VERSION_TBOX_NUMBER_4                  = 0x0204,        // �汾4
    VERSION_TBOX_NUMBER_MAX,                                // ֧�ְ汾���ֵ
};

// ��ŵ֧�ֵİ汾
enum SUPPORT_RENAULT_VERSION
{
    VERSION_RENAULT_NUMBER_NULL               = 0x0300,         // �汾NULL  ���ڿ�ʼλ�ñȽ�
    VERSION_RENAULT_NUMBER_1                  = 0x0301,         // �汾1
    VERSION_RENAULT_NUMBER_2                  = 0x0302,         // �汾2
    VERSION_RENAULT_NUMBER_3                  = 0x0303,         // �汾3
    VERSION_RENAULT_NUMBER_4                  = 0x0304,         // �汾4
    VERSION_RENAULT_NUMBER_MAX,                                 // ֧�ְ汾���ֵ
};

// ���⳵֧�ֵİ汾
enum SUPPORT_EASYCAR_VERSION
{
    VERSION_EASYCAR_NUMBER_NULL               = 0x0400,         // �汾NULL  ���ڿ�ʼλ�ñȽ�
    VERSION_EASYCAR_NUMBER_1                  = 0x0401,         // �汾1
    VERSION_EASYCAR_NUMBER_MAX,                                 // ֧�ְ汾���ֵ
};

// �ղ�TCU֧�ֵİ汾
enum SUPPORT_NISSANTBOX_VERSION
{
	VERSION_NISSANTBOX_NUMBER_NULL               = 0x0500,         // �汾NULL  ���ڿ�ʼλ�ñȽ�
	VERSION_NISSANTBOX_NUMBER_01                 = 0x0501,         // �汾01 531��322
	VERSION_NISSANTBOX_NUMBER_02                 = 0x0502,         //��ŵhje�汾Э��
	VERSION_NISSANTBOX_NUMBER_10                 = 0x0510,         // �汾10   PDI
	VERSION_NISSANTBOX_NUMBER_11				 = 0x0511,         // �汾20   PDI
	VERSION_NISSANTBOX_NUMBER_MAX,                                 // ֧�ְ汾���ֵ
};

///@enum   LYDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM ��Ϣ����
///@author jiangxiaob
///@note   
enum LYDCMMSGTYPE
{
    LY_DCM_MSG_TBOX_LOGIN_REQ         = 0x0001,                 // ��¼���� �ն˷���
    LY_DCM_MSG_TBOX_RENA_REGISTER_REQ = 0x0002,                 // T-BOX�����˷���ע�����󣨼���TCU��
    LY_DCM_MSG_TBOX_RENA_LOGOUT_REQ   = 0x007F,                 // T-BOX�����˷��͵ǳ�����
    LY_DCM_MSG_TBOX_HEARTBEAT_REQ     = 0x0101,                 // �������� �ն˷���     
    LY_DCM_MSG_TBOX_RSA_KEY_RSP       = 0x0201,                 // Զ��RSA��Կ����
    LY_DCM_MSG_TBOX_RC4_KEY           = 0x0202,                 // Զ��RC4��Կ����
    LY_DCM_MSG_TBOX_AUTH_UPDATE       = 0x0301,                 // ��Ȩ����
    LY_DCM_MSG_TBOX_CONFIGURE_RSP     = 0x0401,                 // ������Ϣ �ն˷��� 
    LY_DCM_MSG_TBOX_DATA_PACK         = 0x0402,                 // ������� �ն˷��� 
    LY_DCM_MSG_TBOX_UPDATE_REQ        = 0x0403,                 // T-BOX����ƽ̨��������汾��Ϣ
    LY_DCM_MSG_TBOX_UPDATE_DATA       = 0x0404,                 // T-BOX������������
    LY_DCM_MSG_TBOX_UPDATE_CHECK      = 0x0405,                 // T-BOX�����˷����������У����
    LY_DCM_MSG_TBOX_BLUETOOTH_CNT_STA = 0x0406,                 // T-BOX�����˷����ֻ�����״̬
    LY_DCM_MSG_TBOX_ELEC_FENCE_RSP    = 0x0407,                 // T-BOX��Ӧ����Χ������
    LY_DCM_MSG_TBOX_ELEC_FENCE_ALERT  = 0x0408,                 // T-BOX�ϴ�����Χ������
    LY_DCM_MSG_TBOX_RENA_DATA_ALERT   = 0x0409,                 // T-BOX�����˷������ݺͱ���
    LY_DCM_MSG_TBOX_DEL_ELEC_FENCE_RSP = 0x040A,                // T-BOX��Ӧɾ������Χ������
    LY_DCM_MSG_TBOX_EMER_RESCUE_REQ   = 0x040B,                 // T-BOX���ͽ�����Ԯ����
    LY_DCM_MSG_TBOX_SET_PARAM_RSP     = 0x040C,                 // T-BOX��Ӧ����˲�������
    LY_DCM_MSG_TBOX_CONTROL_RSP       = 0x040D,                 // T-BOX��Ӧ����˿�������
    LY_DCM_MSG_TBOX_EBD_ON_OFF_LINE   = 0x040E,                 // EBD���ߺ�����֪ͨ

	LY_DCM_MSG_NISSAN_TBOX_LOGIN_REQ  = 0x0601,                 // NISSAN-T-BOX����ƽ̨����ע������
    LY_DCM_MSG_NISSAN_TBOX_RSA_LOGIN_REQ = 0x0602,              // NISSAN-T-BOX����ƽ̨����ע������(Ҫ�󷵻�RSA��Կ)
    LY_DCM_MSG_NISSAN_TBOX_RC4_KEY_REQ       = 0x0603,              // NISSAN-T-BOXԶ��RC4��Կ����
	LY_DCM_MSG_NISSAN_TBOX_HEARTBEAT_REQ     = 0x0701,                 // NISSAN-T-BOX�������� �ն˷���
	LY_DCM_MSG_NISSAN_TBOX_RSA_KEY_RSP       = 0x0801,                 // NISSAN-T-BOX�յ�Զ��RSA��Կ������ƽ̨Ӧ�� Զ��RSA��Կ����
	LY_DCM_MSG_NISSAN_TBOX_RC4_KEY           = 0x0802,                 // NISSAN T-BOX����ƽ̨����Զ��RC4��Կ Զ��RC4��Կ����
	LY_DCM_MSG_NISSAN_TBOX_AUTH_UPDATE       = 0x0901,                 // NISSAN T-BOX����ƽ̨������¼�Ȩ�� ��Ȩ����
	LY_DCM_MSG_NISSAN_TBOX_CONFIGURE_RSP     = 0x0A01,                 // NISSAN T-BOX��Ӧ���ƽ̨���������� ������Ϣ �ն˷���
	LY_DCM_MSG_NISSAN_TBOX_QUERYINFO_RSP     = 0x0A02,                 // NISSAN T-BOX��Ӧ���ƽ̨�Ĳ�ѯ��Ϣ���� �ն˷���
	LY_DCM_MSG_NISSAN_TBOX_DATA              = 0x0A03,                 // NISSAN T-BOX����ƽ̨������������
    LY_DCM_MSG_NISSAN_TBOX_DATA_NEW          = 0x0B03,                 // NISSAN T-BOX����ƽ̨������������(�°汾��Э��)
	LY_DCM_MSG_NISSAN_TBOX_GPS               = 0x0A04,                 // NISSAN T-BOX����ƽ̨����GPS����
	LY_DCM_MSG_NISSAN_TBOX_ALERT             = 0x0A05,          // NISSAN T-BOX����ƽ̨���ͱ�������
	LY_DCM_MSG_NISSAN_TBOX_CONTROL_RSP       = 0x0A06,          // NISSAN T-BOX��Ӧ���ƽ̨�ĳ�����������
    LY_DCM_MSG_NISSAN_TBOX_RMTDIAG_RSP       = 0x0A09,          // T-BOX����ƽ̨���͹��ϼ��Ӧ��
    LY_DCM_MSG_NISSAN_TBOX_WAKEUPDVR_RSP     = 0x0A0A,          // T-BOX����ƽ̨����DVR����Ӧ��
    LY_DCM_MSG_NISSAN_TBOX_FAULTLIST_REQ     = 0x0A10,          // T-BOX����ƽ̨�ϴ�֧�ֵĹ����嵥

    //�⼸��ID����
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_VERSION    = 0x0403,                 // NISSAN T-BOX���������汾��Ϣ
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_DATA       = 0x0404,                 // NISSAN T-BOX��������������
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_CHECK      = 0x0405,                 // NISSAN T-BOX�ϴ�����״̬

	//LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_START_REQ = 0x0B01,             // NISSAN T-BOX����ƽ̨������������֪ͨ
	LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_CANCEL_REQ = 0x0C02,            // NISSAN T-BOX����ƽ̨����ȡ��TCU������Ӧ 0x0C02
	LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_PROGRESS_REQ = 0x0C03,          // NISSAN T-BOX����ƽ̨������������ 0x0C03

    LY_DCM_MSG_SERVER_LOGIN_RSP       = 0x8001,                 // ��¼��Ӧ ����˷���
    LY_DCM_MSG_SERVER_RENA_REGISTER_RSP = 0x8002,                 // �������Ӧע�����󣨼���TCU��
    LY_DCM_MSG_SERVER_RENA_LOGOUT_RSP = 0x807F,                 // �������Ӧ�ǳ�����
    LY_DCM_MSG_SERVER_HEARTBEAT_RSP   = 0x8101,                 // ������Ӧ ����˷���    
    LY_DCM_MSG_SERVER_RSA_KEY         = 0x8201,                 // Զ��RSA��Կ����
    LY_DCM_MSG_SERVER_RC4_KEY         = 0x8202,                 // Զ��RC4��Կ����
    LY_DCM_MSG_SERVER_AUTH_UPDATE     = 0x8301,                 // ��Ȩ����
    LY_DCM_MSG_SERVER_CONFIGURE       = 0x8401,                 // ������Ϣ ����˷���
    LY_DCM_MSG_SERVER_DATA_PACK       = 0x8402,                 // ������� ����˷���
    LY_DCM_MSG_SERVER_UPDATE_CMD      = 0x8403,                 // ���ƽ̨��T-BOX�����������Ӧ��
    LY_DCM_MSG_SERVER_UPDATE_DATA     = 0x8404,                  // ���ƽ̨��ӦT-BOX��������
    LY_DCM_MSG_SERVER_UPDATE_CHECK    = 0x8405,                 // ����˶�У������Ӧ��
    LY_DCM_MSG_SERVER_BLUETOOTH_CNT_STA = 0x8406,               // ������յ��ֻ�����״̬���Ӧ��
    LY_DCM_MSG_SERVER_ELEC_FENCE      = 0x8407,                 // ��������T-BOX���͵���Χ������
    LY_DCM_MSG_SERVER_ELEC_FENCE_ALERT_RSP  = 0x8408,           // �������յ�����Χ��Ԥ����Ӧ��
    LY_DCM_MSG_SERVER_RENA_DATA_ALERT_RSP   = 0x8409,           // ������յ����ݺͱ������Ӧ�𣨼���TCU��
    LY_DCM_MSG_SERVER_DEL_ELEC_FENCE    = 0x840A,               // �������T-BOX����ɾ������Χ������
    LY_DCM_MSG_SERVER_EMER_RESCUE_RSP   = 0x840B,               // �������ӦT-BOX������Ԯ����
    LY_DCM_MSG_SERVER_SET_PARAM_RSP     = 0x840C,               // �������T-BOX�·�������������
    LY_DCM_MSG_SERVER_CONTROL_RSP       = 0x840D,               // �������T-BOX�·���������
    LY_DCM_MSG_SERVER_EBD_ON_OFF_LINE   = 0x840E,                // EBD���ߺ�����֪ͨ
    LY_DCM_MSG_SERVER_QUERY_PARAM       = 0x840F,               // �������T-BOX�·�������ѯ����

    LY_DCM_MSG_SERVER_NISSAN_LOGIN_RSP       = 0x8601,           // NISSAN T-BOX��¼��Ӧ ����˷���
    LY_DCM_MSG_SERVER_NISSAN_RSA_LOGIN_RSP   = 0x8602,           // NISSAN T-BOX��¼��Ӧ ����˷���(����RSA��Կ)
    LY_DCM_MSG_SERVER_NISSAN_RC4_KEY_RSP     = 0x8603,           // NISSAN ���ƽ̨�յ�Զ��RC4��Կ����T-BOXӦ�� Զ��RC4��Կ����
    LY_DCM_MSG_SERVER_NISSAN_HEARTBEAT_RSP   = 0x8701,           // NISSAN T-BOX������Ӧ ����˷��� 
    //LY_DCM_MSG_SERVER_NISSAN_RSA_KEY         = 0x8801,           // NISSAN ���ƽ̨��T-BOX����Զ��RSA��Կ Զ��RSA��Կ����
    //LY_DCM_MSG_SERVER_NISSAN_RC4_KEY         = 0x8802,           // NISSAN ���ƽ̨�յ�Զ��RC4��Կ����T-BOXӦ�� Զ��RC4��Կ����
    //LY_DCM_MSG_SERVER_NISSAN_AUTH_UPDATE     = 0x8901,           // NISSAN ���ƽ̨��Ӧ���¼�Ȩ������ ��Ȩ����
    LY_DCM_MSG_SERVER_NISSAN_CONFIGURE       = 0x8A01,           // NISSAN ���ƽ̨��T-BOX���в������� ������Ϣ ����˷���
    LY_DCM_MSG_SERVER_NISSAN_QUERYINFO       = 0x8A02,           // NISSAN ���ƽ̨��ѯT-BOX��Ϣ ������Ϣ ����˷���
    //LY_DCM_MSG_SERVER_NISSAN_DATA_RSP        = 0x8A03,           // NISSAN ���ƽ̨�յ��������ݺ��Ӧ��
    LY_DCM_MSG_SERVER_NISSAN_DATA_RSP_NEW    = 0x8B03,           // NISSAN ���ƽ̨�յ��������ݺ��Ӧ��(�°汾��Э��)
    LY_DCM_MSG_SERVER_NISSAN_GPS_RSP         = 0x8A04,           // NISSAN ���ƽ̨�յ�GPS���ݺ��Ӧ��
    LY_DCM_MSG_SERVER_NISSAN_ALERT_RSP       = 0x8A05,           // NISSAN ���ƽ̨�յ��������ݺ��Ӧ��
    LY_DCM_MSG_SERVER_NISSAN_CONTROL         = 0x8A06,           // NISSAN ���ƽ̨������������
    LY_DCM_MSG_SERVER_NISSAN_NETWORKALARM_RSP = 0x8A07,          // NISSAN ���ƽ̨��������ͳ��
    LY_DCM_MSG_SERVER_NISSAN_RMTDIAG           = 0x8A09,         // NISSAN ���ƽ̨����Զ���������
    LY_DCM_MSG_SERVER_NISSAN_WAKEUPDVR         = 0x8A0A,         // NISSAN ���ƽ̨����DVR��������
    LY_DCM_MSG_SERVER_NISSAN_FAULTLIST_RSP     = 0x8A10,         // NISSAN ���ƽ̨��T-BOX���͹����嵥��Ӧ

    /*��ŵHJE����������ϢID begin ymj20181122*/    
    LY_DCM_MSG_RENAULT_TBOX_DATA             = 0x0B04,           // ��ŵhje T-BOX����ƽ̨������������
    LY_DCM_MSG_SERVER_RENAULT_DATA_RSP       = 0x8B04,           // ��ŵhje ���ƽ̨�յ��������ݺ��Ӧ��
    LY_DCM_MSG_DIAGNOSIS_REQ          = 0x8A0E, //��ŵhje ���ƽ̨��T-BOX�����������
	LY_DCM_MSG_DIAGNOSIS_RSP          = 0x0A0E, //��ŵhje T-BOX����ƽ̨�������Ӧ��
    /*��ŵHJE����������ϢID end ymj20181122*/
    
    //�⼸��ID����
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_VERSION  = 0x8403,           // NISSAN ���ƽ̨����������Ϣ(������ַ)    
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_DATA     = 0x8404,           // NISSAN ���ƽ̨������������Ϣ
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_CHECK    = 0x8405,           // NISSAN ���ƽ̨��������״̬��Ӧ

    LY_DCM_MSG_SERVER_NISSAN_UPDATEFILECONTROL_REQ = 0x8C01,     // NISSAN ���ƽ̨��T-BOX����������������
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPDATEFILECONTROL_RSP = 0x0C01,   // NISSAN T-BOX����ƽ̨��������������Ӧ
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_START_RSP = 0x8B01,       // ���ƽ̨��Ӧ��������֪ͨ
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_CANCEL_RSP = 0x8C02,      // ���ƽ̨��T-BOX����ȡ��TCU�������� 0x8C02
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_PROGRESS_RSP = 0x8C03,    // ���ƽ̨��T-BOX��������������Ӧ 0x8C03
    LY_DCM_MSG_TBOX_4G_EXTEND_CMD_RSP = LY_DCM_MSG_DIAGNOSIS_RSP,           // ���ƽ̨�·���չ����Ӧ�𣨺�����Կ�׹��ܣ�
    LY_DCM_MSG_TBOX_4G_EXTEND_CMD_REQ = LY_DCM_MSG_DIAGNOSIS_REQ,           // ���ƽ̨�·���չ�������󣨺�����Կ�׹��ܣ�
    LY_DCM_MSG_TBOX_TCU_EXTEND_CMD_RSP = 0x8A0F,          // ���ƽ̨��T-BOX������չ����Ӧ��
    LY_DCM_MSG_TBOX_TCU_EXTEND_CMD_REQ = 0x0A0F,          // T-BOX������չ��������

	//֤���������
	LY_DCM_MSG_CERTIFICATE_STATUS_REQ = 0x0D01,			//T-BOX���̨����֤������/�ϱ�֤��״̬����
	LY_DCM_MSG_CERTIFICATE_STATUS_RSP = 0x8D01,			//���ƽ̨�յ�֤�������Ӧ��
	LY_DCM_MSG_CERTIFICATE_DELIEVR_REQ = 0x8D02,	    //���ƽ̨�·�֤�鵽T-BOX
	LY_DCM_MSG_CERTIFICATE_DELIEVR_RSP = 0x0D02,			//T-BOX�յ����ƽ̨�·�֤�����ݵ���Ӧ

    LY_DCM_MSG_NISSAN_TBOX_GET_VIN_REQ = 0x0E01,        // ��ŵ T-BOX����ƽ̨���ͻ�ȡVIN���� 0x0D01
    LY_DCM_MSG_NISSAN_TBOX_GET_VIN_RSP = 0x8E01,        // ��ŵ T-BOX����ƽ̨���ͻ�ȡVINӦ�� 0x0D01
    LY_DCM_MSG_NISSAN_TBOX_WRITE_VIN_REQ = 0x0E02,      // ��ŵ T-BOX����ƽ̨����VIN��д��������� 0x0D02
    LY_DCM_MSG_NISSAN_TBOX_WRITE_VIN_RSP = 0x8E02,      // ��ŵ T-BOX����ƽ̨����VIN��д�����Ӧ�� 0x0D02

    //�����û���̬Э�� begin
    LY_DCM_MSG_DYNAMIC_DATA_UPLOAD_REQ   = 0x0CA0,      //T-BOX��ƽ̨���Ϳ����û�������������
    LY_DCM_MSG_DYNAMIC_DATA_UPLOAD_RSP   = 0x8CA0,      //T-BOX��ƽ̨���Ϳ����û����������յ�����Ӧ
    LY_DCM_MSG_TCU_UPGRADE_DICT_REQ      = 0x8CA1,      //ƽ̨֪ͨTCU���������ֵ�����
    LY_DCM_MSG_TCU_UPGRADE_DICT_RSP      = 0x0CA1,      //TCU��ƽ̨�ظ����������ֵ�����Ӧ
    LY_DCM_MSG_TCU_UPLOAD_DICTIONARY_REQ = 0x0CA2,      //TCU����ʱ,��ƽ̨�ϴ������ֵ�����
    LY_DCM_MSG_TCU_UPLOAD_DICTIONARY_RSP = 0x8CA2,      //TCU����ʱ,��ƽ̨�ϴ������ֵ���Ӧ
    //�����û���̬Э�� end
};

///@struct LYDCMMsgHead [DCMPacketHead.h]
///@brief  LY DCM ��Ϣͷ
///@note   
struct LYDCMMsgHead
{
    char                                m_cPreFlag[LY_PACKET_PRE_FLAG_LEN]; // ǰ�ò��֣���ͷǰ�ñ�־��ly
    unsigned short                      m_uPacketLen;                       // ������
    unsigned short                      m_uVersion;                         // Э��汾
    unsigned short                      m_uMsgID;                           // ҵ��ID 
    unsigned char                       m_cSecretFlag;                      // ���ܱ�ʶ

    ///���캯��
    ///return
    LYDCMMsgHead()
    {
        m_cPreFlag[0] = LY_PACKET_PRE_FLAG_1;
        m_cPreFlag[1] = LY_PACKET_PRE_FLAG_2;
        m_uPacketLen = 0;
        m_uVersion = VERSION_TBOX_NUMBER_1;   // Ĭ��Ϊ�汾1
        m_cSecretFlag = 0;            // ��ʼΪ������
    }
};

typedef std::shared_ptr<LYDCMMsgHead> LYDCMMsgHeadPtr;

//DCM��Ϣͷ����
//@param [in]    LYDCMPacketHead       ��Ϣͷ
//@param [out]   pEncodeBuffer      ������
//return int �ɹ�����0�����򷵻�ʧ��
//@note  �ⲿ��֤����������ĳ��ȴ��ڵ�����Ϣͷ��
int EnCodeLYDCMMsgHead(const LYDCMMsgHead& stDCMMsgHead, char* pEncodeBuffer);


//DCM��Ϣͷ����
//@param [in]    pDecodeBuffer          ������
//@param [out]   stDCMMsgHead            ��Ϣͷ
//return int �ɹ�����0�����򷵻�ʧ��
//@note  
int DeCodeLYDCMMsgHead(const char* pDecodeBuffer, LYDCMMsgHead& stDCMMsgHead);



//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// Ԫ��Э�鶨��
// ��ͷǰ׺
#define YZ_PACKET_PRE_FLAG_1 'L'
#define YZ_PACKET_PRE_FLAG_2 'Y'
#define YZ_PACKET_PRE_FLAG_LEN  2

// ֡�ֽڳ���
#define YZ_DCM_FRAME_LEN  2 

// ��ͷǰ�ó���
#define YZ_PACKET_PRE_LEN (YZ_PACKET_PRE_FLAG_LEN + YZ_DCM_FRAME_LEN)

// ��ͷ���ȣ���ͷ+֡��+ҵ��ID��2�ֽڣ�+��Կ��1�ֽڣ�
#define YZ_PACKET_HEAD_LEN (YZ_PACKET_PRE_LEN + 3)

// CRC 16У���볤�� ��2�ֽڣ�
#define YZ_PACKET_CRC_LEN 2

// Ԫ��ʱ���
#define YZ_PACKE_TIME_LEN 4

// ��β���ȣ�ʱ�����4�ֽڣ� + CRC16У���루2�ֽڣ�
#define YZ_PACKET_TAIL_LEN (4 + YZ_PACKET_CRC_LEN)

// �����Ϣ����
#define MAX_YZ_DCM_PACKET_LEN 1024 
// Ĭ����Ϣ����
#define DEFAULT_YZ_DCM_PACKET_LEN 256 

///@enum   YZDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM ��Ϣ����
///@author tangjie
///@note   
enum YZDCMMSGTYPE
{
    YZ_DCM_MSG_DCM_HEARTBEAT_REQ   = 0x0001,                 // �������� �ն˷��� 
    YZ_DCM_MSG_DCM_LOGIN_REQ       = 0x0002,                 // ��¼���� �ն˷��� 
    YZ_DCM_MSG_DCM_DATA_GPS        = 0x0003,                 // GPS���� �ն˷��� 
    YZ_DCM_MSG_DCM_DATA_FLOW       = 0x0004,                 // ������ �ն˷��� 
    YZ_DCM_MSG_DCM_FAULT_REPORT    = 0x0005,                 // �����ϱ� �ն˷��� 
    YZ_DCM_MSG_DCM_CONFIGURE       = 0x0006,                 // ������Ϣ �ն˷��� 
    YZ_DCM_MSG_DCM_PUSH            = 0x0007,                 // ������Ϣ �ն˷��� 
    YZ_DCM_MSG_DCM_DATA_TRIP       = 0x0008,                 // �г�ͳ����Ϣ �ն˷��� 
    YZ_DCM_MSG_DCM_DATA_PACK       = 0x0009,                 // ������� �ն˷��� 
    YZ_DCM_MSG_DCM_ALERT_UP        = 0x000A,                 // �澯�ϱ���澯���
    YZ_DCM_MSG_DCM_VIN_UP          = 0x000B,                 // �ϴ�VIN��

    YZ_DCM_MSG_SERVER_HEARTBEAT_RSP= 0x1001,                 // ������Ӧ ����˷���
    YZ_DCM_MSG_SERVER_LOGIN_RSP    = 0x1002,                 // ��¼��Ӧ ����˷���
    YZ_DCM_MSG_SERVER_FAULT_RSP    = 0x1005,                 // ������������Ӧ ����˷���
    YZ_DCM_MSG_SERVER_CONFIGURE    = 0x1006,                 // ������Ϣ ����˷���
    YZ_DCM_MSG_SERVER_PUSH         = 0x1007,                 // ������Ϣ ����˷���
    YZ_DCM_MSG_SERVER_DATA_TRIP    = 0x1008,                 // �г�ͳ����Ϣ ����˷���
    YZ_DCM_MSG_SERVER_DATA_PACK    = 0x1009,                 // ������� ����˷���
    YZ_DCM_MSG_SERVER_ALERT_RSP    = 0x100A,                 // �澯�ϱ���Ӧ ����˷���
    YZ_DCM_MSG_SERVER_VIN_UP       = 0x100B,                 // �ϴ�VIN����Ӧ ����˷���
};

///@struct YZDCMPacketHead [DCMPacketHead.h]
///@brief  YZ DCM ��Ϣͷ
///@author tangjie
///@note   
struct YZDCMPacketHead
{
    char                                m_cPreFlag[YZ_PACKET_PRE_FLAG_LEN]; // ǰ�ò��֣���ͷǰ�ñ�־��LY
    unsigned short                      m_uPacketLen;                       // ������
    unsigned short                      m_uMsgID;                           // ҵ��ID 
    unsigned char                       m_cPublicKey;                       // ����

    ///���캯��
    ///return
    YZDCMPacketHead()
    {
        m_cPreFlag[0] = YZ_PACKET_PRE_FLAG_1;
        m_cPreFlag[1] = YZ_PACKET_PRE_FLAG_2;
        m_uPacketLen = 0;
        m_cPublicKey = 1;            // 1 �����������ԿΪ������
    }
};


///�Ƿ�Ԫ��Э����Ϣ  "LY" 0x4C 0x59
///@param [in]    pData            ��������
///return bool ��Ԫ��Э�鷵��true�����򷵻�false
///@note 
inline bool IsYZDCMPacket(const char* pData)
{
    return (YZ_PACKET_PRE_FLAG_1 == pData[0]);
}

///DCM��Ϣͷ����
///@param [in]    stYZPacketHead   ��Ϣͷ
///@param [out]   pEnCodeBuffer    ������
///return int �ɹ�����0�����򷵻�ʧ��
///@note  
int EnCodeYZDCMPacketHead(const YZDCMPacketHead& stYZPacketHead, char* pEnCodeBuffer);

///DCM��Ϣͷ����
///@param [in]    pDecodeBuffer    ����
///@param [out]   stYZPacketHead   ��Ϣͷ
///return int �ɹ�����0�����򷵻�ʧ��
///@note  
int DeCodeYZDCMPacketHead(const char* pDecodeBuffer, YZDCMPacketHead& stYZPacketHead);


//////////////////////////////////////////////////////////////////////////////////////

#endif  /*DCM_PACKET_HEAD_H*/
