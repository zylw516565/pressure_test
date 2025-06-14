///@file     CommunicationCommon.h
///@brief    ͨѶ�������Զ���
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

// Tcp �ͻ��� �����������
#define UTIL_TCP_CLIENT_MAX_CONNECT_NUM  1024

// Tcp ����� �����������
#define UTIL_TCP_SERVER_MAX_CONNECT_NUM  1024

// Ĭ�Ϸ��ͻ�������С 64K
#define UTIL_TCP_SEND_BUFFER_SIZE 64 * 1024
// Ĭ�Ͻ��ջ�������С 64K
#define UTIL_TCP_RECV_BUFFER_SIZE 64 * 1024

///@class  TCP_SERVER_OPT [CommunicationCommon.h]
///@brief  Tcp ��������
///@author tangjie
///@note   
enum TCP_SERVER_OPT
{
    TCP_SERVER_OPT_NODELAY,                 // ��ֹ���ͺϲ���Nagle�㷨,0 �� 1 ��
    TCP_SERVER_OPT_SENDBUFSIZE,             // ���ӷ��ͻ�������С
    TCP_SERVER_OPT_RECVBUFSIZE,             // ���ӽ��ջ�������С
};


///@struct st_ConnectRecvData [CommunicationCommon.h]
///@brief  ���ݽ��ջ�����
///@author tangjie
///@note   
typedef struct st_ConnectRecvData 
{
    int                             m_nID;                // ����ID
    void*                           m_pHandle;            // ���ӹ�����
    unsigned int                    m_nLen;               // ���ջ������ܳ���
    unsigned int                    m_nRecvLen;           // �ѽ������ݳ���
    long long                       m_nRecvTime;          // ��������ʱ��
    char*                           m_pData;              // ���ջ�����
}ConnectRecvData;


///@enum   TCP_STATUS [CommunicationCommon.h]
///@brief  Tcp ����״̬
///@author tangjie
///@note   
enum TCP_STATUS
{
    TCP_STATUS_ACCEPT,       // ���������յ� ������
    TCP_STATUS_CONNECT,      // �ͻ����Ѿ����ӵ�������
    TCP_STATUS_CLOSE,        // �ͻ�����������Ͽ�����
    TCP_STATUS_FAIL,         // �ͻ������ӷ�����ʧ��
    TCP_STATUS_DELETE,       // ����ɾ�����ͷ���Դ
};

///TCP�ͻ��˵�����״̬�仯�ص�
///@param [in]    nConnectID       ����ID
///@param [in]    pIp              ���Ӷ�Ӧ�ķ���IP
///@param [in]    nPort            ���Ӷ�Ӧ�ķ���˿�
///@param [in]    nStatus          ����״̬������� TCP_STATUS
///@param [in]    pAddition        ���Ӳ������ɴ�������ʱ����
///return void
///@note  ��Ҫ��֪ͨ�����д������߼������������������ӵĴ���
typedef void (*TcpClientStatus)(int nConnectID, const char* pIp, unsigned short nPort, int nStatus, void* pAddition);

///TCP������������״̬�ص�������accept��close
///@param [in]    nConnectID       ����ID
///@param [in]    pIp              ���Ӷ�Ӧ��IP
///@param [in]    nPort            ���Ӷ�Ӧ�Ķ˿�
///@param [in]    nStatus          ����״̬������� TCP_STATUS
///@param [in]    pAddition        ���Ӳ������ɴ�������ʱ����
///return void
///@note  ��Ҫ��֪ͨ�����д������߼������������������ӵĴ���
typedef void (*TcpServerStatus)(int nConnectID, const char* pIp, unsigned short nPort, int nStatus, void* pAddition);

///@enum   TCP_DATA_TYPE [CommunicationCommon.h]
///@brief  Tcp ���ݴ�������
///@author tangjie
///@note 
enum TCP_DATA_TYPE
{
    TCP_RECV_DATA,           // ���յ�����
    TCP_SEND_SUCC,           // �������ݳɹ�
    TCP_SEND_FAIL,           // ��������ʧ��
};

///TCP�ͻ������ݴ���֪ͨ���������ա��������ݴ���
///@param [in]    nConnectID       ����ID 
///@param [in]    pData            ����ʱΪ���յ������ݣ�����ʱΪ���͵�����
///@param [in]    nDataLen         ����ʱΪ���յ������ݳ��ȣ�����ʱΪ���͵����ݳ���
///@param [in]    nDataType        ���ݴ������ͣ������ TCP_DATA_TYPE
///@param [in]    pAddition        ���Ӳ������ɴ�������ʱ����
///return void
///@note  ��Ҫ��֪ͨ�����д������߼������������������ӵĴ���
typedef void (*TcpClientData)(int nConnectID, const char* pData, int nDataLen, int nDataType, void* pAddition);

///TCP���������ݴ���֪ͨ���������ա��������ݴ���
///@param [in]    nConnectID       ����ID 
///@param [in]    pData            ����ʱΪ���յ������ݣ�����ʱΪ���͵�����
///@param [in]    nDataLen         ����ʱΪ���յ������ݳ��ȣ�����ʱΪ���͵����ݳ���
///@param [in]    nDataType        ���ݴ������ͣ������ TCP_DATA_TYPE
///@param [in]    pAddition        ���Ӳ������ɴ�������ʱ����
///return void
///@note  ��Ҫ��֪ͨ�����д������߼������������������ӵĴ���
typedef void (*TcpServerData)(int nConnectID, const char* pData, int nDataLen, int nDataType, void* pAddition);

// �������ֽ�ת������
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