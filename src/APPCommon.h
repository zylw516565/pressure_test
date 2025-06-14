///@file     APPCommon.h
///@brief    App ��������(�ڲ�����ͨѶ��Ϣ����)
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     

#ifndef APP_COMMON_H
#define APP_COMMON_H

///@enum   MSG_PROTOCOL [APPCommon.h]
///@brief  ��ϢЭ������
///@author tangjie
///@note   
enum MSG_PROTOCOL
{
    MSG_PROTOCOL_APP                    = 0,    // APP ��ϢЭ��
    MSG_PROTOCOL_DCM                    = 1,    // DCM ��ϢЭ��
    MSG_PROTOCOL_CMPP                   = 2,
    MSG_PROTOCOL_ATBOX                  = 3,
};

///@class  SERVER_TYPE [APPCommon.h]
///@brief  ��������
///@author tangjie
///@note   
enum SERVER_TYPE
{
    SERVER_TYPE_MANAGER             = 1,        // �������
    SERVER_TYPE_APP_ROUTER          = 2,        // APP ·�ɷ���
    SERVER_TYPE_DCM_ROUTER          = 3,        // DCM ·�ɷ���
    SERVER_TYPE_APP_BUSINESS        = 4,        // APP ҵ�����
    SERVER_TYPE_DCM_BUSINESS        = 5,        // DCM ҵ�����
    //SERVER_TYPE_APP_CACHE         = 6,        // APP �������
    //SERVER_TYPE_DCM_CACHE         = 7,        // DCM �������
    SERVER_TYPE_UNICOM_SMS          = 8,        // ��ͨ���ŷ���
    SERVER_TYPE_HTTP_CLIENT         = 9,        // Http���ͷ���
    SERVER_TYPE_TQBOX_ROUTER        = 10,       // TQBox ·�ɷ���
    SERVER_TYPE_DATA_REPORT_CONTROL = 11,       // �����ϴ����Ʒ���
    SERVER_TYPE_CARWINGS_CGUARD     = 12,       // Carwings cguard ����
    SERVER_TYPE_CARWINGS_08IT       = 13,       // Carwings 08IT ����
    SERVER_TYPE_CARWINGS_CGUARD_ROUTE = 14,     // Carwings CGuard��������
    SERVER_TYPE_CARWINGS_08IT_ROUTE = 15,       // Carwings 08IT��������

    SERVER_TYPE_VEH_DPS_SUB         = 19,       // DCMҵ�����-�������ݴ������ ��ֳ����ӷ���

    SERVER_TYPE_ATBOX_DCM_ROUTER    = 23,       // ATBox��Ŀ DCM�������ݵ�·�ɷ���
    SERVER_TYPE_ATBOX_APP_BUSINESS  = 24,       // ATBox��Ŀ APP�������ݵ�ҵ�����
    SERVER_TYPE_ATBOX_DCM_BUSINESS  = 25,       // ATBox��Ŀ DCM�������ݵ�ҵ�����
    SERVER_TYPE_NISSAN_ATBOX        = 26,       // �ղ�ATBox��Ŀ

    SERVER_TYPE_VSTK                = 31,       // Vstk����ǩ����ǩ
    SERVER_TYPE_BTK                 = 32,       // Btk����֤���ȡ
	SERVER_TYPE_CERT_DOWNLOAD_ROUTE = 33,	    // ֤�����ؽ������

    SERVER_TYPE_EV_GB_DEAL          = 40,       // GB���ݴ���
    // 41-45 Ԥ�����������ݴ���
    SERVER_TYPE_EV_GB_SEND          = 46,       // GB���ʹ���

    SERVER_TYPE_EV_EV_CUSTOM_DEAL   = 60,       // EV�Զ������ݴ���
    // 61-65 Ԥ����EV�Զ������ݴ���
    
    SERVER_TYPE_DCVP_NGTP_DCM_ROUTER          = 120, // DCVP��Ŀ NGTPЭ�� DCM�������ݵ�·�ɷ���
    SERVER_TYPE_DCVP_GBVI_DCM_ROUTER          = 121, // DCVP��Ŀ ����Э�� DCM�������ݵ�·�ɷ���
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 131, // DCVP��Ŀ NGTPЭ�� DCM���ƽ���������
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 132, // DCVP��Ŀ NGTPЭ�� DCM�������ݴ������
    SERVER_TYPE_DCVP_GBVI_DCM_REQ_VEH_DATA    = 133, // DCVP��Ŀ ����Э�� DCM���ݴ������
    SERVER_TYPE_DCVP_NGTP_DCM_DATA_POSTER     = 141, // DCVP��Ŀ NGTPЭ�� DCM�������ͷ���
    SERVER_TYPE_DCVP_GBVI_DCM_DATA_RELAY      = 142, // DCVP��Ŀ ����Э�� DCM����ת������
    SERVER_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CTRL = 151, // DCVP��Ŀ NGTPЭ�� APPԶ�̿��Ʒ���
    SERVER_TYPE_DCVP_NGTP_APP_REQ_SMS_SENDER  = 152, // DCVP��Ŀ NGTPЭ�� DCM���ŷ���
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_SELF_ADMIN  = 153, // DCVP��Ŀ NGTPЭ�� ������滻
 
    SERVER_TYPE_TIMER_MANAGER = 209,                 // ��ʱ������ (IOV-TaskTimerModule)

    SERVER_TYPE_TRIP_FIX = 210,                      // �г̼�ʱ�������� (IOV-TripFixModule)
    SERVER_TYPE_ICCID_CHECK = 211,                   // ICCID ��Ч����֤���� (IOV-IccidCheck)

    SERVER_TYPE_OBU_DCM_ROUTER = 192,                  // �Զ���ʻ�ƶ�obu�Ľ���
    SERVER_TYPE_OBU_DCM_REQ_VEH_DATA = 193,            // �Զ���ʻ�ƶ�obu���������ݷ���
    SERVER_TYPE_OBU_DCM_REQ_CTRAL_DOWN = 194,          // �Զ���ʻ�ƶ�obu��Զ���·�����
    SERVER_TYPE_OBU_CAN_DCM_ROUTER = 196,              // �Զ���ʻ�ƶ�obu��can����ת������
	
	SERVER_TYPE_V2X_OBU_DS = 215,						// V2X OBU�������
	SERVER_TYPE_V2X_RSU_DS = 216,						// V2X RSU�������
	SERVER_TYPE_V2X_OBU_NETWORK = 217,					// V2X OBU�������ݷ���
	SERVER_TYPE_V2X_OBU_BSM = 218,						// V2X OBU�������ݷ���
	SERVER_TYPE_V2X_OBU_SCENES = 219,					// V2X OBU�������ݷ���
	SERVER_TYPE_V2X_RSU_DATA = 220,						// V2X RSU���ݷ���
	SERVER_TYPE_V2X_EVENT_ISSUED = 221,					// V2X �¼��·�����
	SERVER_TYPE_V2X_DATA_INTERFACE = 222,				// V2X ���ݽӿڷ���
    SERVER_TYPE_V2X_FORWARD_DATA_REPORT = 223,          // V2X ת�������ϱ�����


    SERVER_TYPE_NADD_VEH_DATA = 225,                    // �ղ����г���װTBOX��������(IOV-NAddVehModule) 
    SERVER_TYPE_NADD_DS = 226,                          // �ղ����г���װTBOX�������(IOV-NAddDSModule) 
    SERVER_TYPE_NADD_VIS = 227,                         // �ղ����г���װTBOX��Ϣ��ѯ����(IOV-NAddVISModule) 
    SERVER_TYPE_NADD_L3_INTERFACE = 228,                // �ղ����г���װTBOX L3�ӿڷ���(IOV-NAddL3InterfaceModule) 
	SERVER_TYPE_NADD_REMOTE_CONTROL = 229,              // �ղ����г���װTBOXԶ�ط���(IOV-NAddRCSModule) 
	SERVER_TYPE_NADD_SMS = 230,                         // �ղ����г���װTBOX���ŷ���(IOV-NAddSMSModule) 

    SERVER_TYPE_L2BU_BOOTSTRAP_API = 250,               // L2 Backup bootstrap API ����
    SERVER_TYPE_L2BU_PUSH_CENTER = 251,                 // L2 Backup �������ķ���
    SERVER_TYPE_L2BU_ALARM_PUSH = 252,                  // L2 Backup �澯����
    SERVER_TYPE_L2BU_DS = 253,                          // L2 Backup �������
    SERVER_TYPE_L2BU_REMOTE_CTRL = 254,                 // L2 Backup Զ�̿��Ʒ���
    SERVER_TYPE_L2BU_API_GATE_WAY = 255,                // L2 Backup API���ط���
};

///@class  MESSAGE_TYPE [APPCommon.h]
///@brief  ��Ϣ����
///@author tangjie
///@note   
enum MESSAGE_TYPE
{
    MESSAGE_TYPE_SERVER_STATUS          = 1,        // ����״̬��Ϣ,�ڲ���Ϣ(ManagerServer)
    //MESSAGE_TYPE_USER_STATUS          = 11,       // �û�״̬��Ϣ����,�ڲ���Ϣ
    MESSAGE_TYPE_DCM_STATUS             = 12,       // DCM ״̬��Ϣ����,�ڲ���Ϣ
    MESSAGE_TYPE_DCM_DATA               = 13,       // DCM ������Ϣ,�ڲ���Ϣ(����)
    MESSAGE_TYPE_DCM_CONFIGURE          = 14,       // DCM ������Ϣ(IOV-DS)
    MESSAGE_TYPE_APP_ROUTER             = 15,       // APP Router���յ��ڲ���Ϣ(Business-DS)
    MESSAGE_TYPE_UBI_DATA_DEAL          = 16,       // UBI���ݴ������(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_DCM_UPDATE             = 17,       // DCM��������(�Ѳ�ʹ��)
    MESSAGE_TYPE_TQBOX_CONFIGURE        = 18,       // TQBox������Ϣ,�ڲ���Ϣ(TQBOX-DS)
    MESSAGE_TYPE_GB_CONFIGURE           = 19,       // �����豸������Ϣ(IOV-GBDS)
    MESSAGE_TYPE_TLS_CONFIGURE          = 20,       // 532PKI�������(IOV-PKIDS)
    MESSAGE_TYPE_GBCYCLE_CONFIGURE      = 21,       // vNext�������(IOV-GBCycleDS)
    MESSAGE_TYPE_GBTLS_CONFIGURE        = 22,       // �����豸PKI�������(IOV-TLSGBDS)

    MESSAGE_TYPE_NISSAN_TBOX_VEHICLE_DATA = 30,     // TCU �������ݴ������(IOV-VehicleDPS)
    MESSAGE_TYPE_NISSAN_TBOX_GPS_DATA   = 31,       // TCU GPS���ݴ������(IOV-GPSDPS)
    MESSAGE_TYPE_NISSAN_TBOX_ALARM_DATA = 32,       // TCU �������ݴ������(IOV-AlarmPushAP)
    MESSAGE_TYPE_KEY_GENERATE           = 34,       // ��Կ���ɷ���(KeyGenerate)
    
    MESSAGE_TYPE_GB_DATAMAG             = 35,       // �������ݴ�������(IOV-GBDataMag)
    MESSAGE_TYPE_GB_DATADEAL_DEF        = 40,       // �������ݴ������Ĭ����ϢID(IOV-GBDataDeal)
    // 41-45 Ԥ�����������ݴ������������
    MESSAGE_TYPE_GB_DATADEAL_MAX        = 45,       // �������ݴ�����������ϢID(IOV-GBDataDeal)
    MESSAGE_TYPE_GB_DATASEND            = 46,       // �������ݷ��ͷ���(IOV-GBDataSend)
 
    MESSAGE_TYPE_ATBOX_CAN_DATA         = 51,       // ATBox CAN����
    MESSAGE_TYPE_ATBOX_GPS_DATA         = 52,       // ATBox GPS����
    MESSAGE_TYPE_AT_CONFIGURE           = 53,       // ATBox DS��Ϣ
    MESSAGE_TYPE_RENAULT_CAN_DATA       = 54,       // ATBox ��ŵHJE CAN���� ymj20181203
    MESSAGE_TYPE_RENAULT_GPS_DATA       = 55,       // ATBox ��ŵHJE GPS���� ymj20181203
    MESSAGE_TYPE_NISSAN_CT_VEH_DATA     = 56,       // ATBox Nissan(����TCU) �������� Johnson 20181217
    MESSAGE_TYPE_NISSAN_CT_GPS_DATA     = 57,       // ATBox Nissan(����TCU) GPS���� Johnson 20181217

    MESSAGE_TYPE_EV_CUSTOM_DEF          = 60,       // EV �Զ������ݴ������Ĭ��(IOV-EVCustomDeal)
    // 61-65 Ԥ����EV�Զ������ݴ������������
    MESSAGE_TYPE_EV_CUSTOM_MAX          = 65,       // EV �Զ������ݴ��������ϢID(IOV-EVCustomDeal)
    MESSAGE_TYPE_DYNAMIC_VEHIC          = 66,       // ��̬Э����������

    MESSAGE_TYPE_USER_LOG               = 101,      // �û���֤(��ƽ̨,�Ѳ�ʹ��)
    //MESSAGE_TYPE_USER_MANAGER         = 102,      // �û�����(��ƽ̨,�Ѳ�ʹ��)
    //MESSAGE_TYPE_MSG_MANAGER          = 103,      // ��Ϣ����(��ƽ̨,�Ѳ�ʹ��)
    //MESSAGE_TYPE_SYS_MANAGER          = 104,      // ϵͳ����(��ƽ̨,�Ѳ�ʹ��)
    //MESSAGE_TYPE_DCM_MANAGER          = 105,      // DCM ����(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_MSG_PUSH               = 106,      // ��Ϣ����(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_TBOX                   = 107,      // TBOX(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_QUERY_BREAK_RULES      = 108,      // ��ѯΥ��(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_EV_MANAGER             = 110,      // EV�ǻ۳��ܼҽӿ�(��ƽ̨,�Ѳ�ʹ��)
    MESSAGE_TYPE_TRIAL_RUN              = 111,      // �Գ��Լܷ���(��ƽ̨,�Ѳ�ʹ��)
    
    MESSAGE_TYPE_UNICOM_SMS             = 112,      // ��ͨ���ŷ���(IOV-UniSms)
    MESSAGE_TYPE_HTTP_CLIENT            = 113,      // Http���ͷ���(IOV-HttpClient)

    MESSAGE_TYPE_VEH_TRIP               = 119,      // �г̷�������(IOV-VehTrip)
    MESSAGE_TYPE_VEH_ALERT              = 120,      // ����������(IOV-VehAlert)
    MESSAGE_TYPE_GPS_EFENCE             = 121,      // ����Χ������(IOV-GPSEFence)

    MESSAGE_TYPE_REMOTE_CONTROL         = 200,      // Զ�̿��Ʒ���(IOV-RCS)
    MESSAGE_TYPE_VEHICLE_INFO           = 201,      // ������Ϣ�������(IOV-VIS)
    MESSAGE_TYPE_DEVICE_MANAGER         = 202,      // �豸�������(IOV-DevMangerS)

    MESSAGE_TYPE_ATBOX_MANAGER          = 203,      // ATBox��Ϣ�������(IOV-ATVIS)

    MESSAGE_TYPE_GB_MANAGER             = 204,      // ������Ϣ�������(IOV-GBVIS)
    MESSAGE_TYPE_FACTORYQC_MANAGER      = 205,      // �����ʼ촦�����(IOV-FactoryQC)

    MESSAGE_TYPE_DCVP_GBVI_DS                  = 121, // DCVP��Ŀ ����Э�� �����ڲ���Ϣ:�����������
    MESSAGE_TYPE_DCVP_GBEV_DS                  = 122, // DCVP��Ŀ ����EVЭ�� �����ڲ���Ϣ:EV�������

    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 131, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ����ƽ��
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 132, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ���������
    MESSAGE_TYPE_DCVP_GBVI_DATA_DEAL           = 133, // DCVP��Ŀ ����Э�� �����ڲ���Ϣ:�������ݴ���
    MESSAGE_TYPE_DCVP_GBEV_DATA_DEAL           = 134, // DCVP��Ŀ ����EVЭ�� �����ڲ���Ϣ: EV���ݴ���
    MESSAGE_TYPE_DCVP_NGTP_DCM_DATA_POSTER     = 141, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�������ͷ���
    MESSAGE_TYPE_DCVP_GBVI_DATA_SEND           = 142, // DCVP��Ŀ ����Э�� �����ڲ���Ϣ:��������ת������
    MESSAGE_TYPE_DCVP_GBEV_DATA_SEND           = 143, // DCVP��Ŀ ����EVЭ�� �����ڲ���Ϣ:EV����ת������
    MESSAGE_TYPE_DCVP_GBEV_PARAM_CTRL          = 144, // DCVP��Ŀ ����EVЭ�� �����ڲ���Ϣ:EV��������

    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CTRL                  = 151, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:APP����Զ�̿���
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_SMS_SENDER                   = 152, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:APP������ŷ���
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_SELF_ADMIN                   = 153, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:������滻 
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CONFIG                = 154, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:Զ�����÷���
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_REMOTE_CONFIG_RESULT         = 155, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:Զ�����ý������
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_SOFTWARE_UPGRADE             = 156, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:������·���
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_SOFTWARE_UPGRADE_RESULT      = 157, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:������½������

    //ymj 20191011
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_BLE          = 160, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:����Կ��֪ͨ����
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_BLE_RESULT   = 161, // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:����Կ�׽������
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_LOG         = 162,  // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:��־����֪ͨ����

    MESSAGE_TYPE_DCVP_EVH_DCM_REQ_CUSTOM_VEH_DATA   = 178,      // DCVP H97�Զ�����������

    //ymj 20200319
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_CAN          = 179, //DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:����������֪ͨ����
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CAN_RESULT   = 180, //DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:���������ؽ������    
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CAN_INFO     = 181, //DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:�����������쳣��Ϣ����
    MESSAGE_TYPE_DCVP_EVH_DCM_REQ_CUSTOM_VEH_ABNORMAL_DATA  = 182,  //DCVP H97�����쳣�澯��Ϣ����
    MESSAGE_TYPE_DCVP_NGTP_DCM_CREDIT   = 185,  //DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:���ų���Ϣ����   
    MESSAGE_TYPE_DCVP_NGTP_DCM_CREDIT_SMS   = 186,  //DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:���ų������·�����

    //ymj 20200723,���Զ���ʻ�ƶ�ƽ̨��
    MESSAGE_TYPE_RSE_DS = 188,              //�Զ���ʻ�ƶ�rse�Ľ���
    MESSAGE_TYPE_RSE_DATE = 189,            //�Զ���ʻ�ƶ�rse�Ĳɼ����ݴ���ģ��(����)
    MESSAGE_TYPE_RSE_CTRL = 190,            //�Զ���ʻ�ƶ�rse��Զ�̿��Ʒ���
    MESSAGE_TYPE_OBU_DCM_ROUTER = 192,                  // �Զ���ʻ�ƶ�obu�Ľ���
    MESSAGE_TYPE_OBU_DCM_REQ_VEH_DATA = 193,            // �Զ���ʻ�ƶ�obu���������ݷ���
    MESSAGE_TYPE_OBU_DCM_REQ_CTRAL_DOWN = 194,          // �Զ���ʻ�ƶ�obu��Զ���·�����
    MESSAGE_TYPE_OBU_CAN_DCM_ROUTER = 196,              // �Զ���ʻ�ƶ�obu��can����ת������

    MESSAGE_TYPE_VSTK_MANAGER                  = 206, // Vstkǩ������IOV-VSTK����
    MESSAGE_TYPE_BTK_MANAGER                   = 207, // Btkǩ������IOV-BTK����
    MESSAGE_TYPE_VEHICLE_STATE                 = 208, // ����״̬��ѯ����(IOV-VSS)
    MESSAGE_TYPE_TIMER_MANAGER                 = 209, // ��ʱ������ (IOV-TaskTimerModule)
    MESSAGE_TYPE_VEHICLE_INFO_MYSQL            = 210, // ����״̬��ѯ����(IOV-VRS)
    MESSAGE_TYPE_NAVSTK_MANAGER                = 211, // NAVstkǩ������IOV-NAVSTK����
    MESSAGE_TYPE_NABTK_MANAGER                 = 212, // NABtkǩ������IOV-NABTK����

    MESSAGE_TYPE_TRIP_FIX = 213,    // �г̼�ʱ�������� (IOV-TripFixModule)
    MESSAGE_TYPE_ICCID_CHECK = 214, // ICCID ��Ч����֤���� (IOV-IccidCheck)
	
    MESSAGE_TYPE_V2X_OBU_DS = 215,						// V2X OBU�������
	MESSAGE_TYPE_V2X_RSU_DS = 216,						// V2X RSU�������
	MESSAGE_TYPE_V2X_OBU_NETWORK = 217,					// V2X OBU�������ݷ���
	MESSAGE_TYPE_V2X_OBU_BSM = 218,						// V2X OBU�������ݷ���
	MESSAGE_TYPE_V2X_OBU_SCENES = 219,					// V2X OBU�������ݷ���
	MESSAGE_TYPE_V2X_RSU_DATA = 220,					// V2X RSU���ݷ���
	MESSAGE_TYPE_V2X_EVENT_ISSUED = 221,				// V2X �¼��·�����
	MESSAGE_TYPE_V2X_DATA_INTERFACE = 222,				// V2X ���ݽӿڷ���
    MESSAGE_TYPE_V2X_FORWARD_DATA_REPORT = 223,         // V2X ת�������ϱ�����

    MESSAGE_TYPE_NADD_VEH_DATA = 225,                   // �ղ����г���װTBOX��������(IOV-NAddVehModule) 
    MESSAGE_TYPE_NADD_DS = 226,                         // �ղ����г���װTBOX�������(IOV-NAddDSModule) 
    MESSAGE_TYPE_NADD_VIS = 227,                        // �ղ����г���װTBOX��Ϣ��ѯ����(IOV-NAddVISModule) 
    MESSAGE_TYPE_NADD_L3_INTERFACE = 228,               // �ղ����г���װTBOX L3�ӿڷ���(IOV-NAddL3InterfaceModule) 
	MESSAGE_TYPE_NADD_REMOTE_CONTROL = 229,             // �ղ����г���װTBOXԶ�ط���(IOV-NAddRCSModule) 
    MESSAGE_TYPE_NADD_SMS = 230,                        // �ղ����г���װTBOX���ŷ���(IOV-NAddSMSModule) 

    MESSAGE_TYPE_L2BU_BOOTSTRAP_API = 250,              // L2 Backup bootstrap API ����
    MESSAGE_TYPE_L2BU_PUSH_CENTER = 251,                // L2 Backup �������ķ���
    MESSAGE_TYPE_L2BU_ALARM_PUSH = 252,                 // L2 Backup �澯����
    MESSAGE_TYPE_L2BU_DS = 253,                         // L2 Backup �������
    MESSAGE_TYPE_L2BU_REMOTE_CTRL = 254,                // L2 Backup Զ�̿��Ʒ���
    MESSAGE_TYPE_L2BU_API_GATE_WAY = 255,               // L2 Backup API���ط���
};

// ��Ϣ���ܺŶ�Ӧ����Ӧ��Ϣ����һλΪ1
#define MESSAGE_FUNCTION_TYPE_RSP_MARK 0x8000
#define MESSAGE_FUNCTION_TYPE_RSP_UNMARK 0x7FFF

///@class  MESSAGE_FUNCTION_TYPE [APPCommon.h]
///@brief  ��Ϣ���ܺ�
///@author tangjie
///@note   �����ֽڣ����λΪ1��ʾ��Ӧ��Ϣ
enum MESSAGE_FUNCTION_TYPE
{
    FUNCTION_TYPE_SERVER_STATUS = 1,                         // ����״̬��Ϣ���ڲ���Ϣ
    //DCM_Cache***BEGIN*** 
    FUNCTION_TYPE_DCM_CACHE_UPDATE    = 1,                   // DCM ���»�������
    FUNCTION_TYPE_DCM_CACHE_QUERY_RANK = 3,                  // ��ѯDCM ��������
    //DCM_Cache***END*** 
    //DCM_Data***BEGIN*** 
    FUNCTION_TYPE_LY_DCM_DATA_REPORT_REQ = 1,                // DCM �����ϱ�����
    FUNCTION_TYPE_YZ_DCM_DATA_REPORT_REQ = 2,                // DCM �����ϱ�����
    FUNCTION_TYPE_DCM_DATA_OFFLINE       = 3,                // DCM ����֪ͨ
    FUNCTION_TYPE_BLUETOOTH_STATE        = 4,                // ����״̬
    FUNCTION_TYPE_FENCE_ALERT            = 5,                // ����Χ��Ԥ��
    FUNCTION_TYPE_YZ_DCMTRIAL_DATA_REQ   = 6,                // �Գ��Լ� DCM �����ϱ�����
    //DCM_Data***END*** 
    //IOV-DS***BEGIN*** 
    FUNCTION_TYPE_DCM_CONFIGURE_REQ = 1,                     // DCM �����·����� 
    FUNCTION_TYPE_GET_AUTH_KEY_REQ = 2,                      // ��ȡ��Ȩ��
    FUNCTION_TYPE_DCM_ELECFENCE_REQ = 3,                     // DCM ����Χ���·�����
    FUNCTION_TYPE_DCM_NETWORKALARM_REQ = 4,                  // DCM �����澯�·�����
    FUNCTION_TYPE_DCM_UPDATECONTROL_REQ = 5,                 // DCM���������·�����
    FUNCTION_TYPE_DCM_UPDATECANCEL_REQ = 6,                  // DCM����ȡ���·�����
    FUNCTION_TYPE_DCM_DVR_REQ = 7,                           // TCU DVR ��������
    FUNCTION_TYPE_DCM_RMTDIAG_REQ = 8,                       // TCU ���ϼ������
    FUNCTION_TYPE_DCM_REMOTE_CTRL_REQ = 9,                   // ��ǩ���ķ�������
    FUNCTION_TYPE_SPECDCM_INFOEX = 10,                       // ���⳵����չ��Ϣ֪ͨ
    FUNCTION_TYPE_DCM_PKI_UPDATECTRL_REQ = 11,               // ��ǩ��DCM���������·�����
    FUNCTION_TYPE_DCM_BACK_UP_REQ = 12,                      // Back up�·�����
    //IOV-DS***END*** 
    FUNCTION_TYPE_TCU_FORCEOFFLINE_REQ = 999,                //DS�����õ�TCUǿ����������
    //User_Log***BEGIN*** 
    FUNCTION_TYPE_USER_GET_CHECK_RAND = 101,                  // ��ȡУ�������
    //User_Log***END*** 
    //SYS_MANAGER***BEGIN*** Add by jiangxiaobao   2015-01-15
    FUNCTION_TYPE_QUERY_LAST_VERSION     = 4,                         //�汾���²�ѯ
    FUNCTION_TYPE_FEED_BACK_IDEA         = 5,                         //�������
    FUNCTION_TYPE_QUERY_OIL_PRICE        = 7,                         //�ͼ۲�ѯ
    FUNCTION_TYPE_ADD_ACT_LOG            = 8,                         //��¼APP��־
    FUNCTION_TYPE_GET_FUNCTION_LABEL     = 9,                         //��ȡ���ܱ�ǩ�ӿ�
    FUNCTION_TYPE_GET_USER_TRAFFIC       = 10,                        //��ȡ�����ӿ�
    FUNCTION_TYPE_GET_EMGCY_RESCUE_INFO  = 16,                        //��ȡ������Ԯ��Ϣ
    //SYS_MANAGER***END***
    //DCM_Status***BEGIN*** 
    FUNCTION_TYPE_DCM_CONFIGURE = 3,                            // DCM ��������
    FUNCTION_TYPE_GET_AUTH_KEY = 5,                             // ��ȡ��Ȩ��
    FUNCTION_TYPE_GET_TRIAL_RUN_LOCATION = 6,                   // ��ȡ�Գ��Լݵ�����
    //DCM_Status***END*** 
    // MSG_PUSH_SERVER***BEGIN***
    FUNCTION_TYPE_MSG_PUSH_USER_INFO = 1,                       // ��Ϣ�����û���Ϣ
    FUNCTION_TYPE_MSG_PUSH_TO_SINGLE_DEVICE = 100,              // ���͵������豸����Ϣ
    FUNCTION_TYPE_MSG_PUSH_COMMON_MSG = 200,                    // ��Ϣ����ͨ����Ϣ
    // MSG_PUSH_SERVER***END***
    // TBOX_SERVER***BEGIN***
    FUNCTION_TYPE_SET_LOCATION_SHARING_INFO = 1,                // λ�ù�����Ϣ
    FUNCTION_TYPE_GET_LOCATION_SHARING_INFO = 2,                // ��ȡλ�ù�����Ϣ
    FUNCTION_TYPE_IGITION_INFO              = 3,                // �����Ϣ
    FUNCTION_TYPE_GET_LOCATION_INFO         = 5,                // ��ȡλ����Ϣ
    FUNCTION_TYPE_GET_LOCATION_BYORDER      = 6,                // �����Ż�ȡλ����Ϣ
    FUNCTION_TYPE_SET_UNLOCK_ALERT          = 9,                // ����δ�������ѿ���
    FUNCTION_TYPE_GET_UNLOCK_ALERT          = 10,               // ��ȡδ�������ѿ���״̬
    // TBOX_SERVER***END*** 

    //BackupVehic***START***  ��̬��������
    FUNCTION_TYPE_LY_DYNAMIC_DATA_REPORT_REQ = 1,               // ��̬Э�����������ϱ�����
    //BackupVehic***End***  ��̬��������

    // QUERY_BREAK_RULES_SERVER***BEGIN*** 
    FUNCTION_TYPE_GET_USER_BREAK_RULES = 1,                // ��ѯΥ��
    // QUERY_BREAK_RULES_SERVER***END*** 


    // DCM �������� ***BEGIN***
    FUNCTION_TYPE_DCM_UPDATE_MSG    = 1,                    //DCM ��������
    // DCM �������� ***END***

    //Key Generate***START***  ��Կ���ɽӿ�
    FUNCTION_TYPE_GET_RSAKEY            = 1,        // ��ȡRSA��Կ
    //Key Generate***End***  ��Կ���ɽӿ�

    //NISSAN_TBOX_Data***BEGIN*** 
    FUNC113_TYPE_VEHICLE_DATA_REPORT_REQ = 1,                // ��������
    FUNC113_TYPE_GPS_DATA_REPORT_REQ = 2,                    // GPS����
    FUNC113_TYPE_ALARM_DATA_REPORT_REQ = 3,                  // ��������
    FUNC113_TYPE_TBOX_GPS_REPORT_REQ = 4,                    // TBOX GPS����(Ϊ�˵���Χ�����)
    FUNC113_TYPE_GB_GPS_REPORT_REQ = 5,                      // ����GPS����(Ϊ�˵���Χ�����)
    FUNC113_TYPE_VEH_TRIP_DATA_REQ = 101,                    // ��������-�г��������
    FUNC113_TYPE_VEH_ALERT_DATA_REQ = 102,                   // ��������-�����������
    FUNC113_TYPE_GPS_EFENCE_DATA_REQ = 103,                  // GPS����-����Χ���������
                                                             //NISSAN_TBOX_Data***END*** 

    // remote control server ***start***
    FUNC200_TYPE_CALL_BACK              = 1,                  // �ص���Ϣ
    FUNC200_TYPE_REMOTE_CONTROL         = 2,                  // Զ�̿���
    FUNC200_TYPE_REMOTE_AWAKEN          = 3,                  // Զ�̻���
    FUNC200_TYPE_CYCLE_PARAM            = 4,                  // ������������
    FUNC200_TYPE_SAFETY_PROTECTION      = 5,                  // ��ȫ����
    FUNC200_TYPE_QUERY_ALARMINFO        = 6,                  // ��ѯ�쳣����
    FUNC200_TYPE_QUERY_UPGRADECANCEL    = 7,                  // ����ȡ��(����)
    FUNC200_TYPE_EV_PARAM_AND_CTRL      = 8,                  // EV�綯���Ĳ�����д�Ϳ���(TCU��ص����úͿ���)
    FUNC200_TYPE_CALL_BACK_GET          = 9,                  // �ص���Ϣ��ȡ
    FUNC200_TYPE_WAKEUPDVR              = 10,                 // TCU DVR �������� 
    FUNC200_TYPE_RMTDIAG                = 11,                 // TCU ���ϼ������
    FUNC200_TYPE_RMTDIAG_RESULT         = 12,                 // TCU ���ϼ���� (�Ӻ󷵻ص�)
    FUNC200_TYPE_EVCAR_REMOTE_CONTROL   = 13,                 // EV��������(������ؿ���)
    FUNC200_TYPE_VIRTUAL_KEY            = 14,                 // ����Կ��
    FUNC200_TYPE_HJE_RMTDIAG            = 15,                 // HJEԶ�����
    FUNC200_TYPE_HJE_RMTDIAG_RESULT     = 16,                 // HJEԶ����Ͻ������(�Ӻ󷵻ص�)
    FUNC200_TYPE_CT_COMMAND             = 17,                 // �ղ�ATBox�����·�
	FUNC200_TYPE_HEV_REMOTE_CONTROL		= 18,                 // ����HEV��������
    // remote control server ***end***

    // �ղ����г���װTBOXԶ�ط��� ***start***
    FUNC229_TYPE_MSG_GET_PARAM           = 1,                   // ��ѯ����
    FUNC229_TYPE_MSG_CTRL                = 2,                   // Զ������
    FUNC229_TYPE_MSG_CTRL_RESULT_REPORT  = 3,                   // Զ�ؽ���ϱ�

    // �ղ����г���װTBOXԶ�ط��� ***end***

    // �ղ����г���װTBOX�������� ***start***
    FUNC225_TYPE_MSG_BROADCAST_REQ       = 1,                   // �����ϴ�����(Peps�㲥)
    FUNC225_TYPE_L3_SET_PUSH_STATUS      = 2,                   // L3������Ҫ���ͳ���״̬���ݵ�tbox
    // �ղ����г���װTBOX�������� ***end***

    // �ղ����г���װTBOX������� ***start***
    FUNC226_TYPE_MSG_REMOTE_CTRL       = 1,                     // ��������
    // �ղ����г���װTBOX������� ***end***

    // �ղ����г���װTBOX NAddVIS���� ***start***
    FUNC227_TYPE_GET_CAR_DATA_REQ       = 1,                    // ��ȡ������������
    // �ղ����г���װTBOX NAddVIS���� ***end***

    // �ղ����г���װTBOX NAddSMS���� ***start***
    FUNC_NADD_TYPE_SHORT_MESSAGE_REQ     = 1,                    // ���Ͷ�������
    // �ղ����г���װTBOX NAddSMS���� ***end***

    // vehicle information server ***start***
    FUNC201_TYPE_VEHICLE_DATA_QUERY      = 1,               // �������ݲ�ѯ
    FUNC201_TYPE_GPS_DATA_QUERY          = 2,               // GPS���ݲ�ѯ
    FUNC201_TYPE_DRIVE_SCORE             = 3,               // ��ȡ��ʻ����
    FUNC201_TYPE_SET_ELEC_FENCE          = 4,               // ���õ���Χ��
    FUNC201_TYPE_GET_ELEC_FENCE          = 5,               // ��ȡ����Χ��
    FUNC201_TYPE_GET_GREEN_TRAVEL        = 6,               // ��ȡ��ɫ������Ϣ
    FUNC201_TYPE_GET_DRIVING_TRACK       = 7,               // ��ȡ��ʻ��Ϊ�켣�ķ�������
    FUNC201_TYPE_GET_ONLINE_COUNT         = 8,               // ����������������ͳ��
    FUNC201_TYPE_GET_VEHICLE_STATUS         = 9,               // �������޳���״̬��ȡ
    FUNC201_TYPE_GET_VEHICLE_TRACK_HISTORY         = 10,      // �������޳�����ʷ�켣��ȡ
    FUNC201_TYPE_GET_PARKING_HISTORY     = 11,              // ��������ͣ����¼��ѯ
    FUNC201_TYPE_DEL_DRIVING_TRACK       = 12,              // ɾ����ʻ��Ϊ�켣�ļ�¼
    FUNC201_TYPE_GET_EV_STATUS_BOARD     = 13,              // ��ȡEV�綯��״̬
    FUNC201_TYPE_GET_EV_DETAIL_DATA      = 14,              // ��ȡEV�綯����ϸʵʱ����
    FUNC201_TYPE_GET_EV_CONST_PARAM      = 15,              // ��ȡEV�綯���̶�ֵ����(��ŵ)
    FUNC201_TYPE_GET_EV_NISSAN_CONSTA    = 16,              // ��ȡEV�綯���̶�ֵ(�ղ�)
    FUNC201_TYPE_GET_EV_NISSAN_DATA      = 17,              // ��ȡEV�綯������������(�ղ�)
    FUNC201_TYPE_GET_EV_UPDATE_STATUS    = 18,              // ��ȡEV�綯������״̬
    FUNC201_TYPE_QRY_MALFUNCTION         = 19,              // ��ѯ��������
    FUNC201_TYPE_GET_TRACK_POS           = 20,              // ��ȡ��ʻ�г̹켣�ĳ�������
    FUNC201_TYPE_GET_START_POS           = 21,              // ��ȡ���(���ʱ)����
    FUNC201_TYPE_GET_PARKING_POS         = 22,              // ��ȡͣ��(����30����)����
    FUNC201_TYPE_GET_EGT_CONST           = 23,              // ��ȡeGT�����̶�ֵ
    FUNC201_TYPE_GET_EGT_CARDATA         = 24,              // ��ȡeGT������������
    FUNC201_TYPE_GET_EV_DIAGNOSIS        = 25,              // ��ȡEV �������   
    FUNC201_TYPE_GET_EVCC_DATA           = 26,              // ��ȡEVCC(����)�Զ���(����)����
    FUNC201_TYPE_SET_TCUBLACKLIST        = 27,              // ���÷�����TCU������
    FUNC201_TYPE_GET_TCUBLACKLIST        = 28,              // ��ȡ������TCU������
    FUNC201_TYPE_GET_EV_VENUCIA_CONST   = 29,              // ��ȡ����EV�����̶�ֵ
    FUNC201_TYPE_GET_EV_VENUCIA_CARDATA = 30,              // ��ȡ����EV������������
    FUNC201_TYPE_GET_VEHICLEREAL_STATUS = 31,              // ���ڷ�ػ�ȡ����ʵʱ״̬
    FUNC201_TYPE_GET_VEHICLEREAL_POS    = 32,              // ���ڷ�ػ�ȡ�����켣
    FUNC201_TYPE_GET_HISTORY_POSITION   = 33,              // ���ڷ�ػ�ȡ������ʷ��λ
    FUNC201_TYPE_SET_FINCEVECHICLE_DATA = 34,              // ���ڷ�����ó�����Ϣ
    FUNC201_TYPE_GET_FINCEONLINE_COUNT  = 35,              // ���ڷ�ػ�ȡ����������
    FUNC201_TYPE_GET_RANGE_VEHICLE      = 36,              // ���ڷ�ػ�ȡ��Χ�ڳ���
    FUNC201_TYPE_GET_GBDATAUPLOADSTATUS = 37,              // ����ƽ̨���ͽ����ѯ  
    FUNC201_TYPE_SET_ROUTEINFO          = 38,              // ��ɾ���������Ϣ  
    FUNC201_TYPE_GET_FORWARD_INFO       = 39,              // ��ȡ����ת����Ϣ
	FUNC201_TYPE_GET_HEV_VEHICLESTATUS  = 40,              // ��ȡ����HEV����״̬
    // vehicle information server ***end***               

    // device manager server  ***start***
    FUNC202_TYPE_DEVICE_CANCEL                 = 1,         // �豸ע��
    FUNC202_TYPE_DEVICE_CHANGE                   = 2,         // �豸����
    FUNC202_TYPE_DEVICE_FOURCODESYNC           = 3,         // ������Ϣͬ��
    FUNC202_TYPE_DEVICE_UPDATEINFOSYNC         = 4,         // ������Ϣͬ��
    FUNC202_TYPE_DEVICE_NETWORKALARM           = 5,         // �����澯
    FUNC202_TYPE_DEVICE_UPDATECONTROL          = 6,         // ��������
    FUNC202_TYPE_DEVICE_GET_BLACKWHITELIST     = 7,         // ��ѯ�ڰ�����
    FUNC202_TYPE_DEVICE_SET_BLACKWHITELIST     = 8,         // ��ɾ�ڰ�����
    FUNC202_TYPE_DEVICE_UPDATECANCEL           = 9,         // ����ȡ��
    FUNC202_TYPE_DEVICE_GPS_UP_INTERVAL        = 10,        // ��������GPS�ϴ�Ƶ������
    FUNC202_TYPE_DEVICE_INFORMATION            = 11,        // �豸��Ϣ��ѯ(�糵ϵ��DCM����״̬�ȡ��������չ)
    FUNC202_TYPE_DEVICE_DCM_GPS                   = 12,        // DCM GPS������Ϣͬ��
    FUNC202_TYPE_DEVICE_DATA_UP_CONFIG           = 13,        // ����ָ���豸�ϱ���������GPS����(�洢��MYSQL��HBASE)
    FUNC202_TYPE_DEVICE_VEHICLE_DATA_CONFIG       = 14,        // ����ָ���豸�ϱ���������������(��App��)
    FUNC202_TYPE_DEVICE_SET_GREY_TCU           = 15,        // ���ûҶ�TCU
    FUNC202_TYPE_DEVICE_GET_GREY_TCU           = 16,        // ��ȡ�Ҷ�TCU
    FUNC202_TYPE_DEVICE_FUNCTION_OPTION        = 17,        // ���ù���ѡ��
    FUNC202_TYPE_DEVICE_GET_TCUCOUNT           = 18,        // ��ȡTCU����
    FUNC202_TYPE_DEVICE_GET_TCUPAGE            = 19,        // ��ҳ��ȡTCU
    FUNC202_TYPE_DEVICE_EVGET_TCUCOUNT         = 20,        // EV��ȡTCU������
    FUNC202_TYPE_DEVICE_SETGBCHECKSTATUS       = 21,        // ����ƽ̨�������״̬ͬ��
    FUNC202_TYPE_DEVICE_EV_DEV_INFO_SYNC       = 22,        // EV�豸������Ϣͬ��
    FUNC202_TYPE_DEVICE_SET_SPEC_INFO          = 23,        // ���������豸��Ϣ
    FUNC202_TYPE_DEVICE_SET_TCU_OFFLINE        = 24,        // tcu���ߴ���
    FUNC202_TYPE_DEVICE_SPEED_WARN             = 25,        // ���ٱ�������
    FUNC202_TYPE_DEVICE_SET_DICTIONARY         = 26,        // ���ÿ����û������ֵ�
    FUNC202_TYPE_DEVICE_SET_UPLOADATA          = 27,        // �����ϴ������ֶ�
    // device manager server  ***end***

    // atbox vis server  ***start***
    FUNC203_TYPE_GET_CAR_INFO                  = 1,        // �����豸��Ϣ������ 
    FUNC203_TYPE_GET_CAR_POS                   = 2,        // ����λ�ò�ѯ����
    FUNC203_TYPE_GET_CAR_ONLINE                = 3,        // ��������״̬��ѯ����
    FUNC203_TYPE_GET_CAR_CANDATA               = 4,        // ����CAN���ݲ�ѯ����
    FUNC203_TYPE_CAR_REMOTECTRL                = 5,        // ������Ͽ��������·����� 
    FUNC203_TYPE_GET_CAR_PM25                  = 6,        // PM2.5���ݲ�ѯ���� 
    FUNC203_TYPE_CHANGE_DEVICE                 = 7,        // AtBox�豸���� 
    FUNC203_TYPE_SET_CYCLEDATA                 = 8,        // AtBox������������ 
    FUNC203_TYPE_SET_CONFIGPARAM               = 9,        // AtBox���÷������ 
    FUNC203_TYPE_SET_ATBOX_GREY                = 10,       // AtBox���ûҶ�
    FUNC203_TYPE_GET_ATBOX_GREYLIST            = 11,       // AtBox��ȡ�Ҷ��б�
    // atbox vis server  ***end***

    // GB vis server  ***start***
    FUNC204_TYPE_EVEHICLE_STATUSBOARD          = 1,        // ����״̬����
    FUNC204_TYPE_EVEHICLE_DETAILDATA           = 2,        // ������ϸʵʱ����
    FUNC204_TYPE_EVEHICLE_PARAMCTRL            = 3,        // ��������������
    FUNC204_TYPE_EVEHICLE_CONSTPARAM           = 4,        // �����̶�ֵ����
    FUNC204_TYPE_EVEHICLE_NISSANCONST          = 5,        // �ղ������̶�ֵ 
    FUNC204_TYPE_EVEHICLE_NISSANDATA           = 6,        // �ղ���������
    FUNC204_TYPE_EVEHICLE_UPDATESTATUS         = 7,        // ����״̬��ѯ
    FUNC204_TYPE_EVREMOTECONTROL               = 8,        // EV��������
    FUNC204_TYPE_EVGETDIAGNOSIS                = 9,        // EV������ѯ
    FUNC204_TYPE_EVEGTCONST                    = 10,       // eGT�����̶�ֵ
    FUNC204_TYPE_EVEGTDATA                     = 11,       // eGT��������
    // GB vis server  ***end***

    // IOV-FactoryQC server  ***start***
    FUNC205_TYPE_FOURCODESYNC                  = 1,        // �����ʼ�����ͬ��
    FUNC205_TYPE_EVEHICLEDETAILDATA            = 2,        // �����ʼ����EV��������
    FUNC205_TYPE_GETVEHICLEDATA                = 3,        // �����ʼ���������
    FUNC205_TYPE_EVEHICLENISSANDATA            = 4,        // �����ʼ��ղ���������
    // IOV-FactoryQC server  ***end***

    // unicom sms server   ***start***
    FUN112_TYPE_UNICOM_SMS_WAKEUP              = 1,          // ���Ż���
    FUN112_TYPE_TCU_LOG_REQUEST                = 2,          // TCU��־����
    FUN112_TYPE_CHECK_ICCID_REQUEST            = 3,          // ICCID��Ч����֤����

    // unicom sms server   ***end***

    // http client server  ***start***
    FUN113_TYPE_HTTP_CLINET_GET                = 1,          // ����HTTP GET����
    FUN113_TYPE_HTTP_CLIENT_POST               = 2,          // ����HTTP POST����
    FUN113_TYPE_HTTP_CLIENT_POST_ON_OFF_LINE   = 3,          // �����豸�����ߵ�HTTP POST����
    FUN113_TYPE_HTTP_CLIENT_EV_SYNC_L3         = 4,          // ����EV VIN��httpclient�ж��Ƿ���Ҫͬ����L3
    FUN113_TYPE_HTTP_CLIENT_POST_VEH_STATUS    = 5,          // ���ͳ���״̬��L3
    FUN113_TYPE_HTTP_CLIENT_POST_VEH_RENAULT   = 6,          // ���ͳ���״̬��L3(for��ŵ���ͳ�)
    FUN113_TYPE_HTTP_CLIENT_VKEY_POST          = 7,          // ����Կ������(��Ҫ��L3�ذ��Ĵ���,�粻��Ҫ�ذ�,ֱ����post)
    FUN113_TYPE_HTTP_CLIENT_DOOR_WARN_RENUALT  = 8,          // ���ͳ��ŵ���δ�ظ澯��L3(for��ŵ���ͳ�)
    FUN113_TYPE_HTTP_CLIENT_POST_PDI           = 9,          // ������ŵPDI�澯��L3(for��ŵ���ͳ�)
    FUN113_TYPE_HTTP_CLIENT_POST_LOGIN_VER     = 10,         // ����TCU��¼�汾��Ϣ
    FUN113_TYPE_HTTP_CLIENT_POST_VNEXT_BATTCODE= 11,         // ����vNext��ر�����Ϣ��L3
    // http client server  ***end***

    // �������� server  ***start***
    FUN30_TYPE_IGN_ALARM                = 7,          // ���澯�����ر�����
    // �������� server  ***end***

    FUNCTION_TYPE_TQBOX_ORDER_REQ = 1,                  // TQBox ָ���·�

    // ������շ���  ***start***
    FUNCTION_TYPE_GB_RENA_UPDATE_GRADE  = 0x01,  // ������ŵ�豸  �����ļ�����

	FUNCITON_TYPE_GB_HEV_REMOTE         = 0x40,  // Remote Control 2VP(����)   up/down
    FUNCITON_TYPE_GB_HEV_SEND2CAR       = 0x42,  // Send2Car 2VP(����)   up/down
    FUNCTION_TYPE_GB_DEV_QUERY          = 0x80,  // �����豸 ��ѯ����
    FUNCTION_TYPE_GB_DEV_SET            = 0x81,  // �����豸 ��������
    FUNCTION_TYPE_GB_DEV_CONTROL        = 0x82,  // �����豸 ��������
    FUNCITON_TYPE_GB_GET_STATUS         = 0x83,  // ���� EVCC ��ȡ����״̬
    FUNCITON_TYPE_GB_EINS               = 0x84,  // ���� EVCC Զ�̵��
    
    FUNCTION_TYPE_VIRTUAL_KEY           = 0xE0,  // ����Կ��
    FUNCTION_TYPE_GB_CAR_CONTROL        = 0xE1,  // �������� ͬGB_MSG_CUSTOM_CONTROL
    FUNCTION_TYPE_GB_CAR_PKI_CTRL       = 0xE2,  // PKI��������
    // ������շ���  ***end***

    //IOV-GBDataDeal***BEGIN***
    FUNCTION_TYPE_GB_DATADEAL           = 0x01, // ��ת��GBDataDeal����Ĺ�����Ϣ
    FUNCTION_TYPE_LB_DATADEAL           = 0x02, // ��ת��GBDataDeal����ĵر���Ϣ
    FUNCTION_TYPE_VNEXT_DATADEAL        = 0x03, // ��ת��GBDataDeal�����vNext��Ϣ
    //IOV-GBDataDeal***END***

    //������Ϣ***BEGIN***
    FUNCTION_TYPE_GBVI_CARLOGIN         = 0x01, // ��ת��GBVIDeal����ĳ�������
    FUNCTION_TYPE_GBVI_REAL_DATA        = 0x02, // ��ת
    FUNCTION_TYPE_GBVI_RETRY_DATA       = 0x03, // 
    FUNCTION_TYPE_GBVI_CARLOGOUT        = 0x04, // ��ת��GBVIDeal����ĳ����ǳ�
    //IOV-GBDataDeal***END***


    //ATBOX_Data***BEGIN***
    FUNCTION_TYPE_CAN_DATA_REQ    = 1, // ATBOX�ϴ�CAN����
    FUNCTION_TYPE_GPS_DATA_REQ    = 2, // ATBOX�ϴ�GPS����
    FUNCTION_TYPE_PM_DATA_REQ    = 3, // ATBOX�ϴ�pm2.5����
    FUNCTION_TYPE_HJE_CAN_DATA_REQ    = 40, // ��ŵHJE����(���Ѻ���)�ϴ�CAN����
    FUNCTION_TYPE_HJE_GPS_DATA_REQ    = 41, // ��ŵHJE����(���Ѻ���)�ϴ�GPS����
    FUNCTION_TYPE_HJE_RMTDIAG_REQ = 42,
    FUNCTION_TYPE_TBOX_4G_EXTEND_REQ        = 42,       // (���Ѻ���)ƽ̨�·���չ�������󣨰�����ŵHJE���ֹ��ϼ�������Կ�׹��ܣ�
    FUNCTION_TYPE_NISSAN_CT_CAN_DATA_REQ    = 43, // �ղ���(���Ǻ���)�ϴ�CAN����
    FUNCTION_TYPE_NISSAN_CT_GPS_DATA_REQ    = 44, // �ղ���(���Ǻ���)�ϴ�GPS����    
    FUNCTION_TYPE_NISSAN_CT_BATCH_CAN_DATA_REQ    = 46, // �ղ���(���Ǻ���)�ϴ�������������
    FUNCTION_TYPE_NISSAN_CT_BATCH_GPS_DATA_REQ    = 47, // �ղ���(���Ǻ���)�ϴ�����GPS����
    FUNCTION_TYPE_NISSAN_ATBOX_RMTDIAG_REQ    = 48, // �ղ�AtBoxԶ�����
    FUNCTION_TYPE_NISSAN_CT_MALFLIST_REQ    = 49, // �ղ���(���Ǻ���)�ϴ��������嵥
    FUNCTION_TYPE_NISSAN_CT_DETECT_IGNON_REQ = 50, // �ղ���(���Ǻ���) APP�˿��������������
	FUNCTION_TYPE_NISSAN_CT_DCM_DATA_OFFLINE = 51, //DCM����֪ͨ

    //ATBOX_TBOX_Data***END*** 
    //IOV-ATDS***BEGIN*** 
    FUNCTION_TYPE_DIAGNOSIS_REQ = 1, // App�ϴ�Զ���������
    FUNCTION_TYPE_TRACK_DATA_REQ = 2,// App�ϴ�����׷��ģʽ
    //IOV-ATDS***END*** 

    //DCVP NGTP��Ϣ***BEGIN***
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 1,        // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ����ƽ��
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 2,        // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ���������
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT_POST = 3,    // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:���ƽ������
    FUNCTION_TYPE_DCVP_NGTP_SERVER_CTRL_RESULT = 4,            // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:Զ�̿���
    FUNCTION_TYPE_DCVP_NGTP_SERVER_SMS_SEND = 5,            // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:�·����Ÿ�DCM
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_VEH_WARN_POST = 6,    // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:�����澯����
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_TBOX_DIAG = 7,            // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ��������Ϣ
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_TBOX_REPLACE = 8,            // DCVP��Ŀ NGTPЭ�� �����ڲ���Ϣ:DCM�ϴ��������Ϣ

    
    //DCVP NGTP��Ϣ***END***
    //OBU ������Ϣ***BEGIN***
        FUNCTION_TYPE_OBU_DCM_REQ_VEH_DATA = 2,        // OBU��Ŀ�����ڲ���Ϣ:DCM�ϴ���������


     //OBU ������Ϣ***END***
     //RSE ������Ϣ***BEGIN***
        FUNCTION_TYPE_RSE_DCM_REQ_VEH_DATA = 2,        // RSE��Ŀ�����ڲ���Ϣ:DCM�ϴ���������
    //RSE ������Ϣ***END***
    //IOV-VSTK***BEGIN*** 
    FUNCTION_TYPE_VSTK_GETCERTINFO = 1, // ���֤�����Ӧ��Ϣ
    FUNCTION_TYPE_VSTK_SIMPLESIGN = 2,  // Simpleǩ��
    FUNCTION_TYPE_VSTK_VERIFY_SIMPLESIGN = 3, // Simple��ǩ��
    FUNCTION_TYPE_VSTK_ATTACHSIGN = 4,  // Attachǩ��
    FUNCTION_TYPE_VSTK_VERIFY_ATTACHSIGN = 5, // Attach��ǩ��
    FUNCTION_TYPE_VSTK_DETACHSIGN = 6,  // Dettachǩ��
    FUNCTION_TYPE_VSTK_VERIFY_DETACHSIGN = 7, // Dettach��ǩ��
    FUNCTION_TYPE_VSTK_ENCRYPTENVELOP = 8,  // ���������ŷ�
    FUNCTION_TYPE_VSTK_VERIFY_DECRYPTENVELOP = 9, // ���������ŷ�
    FUNCTION_TYPE_VSTK_CREATESIGNEDENVELOP = 10,  // ������ǩ���������ŷ�
    FUNCTION_TYPE_VSTK_VERIFY_SIGNEDENVELOP = 11, // ���ܲ���֤��ǩ���������ŷ�
    //IOV-VSTK***END*** 

    //IOV-BTK***BEGIN*** 
    FUNCTION_TYPE_BTK_CERTIFY_APPLY = 1, // ֤������
    FUNCTION_TYPE_BTK_CERTIFY_UPDATE = 2,// ֤�����
    FUNCTION_TYPE_BTK_CERTIFY_LOGOUT = 3, // ֤��ע��
    //IOV-BTK***END*** 

    //IOV-VSS***BEGIN***
    FUNC208_TYPE_VEHICLE_GPS_QUERY = 1,    //����λ�ò�ѯ
    //IOV-VSS***END***

    //IOV-TripFix***BEGIN***
    FUNC213_TYPE_VEH_DATA_REQ = 1,    // �ϴ���������ʷ����
    FUNC213_TYPE_GPS_DATA_REQ = 2,    // �ϴ�GPS����ʷ����
    //IOV-TripFix***END***

    //V2X-RSU***BEGIN*** 
    FUNCTION_TYPE_RSI_MSG = 1,        // �·� RSI ��Ϣ
    FUNCTION_TYPE_RSU_CONFIG = 2,     // �豸����
    FUNCTION_TYPE_RSU_LOG = 3,        // ��־����
    FUNCTION_TYPE_MAP_MSG = 4,        // �·� MAP ��Ϣ
    //V2X-RSU***END*** 

    //V2X-OBU***BEGIN*** 
    FUNCTION_TYPE_0BU_NETWORK_EVENT = 1,        // �·� OBU �����¼���Ϣ
    FUNCTION_TYPE_OBU_CONFIG = 2,           // �豸����
    FUNCTION_TYPE_OBU_LOG = 3,              // ��־����
    FUNCTION_TYPE_0BU_GLOSA_EVENT = 4,        // �·��̲�������Ϣ
    //V2X-OBU***END*** 


    //L2Backup***BEGIN***

    FUNCTION_TYPE_L2BU_CTRL_REQUEST = 600,            // L2Backup��Ŀ �����ڲ���Ϣ:Զ������
    FUNCTION_TYPE_L2BU_SMS_SEND = 601,                // L2Backup��Ŀ �����ڲ���Ϣ:�·����Ÿ��豸��

    //L2Backup***END
};

///@class  DCM_CONFIGURE_CMD_TYPE [APPCommon.h]
///@brief  DCM �������ݹ�������
///@author jiangxiaobao
///@note   DCM�·����������ݵĹ���
enum DCM_CONFIGURE_CMD_TYPE
{
    DCM_CONFIGURE_CMD_REPORT_INTERVAL = 3,                      //�����ϱ�ʱ����
    // ���ſ��ƣ�����ʾ��
    //DCM_CONFIGURE_CMD_DOOR_LOCK_CONTROL = 4,                     //���������� 0x01:������0x00:����
    DCM_CONFIGURE_CMD_CAR_TYPE = 4,                             //DCM��������
    DCM_CONFIGURE_CMD_DVRPHONE_TYPE = 23,        //DVR���տ���
};

// ֧�ֵļ��ܱ�ʶ
enum ENCRYPT_FLAG
{
    ENCRYPT_FLAG_NO_ENCRYPT = 0,            // δ����
    ENCRYPT_FLAG_RSA_ENCRYPT = 1,            // RSA����
    ENCRYPT_FLAG_RC4_ENCRYPT = 2,            // RC4����
    ENCRYPT_FLAG_AES_ENCRYPT = 3,            // AES����
    ENCRYPT_FLAG_NOT_SUPPORT                           // ���ܷ�ʽ��֧��
};

#define PROJECT_TYPE_IOV_531 "531"    // ������Ŀ�������ղ� 531
#define PROJECT_TYPE_IOV_FL  "iov-fl" // ������Ŀ�������Ϸ���������
#define PROJECT_TYPE_IOV_EV  "iov-ev" // ������Ŀ��EV
#define PROJECT_TYPE_IOV_GBVI  "iov-gbvi" // ������Ŀ������
#define PROJECT_TYPE_IOV_2VP  "2VP" // ������Ŀ������2VP

#define STRING_NULL     "null"

#endif  ///*APP_COMMON_H*/

