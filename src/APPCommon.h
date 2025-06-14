///@file     APPCommon.h
///@brief    App 基础定义(内部服务通讯消息类型)
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     

#ifndef APP_COMMON_H
#define APP_COMMON_H

///@enum   MSG_PROTOCOL [APPCommon.h]
///@brief  消息协议类型
///@author tangjie
///@note   
enum MSG_PROTOCOL
{
    MSG_PROTOCOL_APP                    = 0,    // APP 消息协议
    MSG_PROTOCOL_DCM                    = 1,    // DCM 消息协议
    MSG_PROTOCOL_CMPP                   = 2,
    MSG_PROTOCOL_ATBOX                  = 3,
};

///@class  SERVER_TYPE [APPCommon.h]
///@brief  服务类型
///@author tangjie
///@note   
enum SERVER_TYPE
{
    SERVER_TYPE_MANAGER             = 1,        // 管理服务
    SERVER_TYPE_APP_ROUTER          = 2,        // APP 路由服务
    SERVER_TYPE_DCM_ROUTER          = 3,        // DCM 路由服务
    SERVER_TYPE_APP_BUSINESS        = 4,        // APP 业务服务
    SERVER_TYPE_DCM_BUSINESS        = 5,        // DCM 业务服务
    //SERVER_TYPE_APP_CACHE         = 6,        // APP 缓存服务
    //SERVER_TYPE_DCM_CACHE         = 7,        // DCM 缓存服务
    SERVER_TYPE_UNICOM_SMS          = 8,        // 联通短信服务
    SERVER_TYPE_HTTP_CLIENT         = 9,        // Http发送服务
    SERVER_TYPE_TQBOX_ROUTER        = 10,       // TQBox 路由服务
    SERVER_TYPE_DATA_REPORT_CONTROL = 11,       // 数据上传控制服务
    SERVER_TYPE_CARWINGS_CGUARD     = 12,       // Carwings cguard 服务
    SERVER_TYPE_CARWINGS_08IT       = 13,       // Carwings 08IT 服务
    SERVER_TYPE_CARWINGS_CGUARD_ROUTE = 14,     // Carwings CGuard分流服务
    SERVER_TYPE_CARWINGS_08IT_ROUTE = 15,       // Carwings 08IT分流服务

    SERVER_TYPE_VEH_DPS_SUB         = 19,       // DCM业务服务-整车数据处理服务 拆分出的子服务

    SERVER_TYPE_ATBOX_DCM_ROUTER    = 23,       // ATBox项目 DCM请求数据的路由服务
    SERVER_TYPE_ATBOX_APP_BUSINESS  = 24,       // ATBox项目 APP请求数据的业务服务
    SERVER_TYPE_ATBOX_DCM_BUSINESS  = 25,       // ATBox项目 DCM请求数据的业务服务
    SERVER_TYPE_NISSAN_ATBOX        = 26,       // 日产ATBox项目

    SERVER_TYPE_VSTK                = 31,       // Vstk服务，签名验签
    SERVER_TYPE_BTK                 = 32,       // Btk服务，证书获取
	SERVER_TYPE_CERT_DOWNLOAD_ROUTE = 33,	    // 证书下载接入服务

    SERVER_TYPE_EV_GB_DEAL          = 40,       // GB数据处理
    // 41-45 预留给国标数据处理
    SERVER_TYPE_EV_GB_SEND          = 46,       // GB发送处理

    SERVER_TYPE_EV_EV_CUSTOM_DEAL   = 60,       // EV自定义数据处理
    // 61-65 预留给EV自定义数据处理
    
    SERVER_TYPE_DCVP_NGTP_DCM_ROUTER          = 120, // DCVP项目 NGTP协议 DCM请求数据的路由服务
    SERVER_TYPE_DCVP_GBVI_DCM_ROUTER          = 121, // DCVP项目 国六协议 DCM请求数据的路由服务
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 131, // DCVP项目 NGTP协议 DCM控制结果处理服务
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 132, // DCVP项目 NGTP协议 DCM车辆数据处理服务
    SERVER_TYPE_DCVP_GBVI_DCM_REQ_VEH_DATA    = 133, // DCVP项目 国六协议 DCM数据处理服务
    SERVER_TYPE_DCVP_NGTP_DCM_DATA_POSTER     = 141, // DCVP项目 NGTP协议 DCM数据推送服务
    SERVER_TYPE_DCVP_GBVI_DCM_DATA_RELAY      = 142, // DCVP项目 国六协议 DCM数据转发服务
    SERVER_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CTRL = 151, // DCVP项目 NGTP协议 APP远程控制服务
    SERVER_TYPE_DCVP_NGTP_APP_REQ_SMS_SENDER  = 152, // DCVP项目 NGTP协议 DCM短信发送
    SERVER_TYPE_DCVP_NGTP_DCM_REQ_SELF_ADMIN  = 153, // DCVP项目 NGTP协议 自诊断替换
 
    SERVER_TYPE_TIMER_MANAGER = 209,                 // 定时器服务 (IOV-TaskTimerModule)

    SERVER_TYPE_TRIP_FIX = 210,                      // 行程即时补偿服务 (IOV-TripFixModule)
    SERVER_TYPE_ICCID_CHECK = 211,                   // ICCID 有效性验证服务 (IOV-IccidCheck)

    SERVER_TYPE_OBU_DCM_ROUTER = 192,                  // 自动驾驶云端obu的接入
    SERVER_TYPE_OBU_DCM_REQ_VEH_DATA = 193,            // 自动驾驶云端obu的整车数据服务
    SERVER_TYPE_OBU_DCM_REQ_CTRAL_DOWN = 194,          // 自动驾驶云端obu的远控下发服务
    SERVER_TYPE_OBU_CAN_DCM_ROUTER = 196,              // 自动驾驶云端obu的can接入转发服务
	
	SERVER_TYPE_V2X_OBU_DS = 215,						// V2X OBU接入服务
	SERVER_TYPE_V2X_RSU_DS = 216,						// V2X RSU接入服务
	SERVER_TYPE_V2X_OBU_NETWORK = 217,					// V2X OBU网络数据服务
	SERVER_TYPE_V2X_OBU_BSM = 218,						// V2X OBU整车数据服务
	SERVER_TYPE_V2X_OBU_SCENES = 219,					// V2X OBU场景数据服务
	SERVER_TYPE_V2X_RSU_DATA = 220,						// V2X RSU数据服务
	SERVER_TYPE_V2X_EVENT_ISSUED = 221,					// V2X 事件下发服务
	SERVER_TYPE_V2X_DATA_INTERFACE = 222,				// V2X 数据接口服务
    SERVER_TYPE_V2X_FORWARD_DATA_REPORT = 223,          // V2X 转发数据上报服务


    SERVER_TYPE_NADD_VEH_DATA = 225,                    // 日产保有车后装TBOX整车服务(IOV-NAddVehModule) 
    SERVER_TYPE_NADD_DS = 226,                          // 日产保有车后装TBOX接入服务(IOV-NAddDSModule) 
    SERVER_TYPE_NADD_VIS = 227,                         // 日产保有车后装TBOX信息查询服务(IOV-NAddVISModule) 
    SERVER_TYPE_NADD_L3_INTERFACE = 228,                // 日产保有车后装TBOX L3接口服务(IOV-NAddL3InterfaceModule) 
	SERVER_TYPE_NADD_REMOTE_CONTROL = 229,              // 日产保有车后装TBOX远控服务(IOV-NAddRCSModule) 
	SERVER_TYPE_NADD_SMS = 230,                         // 日产保有车后装TBOX短信服务(IOV-NAddSMSModule) 

    SERVER_TYPE_L2BU_BOOTSTRAP_API = 250,               // L2 Backup bootstrap API 服务
    SERVER_TYPE_L2BU_PUSH_CENTER = 251,                 // L2 Backup 推送中心服务
    SERVER_TYPE_L2BU_ALARM_PUSH = 252,                  // L2 Backup 告警服务
    SERVER_TYPE_L2BU_DS = 253,                          // L2 Backup 接入服务
    SERVER_TYPE_L2BU_REMOTE_CTRL = 254,                 // L2 Backup 远程控制服务
    SERVER_TYPE_L2BU_API_GATE_WAY = 255,                // L2 Backup API网关服务
};

///@class  MESSAGE_TYPE [APPCommon.h]
///@brief  消息类型
///@author tangjie
///@note   
enum MESSAGE_TYPE
{
    MESSAGE_TYPE_SERVER_STATUS          = 1,        // 服务状态消息,内部消息(ManagerServer)
    //MESSAGE_TYPE_USER_STATUS          = 11,       // 用户状态信息缓存,内部消息
    MESSAGE_TYPE_DCM_STATUS             = 12,       // DCM 状态信息缓存,内部消息
    MESSAGE_TYPE_DCM_DATA               = 13,       // DCM 数据消息,内部消息(整车)
    MESSAGE_TYPE_DCM_CONFIGURE          = 14,       // DCM 设置消息(IOV-DS)
    MESSAGE_TYPE_APP_ROUTER             = 15,       // APP Router接收的内部消息(Business-DS)
    MESSAGE_TYPE_UBI_DATA_DEAL          = 16,       // UBI数据处理服务(老平台,已不使用)
    MESSAGE_TYPE_DCM_UPDATE             = 17,       // DCM升级服务(已不使用)
    MESSAGE_TYPE_TQBOX_CONFIGURE        = 18,       // TQBox设置消息,内部消息(TQBOX-DS)
    MESSAGE_TYPE_GB_CONFIGURE           = 19,       // 国标设备设置消息(IOV-GBDS)
    MESSAGE_TYPE_TLS_CONFIGURE          = 20,       // 532PKI接入服务(IOV-PKIDS)
    MESSAGE_TYPE_GBCYCLE_CONFIGURE      = 21,       // vNext接入服务(IOV-GBCycleDS)
    MESSAGE_TYPE_GBTLS_CONFIGURE        = 22,       // 国标设备PKI接入服务(IOV-TLSGBDS)

    MESSAGE_TYPE_NISSAN_TBOX_VEHICLE_DATA = 30,     // TCU 整车数据处理服务(IOV-VehicleDPS)
    MESSAGE_TYPE_NISSAN_TBOX_GPS_DATA   = 31,       // TCU GPS数据处理服务(IOV-GPSDPS)
    MESSAGE_TYPE_NISSAN_TBOX_ALARM_DATA = 32,       // TCU 报警数据处理服务(IOV-AlarmPushAP)
    MESSAGE_TYPE_KEY_GENERATE           = 34,       // 密钥生成服务(KeyGenerate)
    
    MESSAGE_TYPE_GB_DATAMAG             = 35,       // 国标数据处理及发送(IOV-GBDataMag)
    MESSAGE_TYPE_GB_DATADEAL_DEF        = 40,       // 国标数据处理服务默认消息ID(IOV-GBDataDeal)
    // 41-45 预留给国标数据处理服务配置用
    MESSAGE_TYPE_GB_DATADEAL_MAX        = 45,       // 国标数据处理服务最大消息ID(IOV-GBDataDeal)
    MESSAGE_TYPE_GB_DATASEND            = 46,       // 国标数据发送服务(IOV-GBDataSend)
 
    MESSAGE_TYPE_ATBOX_CAN_DATA         = 51,       // ATBox CAN数据
    MESSAGE_TYPE_ATBOX_GPS_DATA         = 52,       // ATBox GPS数据
    MESSAGE_TYPE_AT_CONFIGURE           = 53,       // ATBox DS消息
    MESSAGE_TYPE_RENAULT_CAN_DATA       = 54,       // ATBox 雷诺HJE CAN数据 ymj20181203
    MESSAGE_TYPE_RENAULT_GPS_DATA       = 55,       // ATBox 雷诺HJE GPS数据 ymj20181203
    MESSAGE_TYPE_NISSAN_CT_VEH_DATA     = 56,       // ATBox Nissan(畅星TCU) 整车数据 Johnson 20181217
    MESSAGE_TYPE_NISSAN_CT_GPS_DATA     = 57,       // ATBox Nissan(畅星TCU) GPS数据 Johnson 20181217

    MESSAGE_TYPE_EV_CUSTOM_DEF          = 60,       // EV 自定义数据处理服务默认(IOV-EVCustomDeal)
    // 61-65 预留给EV自定义数据处理服务配置用
    MESSAGE_TYPE_EV_CUSTOM_MAX          = 65,       // EV 自定义数据处理最大消息ID(IOV-EVCustomDeal)
    MESSAGE_TYPE_DYNAMIC_VEHIC          = 66,       // 动态协议整车服务

    MESSAGE_TYPE_USER_LOG               = 101,      // 用户认证(老平台,已不使用)
    //MESSAGE_TYPE_USER_MANAGER         = 102,      // 用户管理(老平台,已不使用)
    //MESSAGE_TYPE_MSG_MANAGER          = 103,      // 消息管理(老平台,已不使用)
    //MESSAGE_TYPE_SYS_MANAGER          = 104,      // 系统管理(老平台,已不使用)
    //MESSAGE_TYPE_DCM_MANAGER          = 105,      // DCM 管理(老平台,已不使用)
    MESSAGE_TYPE_MSG_PUSH               = 106,      // 消息推送(老平台,已不使用)
    MESSAGE_TYPE_TBOX                   = 107,      // TBOX(老平台,已不使用)
    MESSAGE_TYPE_QUERY_BREAK_RULES      = 108,      // 查询违章(老平台,已不使用)
    MESSAGE_TYPE_EV_MANAGER             = 110,      // EV智慧车管家接口(老平台,已不使用)
    MESSAGE_TYPE_TRIAL_RUN              = 111,      // 试乘试架服务(老平台,已不使用)
    
    MESSAGE_TYPE_UNICOM_SMS             = 112,      // 联通短信服务(IOV-UniSms)
    MESSAGE_TYPE_HTTP_CLIENT            = 113,      // Http发送服务(IOV-HttpClient)

    MESSAGE_TYPE_VEH_TRIP               = 119,      // 行程分析服务(IOV-VehTrip)
    MESSAGE_TYPE_VEH_ALERT              = 120,      // 报警监测服务(IOV-VehAlert)
    MESSAGE_TYPE_GPS_EFENCE             = 121,      // 电子围栏服务(IOV-GPSEFence)

    MESSAGE_TYPE_REMOTE_CONTROL         = 200,      // 远程控制服务(IOV-RCS)
    MESSAGE_TYPE_VEHICLE_INFO           = 201,      // 车辆信息处理服务(IOV-VIS)
    MESSAGE_TYPE_DEVICE_MANAGER         = 202,      // 设备管理服务(IOV-DevMangerS)

    MESSAGE_TYPE_ATBOX_MANAGER          = 203,      // ATBox信息处理服务(IOV-ATVIS)

    MESSAGE_TYPE_GB_MANAGER             = 204,      // 国标信息处理服务(IOV-GBVIS)
    MESSAGE_TYPE_FACTORYQC_MANAGER      = 205,      // 工厂质检处理服务(IOV-FactoryQC)

    MESSAGE_TYPE_DCVP_GBVI_DS                  = 121, // DCVP项目 国六协议 服务内部消息:国六接入服务
    MESSAGE_TYPE_DCVP_GBEV_DS                  = 122, // DCVP项目 国标EV协议 服务内部消息:EV接入服务

    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 131, // DCVP项目 NGTP协议 服务内部消息:DCM上传控制结果
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 132, // DCVP项目 NGTP协议 服务内部消息:DCM上传车辆数据
    MESSAGE_TYPE_DCVP_GBVI_DATA_DEAL           = 133, // DCVP项目 国六协议 服务内部消息:国六数据处理
    MESSAGE_TYPE_DCVP_GBEV_DATA_DEAL           = 134, // DCVP项目 国标EV协议 服务内部消息: EV数据处理
    MESSAGE_TYPE_DCVP_NGTP_DCM_DATA_POSTER     = 141, // DCVP项目 NGTP协议 服务内部消息:DCM数据推送服务
    MESSAGE_TYPE_DCVP_GBVI_DATA_SEND           = 142, // DCVP项目 国六协议 服务内部消息:国六数据转发服务
    MESSAGE_TYPE_DCVP_GBEV_DATA_SEND           = 143, // DCVP项目 国标EV协议 服务内部消息:EV数据转发服务
    MESSAGE_TYPE_DCVP_GBEV_PARAM_CTRL          = 144, // DCVP项目 国标EV协议 服务内部消息:EV参数控制

    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CTRL                  = 151, // DCVP项目 NGTP协议 服务内部消息:APP请求远程控制
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_SMS_SENDER                   = 152, // DCVP项目 NGTP协议 服务内部消息:APP请求短信发送
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_SELF_ADMIN                   = 153, // DCVP项目 NGTP协议 服务内部消息:自诊断替换 
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_REMOTE_CONFIG                = 154, // DCVP项目 NGTP协议 服务内部消息:远程配置服务
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_REMOTE_CONFIG_RESULT         = 155, // DCVP项目 NGTP协议 服务内部消息:远程配置结果服务
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_SOFTWARE_UPGRADE             = 156, // DCVP项目 NGTP协议 服务内部消息:软件更新服务
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_SOFTWARE_UPGRADE_RESULT      = 157, // DCVP项目 NGTP协议 服务内部消息:软件更新结果服务

    //ymj 20191011
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_BLE          = 160, // DCVP项目 NGTP协议 服务内部消息:蓝牙钥匙通知服务
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_BLE_RESULT   = 161, // DCVP项目 NGTP协议 服务内部消息:蓝牙钥匙结果服务
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_LOG         = 162,  // DCVP项目 NGTP协议 服务内部消息:日志短信通知服务

    MESSAGE_TYPE_DCVP_EVH_DCM_REQ_CUSTOM_VEH_DATA   = 178,      // DCVP H97自定义整车服务

    //ymj 20200319
    MESSAGE_TYPE_DCVP_NGTP_APP_REQ_CAN          = 179, //DCVP项目 NGTP协议 服务内部消息:车辆网络监控通知服务
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CAN_RESULT   = 180, //DCVP项目 NGTP协议 服务内部消息:车辆网络监控结果服务    
    MESSAGE_TYPE_DCVP_NGTP_DCM_REQ_CAN_INFO     = 181, //DCVP项目 NGTP协议 服务内部消息:车辆网络监控异常信息服务
    MESSAGE_TYPE_DCVP_EVH_DCM_REQ_CUSTOM_VEH_ABNORMAL_DATA  = 182,  //DCVP H97车辆异常告警信息服务
    MESSAGE_TYPE_DCVP_NGTP_DCM_CREDIT   = 185,  //DCVP项目 NGTP协议 服务内部消息:授信车信息服务   
    MESSAGE_TYPE_DCVP_NGTP_DCM_CREDIT_SMS   = 186,  //DCVP项目 NGTP协议 服务内部消息:授信车短信下发服务

    //ymj 20200723,给自动驾驶云端平台用
    MESSAGE_TYPE_RSE_DS = 188,              //自动驾驶云端rse的接入
    MESSAGE_TYPE_RSE_DATE = 189,            //自动驾驶云端rse的采集数据处理模块(整车)
    MESSAGE_TYPE_RSE_CTRL = 190,            //自动驾驶云端rse的远程控制服务
    MESSAGE_TYPE_OBU_DCM_ROUTER = 192,                  // 自动驾驶云端obu的接入
    MESSAGE_TYPE_OBU_DCM_REQ_VEH_DATA = 193,            // 自动驾驶云端obu的整车数据服务
    MESSAGE_TYPE_OBU_DCM_REQ_CTRAL_DOWN = 194,          // 自动驾驶云端obu的远控下发服务
    MESSAGE_TYPE_OBU_CAN_DCM_ROUTER = 196,              // 自动驾驶云端obu的can接入转发服务

    MESSAGE_TYPE_VSTK_MANAGER                  = 206, // Vstk签名管理（IOV-VSTK服务）
    MESSAGE_TYPE_BTK_MANAGER                   = 207, // Btk签名管理（IOV-BTK服务）
    MESSAGE_TYPE_VEHICLE_STATE                 = 208, // 车辆状态查询服务(IOV-VSS)
    MESSAGE_TYPE_TIMER_MANAGER                 = 209, // 定时器服务 (IOV-TaskTimerModule)
    MESSAGE_TYPE_VEHICLE_INFO_MYSQL            = 210, // 车辆状态查询服务(IOV-VRS)
    MESSAGE_TYPE_NAVSTK_MANAGER                = 211, // NAVstk签名管理（IOV-NAVSTK服务）
    MESSAGE_TYPE_NABTK_MANAGER                 = 212, // NABtk签名管理（IOV-NABTK服务）

    MESSAGE_TYPE_TRIP_FIX = 213,    // 行程即时补偿服务 (IOV-TripFixModule)
    MESSAGE_TYPE_ICCID_CHECK = 214, // ICCID 有效性验证服务 (IOV-IccidCheck)
	
    MESSAGE_TYPE_V2X_OBU_DS = 215,						// V2X OBU接入服务
	MESSAGE_TYPE_V2X_RSU_DS = 216,						// V2X RSU接入服务
	MESSAGE_TYPE_V2X_OBU_NETWORK = 217,					// V2X OBU网络数据服务
	MESSAGE_TYPE_V2X_OBU_BSM = 218,						// V2X OBU整车数据服务
	MESSAGE_TYPE_V2X_OBU_SCENES = 219,					// V2X OBU场景数据服务
	MESSAGE_TYPE_V2X_RSU_DATA = 220,					// V2X RSU数据服务
	MESSAGE_TYPE_V2X_EVENT_ISSUED = 221,				// V2X 事件下发服务
	MESSAGE_TYPE_V2X_DATA_INTERFACE = 222,				// V2X 数据接口服务
    MESSAGE_TYPE_V2X_FORWARD_DATA_REPORT = 223,         // V2X 转发数据上报服务

    MESSAGE_TYPE_NADD_VEH_DATA = 225,                   // 日产保有车后装TBOX整车服务(IOV-NAddVehModule) 
    MESSAGE_TYPE_NADD_DS = 226,                         // 日产保有车后装TBOX接入服务(IOV-NAddDSModule) 
    MESSAGE_TYPE_NADD_VIS = 227,                        // 日产保有车后装TBOX信息查询服务(IOV-NAddVISModule) 
    MESSAGE_TYPE_NADD_L3_INTERFACE = 228,               // 日产保有车后装TBOX L3接口服务(IOV-NAddL3InterfaceModule) 
	MESSAGE_TYPE_NADD_REMOTE_CONTROL = 229,             // 日产保有车后装TBOX远控服务(IOV-NAddRCSModule) 
    MESSAGE_TYPE_NADD_SMS = 230,                        // 日产保有车后装TBOX短信服务(IOV-NAddSMSModule) 

    MESSAGE_TYPE_L2BU_BOOTSTRAP_API = 250,              // L2 Backup bootstrap API 服务
    MESSAGE_TYPE_L2BU_PUSH_CENTER = 251,                // L2 Backup 推送中心服务
    MESSAGE_TYPE_L2BU_ALARM_PUSH = 252,                 // L2 Backup 告警服务
    MESSAGE_TYPE_L2BU_DS = 253,                         // L2 Backup 接入服务
    MESSAGE_TYPE_L2BU_REMOTE_CTRL = 254,                // L2 Backup 远程控制服务
    MESSAGE_TYPE_L2BU_API_GATE_WAY = 255,               // L2 Backup API网关服务
};

// 消息功能号对应的响应消息，第一位为1
#define MESSAGE_FUNCTION_TYPE_RSP_MARK 0x8000
#define MESSAGE_FUNCTION_TYPE_RSP_UNMARK 0x7FFF

///@class  MESSAGE_FUNCTION_TYPE [APPCommon.h]
///@brief  消息功能号
///@author tangjie
///@note   两个字节，最高位为1表示响应消息
enum MESSAGE_FUNCTION_TYPE
{
    FUNCTION_TYPE_SERVER_STATUS = 1,                         // 服务状态消息，内部消息
    //DCM_Cache***BEGIN*** 
    FUNCTION_TYPE_DCM_CACHE_UPDATE    = 1,                   // DCM 更新缓存数据
    FUNCTION_TYPE_DCM_CACHE_QUERY_RANK = 3,                  // 查询DCM 排名数据
    //DCM_Cache***END*** 
    //DCM_Data***BEGIN*** 
    FUNCTION_TYPE_LY_DCM_DATA_REPORT_REQ = 1,                // DCM 数据上报请求
    FUNCTION_TYPE_YZ_DCM_DATA_REPORT_REQ = 2,                // DCM 数据上报请求
    FUNCTION_TYPE_DCM_DATA_OFFLINE       = 3,                // DCM 离线通知
    FUNCTION_TYPE_BLUETOOTH_STATE        = 4,                // 蓝牙状态
    FUNCTION_TYPE_FENCE_ALERT            = 5,                // 电子围栏预警
    FUNCTION_TYPE_YZ_DCMTRIAL_DATA_REQ   = 6,                // 试乘试驾 DCM 数据上报请求
    //DCM_Data***END*** 
    //IOV-DS***BEGIN*** 
    FUNCTION_TYPE_DCM_CONFIGURE_REQ = 1,                     // DCM 配置下发请求 
    FUNCTION_TYPE_GET_AUTH_KEY_REQ = 2,                      // 获取鉴权码
    FUNCTION_TYPE_DCM_ELECFENCE_REQ = 3,                     // DCM 电子围栏下发请求
    FUNCTION_TYPE_DCM_NETWORKALARM_REQ = 4,                  // DCM 流量告警下发请求
    FUNCTION_TYPE_DCM_UPDATECONTROL_REQ = 5,                 // DCM升级控制下发请求
    FUNCTION_TYPE_DCM_UPDATECANCEL_REQ = 6,                  // DCM升级取消下发请求
    FUNCTION_TYPE_DCM_DVR_REQ = 7,                           // TCU DVR 唤醒请求
    FUNCTION_TYPE_DCM_RMTDIAG_REQ = 8,                       // TCU 故障检测请求
    FUNCTION_TYPE_DCM_REMOTE_CTRL_REQ = 9,                   // 带签名的反控请求
    FUNCTION_TYPE_SPECDCM_INFOEX = 10,                       // 特殊车辆扩展信息通知
    FUNCTION_TYPE_DCM_PKI_UPDATECTRL_REQ = 11,               // 带签名DCM升级控制下发请求
    FUNCTION_TYPE_DCM_BACK_UP_REQ = 12,                      // Back up下发请求
    //IOV-DS***END*** 
    FUNCTION_TYPE_TCU_FORCEOFFLINE_REQ = 999,                //DS服务公用的TCU强制下线请求
    //User_Log***BEGIN*** 
    FUNCTION_TYPE_USER_GET_CHECK_RAND = 101,                  // 获取校验随机数
    //User_Log***END*** 
    //SYS_MANAGER***BEGIN*** Add by jiangxiaobao   2015-01-15
    FUNCTION_TYPE_QUERY_LAST_VERSION     = 4,                         //版本更新查询
    FUNCTION_TYPE_FEED_BACK_IDEA         = 5,                         //意见反馈
    FUNCTION_TYPE_QUERY_OIL_PRICE        = 7,                         //油价查询
    FUNCTION_TYPE_ADD_ACT_LOG            = 8,                         //记录APP日志
    FUNCTION_TYPE_GET_FUNCTION_LABEL     = 9,                         //获取功能标签接口
    FUNCTION_TYPE_GET_USER_TRAFFIC       = 10,                        //获取流量接口
    FUNCTION_TYPE_GET_EMGCY_RESCUE_INFO  = 16,                        //获取紧急救援信息
    //SYS_MANAGER***END***
    //DCM_Status***BEGIN*** 
    FUNCTION_TYPE_DCM_CONFIGURE = 3,                            // DCM 设置数据
    FUNCTION_TYPE_GET_AUTH_KEY = 5,                             // 获取鉴权码
    FUNCTION_TYPE_GET_TRIAL_RUN_LOCATION = 6,                   // 获取试乘试驾的坐标
    //DCM_Status***END*** 
    // MSG_PUSH_SERVER***BEGIN***
    FUNCTION_TYPE_MSG_PUSH_USER_INFO = 1,                       // 消息推送用户信息
    FUNCTION_TYPE_MSG_PUSH_TO_SINGLE_DEVICE = 100,              // 推送到单个设备的消息
    FUNCTION_TYPE_MSG_PUSH_COMMON_MSG = 200,                    // 消息推送通用消息
    // MSG_PUSH_SERVER***END***
    // TBOX_SERVER***BEGIN***
    FUNCTION_TYPE_SET_LOCATION_SHARING_INFO = 1,                // 位置共享消息
    FUNCTION_TYPE_GET_LOCATION_SHARING_INFO = 2,                // 获取位置共享消息
    FUNCTION_TYPE_IGITION_INFO              = 3,                // 点火信息
    FUNCTION_TYPE_GET_LOCATION_INFO         = 5,                // 获取位置信息
    FUNCTION_TYPE_GET_LOCATION_BYORDER      = 6,                // 订单号获取位置信息
    FUNCTION_TYPE_SET_UNLOCK_ALERT          = 9,                // 设置未锁车提醒开关
    FUNCTION_TYPE_GET_UNLOCK_ALERT          = 10,               // 获取未锁车提醒开关状态
    // TBOX_SERVER***END*** 

    //BackupVehic***START***  动态整车服务
    FUNCTION_TYPE_LY_DYNAMIC_DATA_REPORT_REQ = 1,               // 动态协议整车数据上报请求
    //BackupVehic***End***  动态整车服务

    // QUERY_BREAK_RULES_SERVER***BEGIN*** 
    FUNCTION_TYPE_GET_USER_BREAK_RULES = 1,                // 查询违章
    // QUERY_BREAK_RULES_SERVER***END*** 


    // DCM 升级服务 ***BEGIN***
    FUNCTION_TYPE_DCM_UPDATE_MSG    = 1,                    //DCM 升级服务
    // DCM 升级服务 ***END***

    //Key Generate***START***  密钥生成接口
    FUNCTION_TYPE_GET_RSAKEY            = 1,        // 获取RSA密钥
    //Key Generate***End***  密钥生成接口

    //NISSAN_TBOX_Data***BEGIN*** 
    FUNC113_TYPE_VEHICLE_DATA_REPORT_REQ = 1,                // 整车数据
    FUNC113_TYPE_GPS_DATA_REPORT_REQ = 2,                    // GPS数据
    FUNC113_TYPE_ALARM_DATA_REPORT_REQ = 3,                  // 报警数据
    FUNC113_TYPE_TBOX_GPS_REPORT_REQ = 4,                    // TBOX GPS数据(为了电子围栏检测)
    FUNC113_TYPE_GB_GPS_REPORT_REQ = 5,                      // 国标GPS数据(为了电子围栏检测)
    FUNC113_TYPE_VEH_TRIP_DATA_REQ = 101,                    // 整车数据-行程相关数据
    FUNC113_TYPE_VEH_ALERT_DATA_REQ = 102,                   // 整车数据-报警相关数据
    FUNC113_TYPE_GPS_EFENCE_DATA_REQ = 103,                  // GPS数据-电子围栏相关数据
                                                             //NISSAN_TBOX_Data***END*** 

    // remote control server ***start***
    FUNC200_TYPE_CALL_BACK              = 1,                  // 回调消息
    FUNC200_TYPE_REMOTE_CONTROL         = 2,                  // 远程控制
    FUNC200_TYPE_REMOTE_AWAKEN          = 3,                  // 远程唤醒
    FUNC200_TYPE_CYCLE_PARAM            = 4,                  // 周期数据设置
    FUNC200_TYPE_SAFETY_PROTECTION      = 5,                  // 安全防护
    FUNC200_TYPE_QUERY_ALARMINFO        = 6,                  // 查询异常报警
    FUNC200_TYPE_QUERY_UPGRADECANCEL    = 7,                  // 升级取消(废弃)
    FUNC200_TYPE_EV_PARAM_AND_CTRL      = 8,                  // EV电动车的参数读写和控制(TCU相关的设置和控制)
    FUNC200_TYPE_CALL_BACK_GET          = 9,                  // 回调消息获取
    FUNC200_TYPE_WAKEUPDVR              = 10,                 // TCU DVR 唤醒请求 
    FUNC200_TYPE_RMTDIAG                = 11,                 // TCU 故障检测请求
    FUNC200_TYPE_RMTDIAG_RESULT         = 12,                 // TCU 故障检测结果 (延后返回的)
    FUNC200_TYPE_EVCAR_REMOTE_CONTROL   = 13,                 // EV车辆控制(车辆相关控制)
    FUNC200_TYPE_VIRTUAL_KEY            = 14,                 // 虚拟钥匙
    FUNC200_TYPE_HJE_RMTDIAG            = 15,                 // HJE远程诊断
    FUNC200_TYPE_HJE_RMTDIAG_RESULT     = 16,                 // HJE远程诊断结果返回(延后返回的)
    FUNC200_TYPE_CT_COMMAND             = 17,                 // 日产ATBox命令下发
	FUNC200_TYPE_HEV_REMOTE_CONTROL		= 18,                 // 东本HEV车辆反控
    // remote control server ***end***

    // 日产保有车后装TBOX远控服务 ***start***
    FUNC229_TYPE_MSG_GET_PARAM           = 1,                   // 查询请求
    FUNC229_TYPE_MSG_CTRL                = 2,                   // 远控请求
    FUNC229_TYPE_MSG_CTRL_RESULT_REPORT  = 3,                   // 远控结果上报

    // 日产保有车后装TBOX远控服务 ***end***

    // 日产保有车后装TBOX整车服务 ***start***
    FUNC225_TYPE_MSG_BROADCAST_REQ       = 1,                   // 数据上传请求(Peps广播)
    FUNC225_TYPE_L3_SET_PUSH_STATUS      = 2,                   // L3设置需要推送车辆状态数据的tbox
    // 日产保有车后装TBOX整车服务 ***end***

    // 日产保有车后装TBOX接入服务 ***start***
    FUNC226_TYPE_MSG_REMOTE_CTRL       = 1,                     // 反控请求
    // 日产保有车后装TBOX接入服务 ***end***

    // 日产保有车后装TBOX NAddVIS服务 ***start***
    FUNC227_TYPE_GET_CAR_DATA_REQ       = 1,                    // 获取车辆数据请求
    // 日产保有车后装TBOX NAddVIS服务 ***end***

    // 日产保有车后装TBOX NAddSMS服务 ***start***
    FUNC_NADD_TYPE_SHORT_MESSAGE_REQ     = 1,                    // 发送短信请求
    // 日产保有车后装TBOX NAddSMS服务 ***end***

    // vehicle information server ***start***
    FUNC201_TYPE_VEHICLE_DATA_QUERY      = 1,               // 整车数据查询
    FUNC201_TYPE_GPS_DATA_QUERY          = 2,               // GPS数据查询
    FUNC201_TYPE_DRIVE_SCORE             = 3,               // 获取驾驶评分
    FUNC201_TYPE_SET_ELEC_FENCE          = 4,               // 设置电子围栏
    FUNC201_TYPE_GET_ELEC_FENCE          = 5,               // 获取电子围栏
    FUNC201_TYPE_GET_GREEN_TRAVEL        = 6,               // 获取绿色出行信息
    FUNC201_TYPE_GET_DRIVING_TRACK       = 7,               // 获取驾驶行为轨迹的分析数据
    FUNC201_TYPE_GET_ONLINE_COUNT         = 8,               // 融资租赁在线数量统计
    FUNC201_TYPE_GET_VEHICLE_STATUS         = 9,               // 融资租赁车辆状态获取
    FUNC201_TYPE_GET_VEHICLE_TRACK_HISTORY         = 10,      // 融资租赁车辆历史轨迹获取
    FUNC201_TYPE_GET_PARKING_HISTORY     = 11,              // 融资租赁停车记录查询
    FUNC201_TYPE_DEL_DRIVING_TRACK       = 12,              // 删除驾驶行为轨迹的记录
    FUNC201_TYPE_GET_EV_STATUS_BOARD     = 13,              // 获取EV电动车状态
    FUNC201_TYPE_GET_EV_DETAIL_DATA      = 14,              // 获取EV电动车详细实时数据
    FUNC201_TYPE_GET_EV_CONST_PARAM      = 15,              // 获取EV电动车固定值参数(雷诺)
    FUNC201_TYPE_GET_EV_NISSAN_CONSTA    = 16,              // 获取EV电动车固定值(日产)
    FUNC201_TYPE_GET_EV_NISSAN_DATA      = 17,              // 获取EV电动车车联网数据(日产)
    FUNC201_TYPE_GET_EV_UPDATE_STATUS    = 18,              // 获取EV电动车升级状态
    FUNC201_TYPE_QRY_MALFUNCTION         = 19,              // 查询车辆故障
    FUNC201_TYPE_GET_TRACK_POS           = 20,              // 获取驾驶行程轨迹的抽样坐标
    FUNC201_TYPE_GET_START_POS           = 21,              // 获取起点(点火时)坐标
    FUNC201_TYPE_GET_PARKING_POS         = 22,              // 获取停车(超过30分钟)坐标
    FUNC201_TYPE_GET_EGT_CONST           = 23,              // 获取eGT车辆固定值
    FUNC201_TYPE_GET_EGT_CARDATA         = 24,              // 获取eGT车辆车联数据
    FUNC201_TYPE_GET_EV_DIAGNOSIS        = 25,              // 获取EV 诊断项结果   
    FUNC201_TYPE_GET_EVCC_DATA           = 26,              // 获取EVCC(东本)自定义(车联)数据
    FUNC201_TYPE_SET_TCUBLACKLIST        = 27,              // 设置防攻击TCU黑名单
    FUNC201_TYPE_GET_TCUBLACKLIST        = 28,              // 获取防攻击TCU黑名单
    FUNC201_TYPE_GET_EV_VENUCIA_CONST   = 29,              // 获取启辰EV车辆固定值
    FUNC201_TYPE_GET_EV_VENUCIA_CARDATA = 30,              // 获取启辰EV车辆车联数据
    FUNC201_TYPE_GET_VEHICLEREAL_STATUS = 31,              // 金融风控获取车辆实时状态
    FUNC201_TYPE_GET_VEHICLEREAL_POS    = 32,              // 金融风控获取车辆轨迹
    FUNC201_TYPE_GET_HISTORY_POSITION   = 33,              // 金融风控获取车辆历史定位
    FUNC201_TYPE_SET_FINCEVECHICLE_DATA = 34,              // 金融风控设置车辆信息
    FUNC201_TYPE_GET_FINCEONLINE_COUNT  = 35,              // 金融风控获取车辆在线数
    FUNC201_TYPE_GET_RANGE_VEHICLE      = 36,              // 金融风控获取范围内车辆
    FUNC201_TYPE_GET_GBDATAUPLOADSTATUS = 37,              // 国标平台发送结果查询  
    FUNC201_TYPE_SET_ROUTEINFO          = 38,              // 增删接入服务信息  
    FUNC201_TYPE_GET_FORWARD_INFO       = 39,              // 获取国标转发信息
	FUNC201_TYPE_GET_HEV_VEHICLESTATUS  = 40,              // 获取东本HEV车辆状态
    // vehicle information server ***end***               

    // device manager server  ***start***
    FUNC202_TYPE_DEVICE_CANCEL                 = 1,         // 设备注销
    FUNC202_TYPE_DEVICE_CHANGE                   = 2,         // 设备更换
    FUNC202_TYPE_DEVICE_FOURCODESYNC           = 3,         // 四码信息同步
    FUNC202_TYPE_DEVICE_UPDATEINFOSYNC         = 4,         // 升级信息同步
    FUNC202_TYPE_DEVICE_NETWORKALARM           = 5,         // 流量告警
    FUNC202_TYPE_DEVICE_UPDATECONTROL          = 6,         // 升级控制
    FUNC202_TYPE_DEVICE_GET_BLACKWHITELIST     = 7,         // 查询黑白名单
    FUNC202_TYPE_DEVICE_SET_BLACKWHITELIST     = 8,         // 增删黑白名单
    FUNC202_TYPE_DEVICE_UPDATECANCEL           = 9,         // 升级取消
    FUNC202_TYPE_DEVICE_GPS_UP_INTERVAL        = 10,        // 融资租赁GPS上传频率设置
    FUNC202_TYPE_DEVICE_INFORMATION            = 11,        // 设备信息查询(如车系、DCM在线状态等、后待定扩展)
    FUNC202_TYPE_DEVICE_DCM_GPS                   = 12,        // DCM GPS盒子信息同步
    FUNC202_TYPE_DEVICE_DATA_UP_CONFIG           = 13,        // 设置指定设备上报的整车和GPS数据(存储于MYSQL或HBASE)
    FUNC202_TYPE_DEVICE_VEHICLE_DATA_CONFIG       = 14,        // 设置指定设备上报的整车数据推送(至App端)
    FUNC202_TYPE_DEVICE_SET_GREY_TCU           = 15,        // 设置灰度TCU
    FUNC202_TYPE_DEVICE_GET_GREY_TCU           = 16,        // 获取灰度TCU
    FUNC202_TYPE_DEVICE_FUNCTION_OPTION        = 17,        // 设置功能选项
    FUNC202_TYPE_DEVICE_GET_TCUCOUNT           = 18,        // 获取TCU数量
    FUNC202_TYPE_DEVICE_GET_TCUPAGE            = 19,        // 分页获取TCU
    FUNC202_TYPE_DEVICE_EVGET_TCUCOUNT         = 20,        // EV获取TCU在线数
    FUNC202_TYPE_DEVICE_SETGBCHECKSTATUS       = 21,        // 国标平台车辆审核状态同步
    FUNC202_TYPE_DEVICE_EV_DEV_INFO_SYNC       = 22,        // EV设备特殊信息同步
    FUNC202_TYPE_DEVICE_SET_SPEC_INFO          = 23,        // 设置特殊设备信息
    FUNC202_TYPE_DEVICE_SET_TCU_OFFLINE        = 24,        // tcu下线处理
    FUNC202_TYPE_DEVICE_SPEED_WARN             = 25,        // 超速报警设置
    FUNC202_TYPE_DEVICE_SET_DICTIONARY         = 26,        // 设置可配置化数据字典
    FUNC202_TYPE_DEVICE_SET_UPLOADATA          = 27,        // 设置上传数据字段
    // device manager server  ***end***

    // atbox vis server  ***start***
    FUNC203_TYPE_GET_CAR_INFO                  = 1,        // 车辆设备信息管理功能 
    FUNC203_TYPE_GET_CAR_POS                   = 2,        // 车辆位置查询功能
    FUNC203_TYPE_GET_CAR_ONLINE                = 3,        // 车辆在线状态查询功能
    FUNC203_TYPE_GET_CAR_CANDATA               = 4,        // 车辆CAN数据查询功能
    FUNC203_TYPE_CAR_REMOTECTRL                = 5,        // 车辆诊断控制命令下发功能 
    FUNC203_TYPE_GET_CAR_PM25                  = 6,        // PM2.5数据查询功能 
    FUNC203_TYPE_CHANGE_DEVICE                 = 7,        // AtBox设备更换 
    FUNC203_TYPE_SET_CYCLEDATA                 = 8,        // AtBox设置周期数据 
    FUNC203_TYPE_SET_CONFIGPARAM               = 9,        // AtBox设置服务参数 
    FUNC203_TYPE_SET_ATBOX_GREY                = 10,       // AtBox设置灰度
    FUNC203_TYPE_GET_ATBOX_GREYLIST            = 11,       // AtBox获取灰度列表
    // atbox vis server  ***end***

    // GB vis server  ***start***
    FUNC204_TYPE_EVEHICLE_STATUSBOARD          = 1,        // 车辆状态看板
    FUNC204_TYPE_EVEHICLE_DETAILDATA           = 2,        // 车辆详细实时数据
    FUNC204_TYPE_EVEHICLE_PARAMCTRL            = 3,        // 车辆参数及控制
    FUNC204_TYPE_EVEHICLE_CONSTPARAM           = 4,        // 车辆固定值参数
    FUNC204_TYPE_EVEHICLE_NISSANCONST          = 5,        // 日产车辆固定值 
    FUNC204_TYPE_EVEHICLE_NISSANDATA           = 6,        // 日产车联数据
    FUNC204_TYPE_EVEHICLE_UPDATESTATUS         = 7,        // 升级状态查询
    FUNC204_TYPE_EVREMOTECONTROL               = 8,        // EV车辆控制
    FUNC204_TYPE_EVGETDIAGNOSIS                = 9,        // EV诊断项查询
    FUNC204_TYPE_EVEGTCONST                    = 10,       // eGT车辆固定值
    FUNC204_TYPE_EVEGTDATA                     = 11,       // eGT车联数据
    // GB vis server  ***end***

    // IOV-FactoryQC server  ***start***
    FUNC205_TYPE_FOURCODESYNC                  = 1,        // 工厂质检四码同步
    FUNC205_TYPE_EVEHICLEDETAILDATA            = 2,        // 工厂质检国标EV车联数据
    FUNC205_TYPE_GETVEHICLEDATA                = 3,        // 工厂质检整车数据
    FUNC205_TYPE_EVEHICLENISSANDATA            = 4,        // 工厂质检日产车联数据
    // IOV-FactoryQC server  ***end***

    // unicom sms server   ***start***
    FUN112_TYPE_UNICOM_SMS_WAKEUP              = 1,          // 短信唤醒
    FUN112_TYPE_TCU_LOG_REQUEST                = 2,          // TCU日志请求
    FUN112_TYPE_CHECK_ICCID_REQUEST            = 3,          // ICCID有效性验证请求

    // unicom sms server   ***end***

    // http client server  ***start***
    FUN113_TYPE_HTTP_CLINET_GET                = 1,          // 发送HTTP GET请求
    FUN113_TYPE_HTTP_CLIENT_POST               = 2,          // 发送HTTP POST请求
    FUN113_TYPE_HTTP_CLIENT_POST_ON_OFF_LINE   = 3,          // 发送设备上下线的HTTP POST请求
    FUN113_TYPE_HTTP_CLIENT_EV_SYNC_L3         = 4,          // 发送EV VIN到httpclient判断是否需要同步到L3
    FUN113_TYPE_HTTP_CLIENT_POST_VEH_STATUS    = 5,          // 发送车辆状态到L3
    FUN113_TYPE_HTTP_CLIENT_POST_VEH_RENAULT   = 6,          // 发送车辆状态到L3(for雷诺汽油车)
    FUN113_TYPE_HTTP_CLIENT_VKEY_POST          = 7,          // 蓝牙钥匙推送(需要等L3回包的处理,如不需要回包,直接用post)
    FUN113_TYPE_HTTP_CLIENT_DOOR_WARN_RENUALT  = 8,          // 发送车门灯锁未关告警到L3(for雷诺汽油车)
    FUN113_TYPE_HTTP_CLIENT_POST_PDI           = 9,          // 发送雷诺PDI告警到L3(for雷诺汽油车)
    FUN113_TYPE_HTTP_CLIENT_POST_LOGIN_VER     = 10,         // 发送TCU登录版本信息
    FUN113_TYPE_HTTP_CLIENT_POST_VNEXT_BATTCODE= 11,         // 发送vNext电池编码信息给L3
    // http client server  ***end***

    // 整车服务 server  ***start***
    FUN30_TYPE_IGN_ALARM                = 7,          // 点火告警开启关闭请求
    // 整车服务 server  ***end***

    FUNCTION_TYPE_TQBOX_ORDER_REQ = 1,                  // TQBox 指令下发

    // 国标接收服务  ***start***
    FUNCTION_TYPE_GB_RENA_UPDATE_GRADE  = 0x01,  // 国标雷诺设备  升级文件下载

	FUNCITON_TYPE_GB_HEV_REMOTE         = 0x40,  // Remote Control 2VP(东本)   up/down
    FUNCITON_TYPE_GB_HEV_SEND2CAR       = 0x42,  // Send2Car 2VP(东本)   up/down
    FUNCTION_TYPE_GB_DEV_QUERY          = 0x80,  // 国标设备 查询命令
    FUNCTION_TYPE_GB_DEV_SET            = 0x81,  // 国标设备 设置命令
    FUNCTION_TYPE_GB_DEV_CONTROL        = 0x82,  // 国标设备 控制命令
    FUNCITON_TYPE_GB_GET_STATUS         = 0x83,  // 国标 EVCC 获取车辆状态
    FUNCITON_TYPE_GB_EINS               = 0x84,  // 国标 EVCC 远程电检
    
    FUNCTION_TYPE_VIRTUAL_KEY           = 0xE0,  // 虚拟钥匙
    FUNCTION_TYPE_GB_CAR_CONTROL        = 0xE1,  // 车辆控制 同GB_MSG_CUSTOM_CONTROL
    FUNCTION_TYPE_GB_CAR_PKI_CTRL       = 0xE2,  // PKI车辆控制
    // 国标接收服务  ***end***

    //IOV-GBDataDeal***BEGIN***
    FUNCTION_TYPE_GB_DATADEAL           = 0x01, // 中转到GBDataDeal服务的国标消息
    FUNCTION_TYPE_LB_DATADEAL           = 0x02, // 中转到GBDataDeal服务的地标消息
    FUNCTION_TYPE_VNEXT_DATADEAL        = 0x03, // 中转到GBDataDeal服务的vNext消息
    //IOV-GBDataDeal***END***

    //国六消息***BEGIN***
    FUNCTION_TYPE_GBVI_CARLOGIN         = 0x01, // 中转到GBVIDeal服务的车辆登入
    FUNCTION_TYPE_GBVI_REAL_DATA        = 0x02, // 中转
    FUNCTION_TYPE_GBVI_RETRY_DATA       = 0x03, // 
    FUNCTION_TYPE_GBVI_CARLOGOUT        = 0x04, // 中转到GBVIDeal服务的车辆登出
    //IOV-GBDataDeal***END***


    //ATBOX_Data***BEGIN***
    FUNCTION_TYPE_CAN_DATA_REQ    = 1, // ATBOX上传CAN数据
    FUNCTION_TYPE_GPS_DATA_REQ    = 2, // ATBOX上传GPS数据
    FUNCTION_TYPE_PM_DATA_REQ    = 3, // ATBOX上传pm2.5数据
    FUNCTION_TYPE_HJE_CAN_DATA_REQ    = 40, // 雷诺HJE部分(联友盒子)上传CAN数据
    FUNCTION_TYPE_HJE_GPS_DATA_REQ    = 41, // 雷诺HJE部分(联友盒子)上传GPS数据
    FUNCTION_TYPE_HJE_RMTDIAG_REQ = 42,
    FUNCTION_TYPE_TBOX_4G_EXTEND_REQ        = 42,       // (联友盒子)平台下发扩展控制请求（包含雷诺HJE部分故障检测和蓝牙钥匙功能）
    FUNCTION_TYPE_NISSAN_CT_CAN_DATA_REQ    = 43, // 日产车(畅星盒子)上传CAN数据
    FUNCTION_TYPE_NISSAN_CT_GPS_DATA_REQ    = 44, // 日产车(畅星盒子)上传GPS数据    
    FUNCTION_TYPE_NISSAN_CT_BATCH_CAN_DATA_REQ    = 46, // 日产车(长星盒子)上传批量整车数据
    FUNCTION_TYPE_NISSAN_CT_BATCH_GPS_DATA_REQ    = 47, // 日产车(畅星盒子)上传批量GPS数据
    FUNCTION_TYPE_NISSAN_ATBOX_RMTDIAG_REQ    = 48, // 日产AtBox远程诊断
    FUNCTION_TYPE_NISSAN_CT_MALFLIST_REQ    = 49, // 日产车(畅星盒子)上传故障项清单
    FUNCTION_TYPE_NISSAN_CT_DETECT_IGNON_REQ = 50, // 日产车(畅星盒子) APP端开启车辆点火提醒
	FUNCTION_TYPE_NISSAN_CT_DCM_DATA_OFFLINE = 51, //DCM离线通知

    //ATBOX_TBOX_Data***END*** 
    //IOV-ATDS***BEGIN*** 
    FUNCTION_TYPE_DIAGNOSIS_REQ = 1, // App上传远程诊断数据
    FUNCTION_TYPE_TRACK_DATA_REQ = 2,// App上传车辆追踪模式
    //IOV-ATDS***END*** 

    //DCVP NGTP消息***BEGIN***
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT = 1,        // DCVP项目 NGTP协议 服务内部消息:DCM上传控制结果
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_VEH_DATA    = 2,        // DCVP项目 NGTP协议 服务内部消息:DCM上传车辆数据
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_CTRL_RESULT_POST = 3,    // DCVP项目 NGTP协议 服务内部消息:控制结果推送
    FUNCTION_TYPE_DCVP_NGTP_SERVER_CTRL_RESULT = 4,            // DCVP项目 NGTP协议 服务内部消息:远程控制
    FUNCTION_TYPE_DCVP_NGTP_SERVER_SMS_SEND = 5,            // DCVP项目 NGTP协议 服务内部消息:下发短信给DCM
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_VEH_WARN_POST = 6,    // DCVP项目 NGTP协议 服务内部消息:整车告警推送
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_TBOX_DIAG = 7,            // DCVP项目 NGTP协议 服务内部消息:DCM上传自诊断信息
    FUNCTION_TYPE_DCVP_NGTP_DCM_REQ_TBOX_REPLACE = 8,            // DCVP项目 NGTP协议 服务内部消息:DCM上传自诊断信息

    
    //DCVP NGTP消息***END***
    //OBU 服务消息***BEGIN***
        FUNCTION_TYPE_OBU_DCM_REQ_VEH_DATA = 2,        // OBU项目服务内部消息:DCM上传车辆数据


     //OBU 服务消息***END***
     //RSE 服务消息***BEGIN***
        FUNCTION_TYPE_RSE_DCM_REQ_VEH_DATA = 2,        // RSE项目服务内部消息:DCM上传车辆数据
    //RSE 服务消息***END***
    //IOV-VSTK***BEGIN*** 
    FUNCTION_TYPE_VSTK_GETCERTINFO = 1, // 获得证书的相应信息
    FUNCTION_TYPE_VSTK_SIMPLESIGN = 2,  // Simple签名
    FUNCTION_TYPE_VSTK_VERIFY_SIMPLESIGN = 3, // Simple验签名
    FUNCTION_TYPE_VSTK_ATTACHSIGN = 4,  // Attach签名
    FUNCTION_TYPE_VSTK_VERIFY_ATTACHSIGN = 5, // Attach验签名
    FUNCTION_TYPE_VSTK_DETACHSIGN = 6,  // Dettach签名
    FUNCTION_TYPE_VSTK_VERIFY_DETACHSIGN = 7, // Dettach验签名
    FUNCTION_TYPE_VSTK_ENCRYPTENVELOP = 8,  // 制作数字信封
    FUNCTION_TYPE_VSTK_VERIFY_DECRYPTENVELOP = 9, // 解密数字信封
    FUNCTION_TYPE_VSTK_CREATESIGNEDENVELOP = 10,  // 制作带签名的数字信封
    FUNCTION_TYPE_VSTK_VERIFY_SIGNEDENVELOP = 11, // 解密并验证带签名的数字信封
    //IOV-VSTK***END*** 

    //IOV-BTK***BEGIN*** 
    FUNCTION_TYPE_BTK_CERTIFY_APPLY = 1, // 证书申请
    FUNCTION_TYPE_BTK_CERTIFY_UPDATE = 2,// 证书更新
    FUNCTION_TYPE_BTK_CERTIFY_LOGOUT = 3, // 证书注销
    //IOV-BTK***END*** 

    //IOV-VSS***BEGIN***
    FUNC208_TYPE_VEHICLE_GPS_QUERY = 1,    //车辆位置查询
    //IOV-VSS***END***

    //IOV-TripFix***BEGIN***
    FUNC213_TYPE_VEH_DATA_REQ = 1,    // 上传整车的历史数据
    FUNC213_TYPE_GPS_DATA_REQ = 2,    // 上传GPS的历史数据
    //IOV-TripFix***END***

    //V2X-RSU***BEGIN*** 
    FUNCTION_TYPE_RSI_MSG = 1,        // 下发 RSI 消息
    FUNCTION_TYPE_RSU_CONFIG = 2,     // 设备配置
    FUNCTION_TYPE_RSU_LOG = 3,        // 日志请求
    FUNCTION_TYPE_MAP_MSG = 4,        // 下发 MAP 消息
    //V2X-RSU***END*** 

    //V2X-OBU***BEGIN*** 
    FUNCTION_TYPE_0BU_NETWORK_EVENT = 1,        // 下发 OBU 网络事件消息
    FUNCTION_TYPE_OBU_CONFIG = 2,           // 设备配置
    FUNCTION_TYPE_OBU_LOG = 3,              // 日志请求
    FUNCTION_TYPE_0BU_GLOSA_EVENT = 4,        // 下发绿波车速消息
    //V2X-OBU***END*** 


    //L2Backup***BEGIN***

    FUNCTION_TYPE_L2BU_CTRL_REQUEST = 600,            // L2Backup项目 服务内部消息:远控请求
    FUNCTION_TYPE_L2BU_SMS_SEND = 601,                // L2Backup项目 服务内部消息:下发短信给设备端

    //L2Backup***END
};

///@class  DCM_CONFIGURE_CMD_TYPE [APPCommon.h]
///@brief  DCM 设置数据功能类型
///@author jiangxiaobao
///@note   DCM下发的设置数据的功能
enum DCM_CONFIGURE_CMD_TYPE
{
    DCM_CONFIGURE_CMD_REPORT_INTERVAL = 3,                      //数据上报时间间隔
    // 车门控制，仅演示用
    //DCM_CONFIGURE_CMD_DOOR_LOCK_CONTROL = 4,                     //车门锁控制 0x01:上锁，0x00:开锁
    DCM_CONFIGURE_CMD_CAR_TYPE = 4,                             //DCM车辆类型
    DCM_CONFIGURE_CMD_DVRPHONE_TYPE = 23,        //DVR拍照控制
};

// 支持的加密标识
enum ENCRYPT_FLAG
{
    ENCRYPT_FLAG_NO_ENCRYPT = 0,            // 未加密
    ENCRYPT_FLAG_RSA_ENCRYPT = 1,            // RSA加密
    ENCRYPT_FLAG_RC4_ENCRYPT = 2,            // RC4加密
    ENCRYPT_FLAG_AES_ENCRYPT = 3,            // AES加密
    ENCRYPT_FLAG_NOT_SUPPORT                           // 加密方式不支持
};

#define PROJECT_TYPE_IOV_531 "531"    // 服务项目：东风日产 531
#define PROJECT_TYPE_IOV_FL  "iov-fl" // 服务项目：东风南方融资租赁
#define PROJECT_TYPE_IOV_EV  "iov-ev" // 服务项目：EV
#define PROJECT_TYPE_IOV_GBVI  "iov-gbvi" // 服务项目：国六
#define PROJECT_TYPE_IOV_2VP  "2VP" // 服务项目：东本2VP

#define STRING_NULL     "null"

#endif  ///*APP_COMMON_H*/

