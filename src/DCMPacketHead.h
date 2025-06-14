///@file     DCMPacketHead.h
///@brief    DCM 消息包
///@author   tangjie
///@date     2015-01-10
///@version  v1.0.0.0
///@note     

#ifndef DCM_PACKET_HEAD_H
#define DCM_PACKET_HEAD_H

#include <memory.h>
#include <memory>

// DCM 类型
#ifndef DCM_TYPE_LY
#define DCM_TYPE_LY     0   //(NET_PACKET_TYPE_LY_TCU)         // 联友自定义协议 TCU (0)
#endif
#ifndef DCM_TYPE_YZ
#define DCM_TYPE_YZ     1   //(NET_PACKET_TYPE_YZ_OBD)         // 元征OBD协议 (1)
#endif


//////////////////////////////////////////////////////////////////////////////////////
// 联友自主协议定义
// 消息包头尾标识

/*********用新协议代替**********/
/*
#define LY_DCM_PACKET_FLAG 0xF5
//转义用到标识
#define LY_ESCAPE_CHARACTER_FLAG1   0xf4
#define LY_ESCAPE_CHARACTER_FLAG2   0xf5
#define LY_ESCAPE_CHARACTER_FLAG21   0x01
#define LY_ESCAPE_CHARACTER_FLAG22   0x02
// 最大消息长度
#define MAX_LY_DCM_PACKET_LEN 128
//消息头长度
#define  LY_DCM_PACKET_HEAD_LEN 13

///是否联友协议消息
///@param [in]    pData            接收数据
///return bool 是联友自主协议返回true，否则返回false
///@note 
inline bool IsLYDCMPacket(const char* pData)
{
    return (LY_DCM_PACKET_FLAG == pData[0]);
}

///@class  LYDCMErrorCode [DCMPacketHead.h]
///@brief  DCM 错误码
///@author tangjie
///@note   
enum LYDCMErrorCode
{
    LY_DCM_ERROR_OK = 0,                     // 成功/确认
    LY_DCM_ERROR_FAILD = 1,                  // 失败
    LY_DCM_ERROR_MSG_ERROR = 2,              // 消息有误
    LY_DCM_ERROR_NOT_SUPPORT = 3,            // 不支持
};

///@enum   LYDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM 消息类型
///@author tangjie
///@note   
enum LYDCMMSGTYPE
{
    LY_DCM_MSG_DCM_COM_RSP         = 0x0001,                 // 通用应答消息 终端发送 
    LY_DCM_MSG_DCM_QUERY_PARAM_RSP = 0x0006,                 // 参数应答消息 终端发送 
    LY_DCM_MSG_DCM_DATA_REPORT     = 0x0007,                 // 周期数据信息发送 终端发送 
    LY_DCM_MSG_DCM_QUERY_DATA_RSP  = 0x0008,                 // 查询数据信息应答 终端发送 
    LY_DCM_MSG_DCM_DATA_REISSUE    = 0x0009,                 // 数据补发 终端发送 

    LY_DCM_MSG_SERVER_COM_RSP      = 0x8001,                 // 通用应答消息 服务端发送
    LY_DCM_MSG_SERVER_SET_PARAM    = 0x8005,                 // 设置终端参数 服务端发送
    LY_DCM_MSG_SERVER_QUERY_PARAM  = 0x8006,                 // 查询终端参数 服务端发送
    LY_DCM_MSG_SERVER_QUERY_DATA   = 0x8008,                 // 查询数据信息 服务端发送
};

//终端ID长度
#define TERMINAL_ID_LEN  6


struct LYDCMMsgHead
{
    unsigned short         m_uMsgId;            //消息ID
    unsigned short         m_uMsgLen;           //消息长度
    char                   m_sTerminalId[TERMINAL_ID_LEN];       //终端ID
    unsigned short         m_uMsgSequenceNum;   //消息流水号
    unsigned char          m_cPublicKey;        //公匙

    //构造函数
    LYDCMMsgHead()
    {
        m_uMsgId = 0;
        m_uMsgLen = 0;
        memset(m_sTerminalId, 0, TERMINAL_ID_LEN);
        m_uMsgSequenceNum = 0;
        m_cPublicKey = 1;            // 1 计算出来的密钥为不加密
    }
};


//DCM消息头编码
//@param [in]    stDCMMsgHead       消息头
//@param [out]   pEncodeBuffer      编码结果
//return int 成功返回0，否则返回失败
//@note  外部保证编码结果区域的长度大于等于消息头长
int EnCodeLYDCMMsgHead(const LYDCMMsgHead& stDCMMsgHead, char* pEncodeBuffer);


//DCM消息头解码
//@param [in]    pDecodeBuffer          编码结果
//@param [out]   stDCMMsgHead            消息头
//return int 成功返回0，否则返回失败
//@note  
int DeCodeLYDCMMsgHead(const char* pDecodeBuffer, LYDCMMsgHead& stDCMMsgHead);

//DCM消息头解码扩展
//@param [in]    pszMsg                  消息
//@param [out]   stDCMMsgHead            消息头
//return int 成功返回0，否则返回失败
//@note  
int DeCodeLYDCMMsgHeadEx(const char* pszMsg, unsigned int nMsgLen, LYDCMMsgHead& stDCMMsgHead);
*/

// 联友自主协议定义（新20151014）
// 消息包头尾标识
#define LY_PACKET_PRE_FLAG_1 'l'
#define LY_PACKET_PRE_FLAG_2 'y'
#define LY_PACKET_PRE_FLAG_LEN  2

// 帧字节长度
#define LY_DCM_FRAME_LEN  2 

// 包头前置长度
#define LY_PACKET_PRE_LEN (LY_PACKET_PRE_FLAG_LEN + LY_DCM_FRAME_LEN)

// 包头长度：报头+帧长+协议版本(2字节)+业务类型（2字节）+加密标识（1字节）
#define LY_PACKET_HEAD_LEN (LY_PACKET_PRE_LEN + 5)

// CRC 16校验码长度 （2字节）
#define LY_PACKET_CRC_LEN 2

// 结束域长度（2字节）
#define LY_PACKET_END_FLAG_LEN 2

// 结束域
#define LY_PACKET_END_FLAG_1 0xBB
#define LY_PACKET_END_FLAG_2 0x66
//时间戳长度（4字节）
#define LY_PACKET_TIME_LEN 4
// 包尾长度：时间戳（4字节） + CRC16校验码（2字节）+ 结束域（2字节）
#define LY_PACKET_TAIL_LEN (LY_PACKET_TIME_LEN + LY_PACKET_CRC_LEN + LY_PACKET_END_FLAG_LEN)

// 最大消息长度
#define MAX_LY_DCM_PACKET_LEN 65535 
// 默认消息长度
#define DEFAULT_LY_DCM_PACKET_LEN 256 

// 过期登录最小时长(秒)
#define LIMIT_LOGIN_EXPIRE_MIN 90


///是否联友协议消息
///@param [in]    pData            接收数据
///return bool 是联友自主协议返回true，否则返回false
///@note 
inline bool IsLYDCMPacket(const char* pData)
{
    return (LY_PACKET_PRE_FLAG_1 == pData[0]);
}

///@class  LYDCMErrorCode [DCMPacketHead.h]
///@brief  DCM 错误码
///@note   
// enum LYDCMErrorCode
// {
//     LY_DCM_ERROR_OK = 0,                     // 成功/确认
//     LY_DCM_ERROR_FAILD = 1,                  // 失败
//     LY_DCM_ERROR_MSG_ERROR = 2,              // 消息有误
//     LY_DCM_ERROR_NOT_SUPPORT = 3,            // 不支持
// };

///@class  LYTBOXErrorCode [DCMPacketHead.h]
///@brief  DCM 错误码
///@note   
enum LYTBOXErrorCode
{
    LY_TBOX_ERROR_OK                        = 0x00,      // 成功/确认
    LY_TBOX_ERROR_VERSION_ERR               = 0x01,      // 协议版本错误
    LY_TBOX_ERROR_BUSINESS_TYPE_ERR         = 0x02,      // 业务类型未定义
    LY_TBOX_ERROR_ENCRYPT_INDISTINGUISHABLE = 0x03,      // 加密标识未能识别 (加密标识不在定义范围内)
    LY_TBOX_ERROR_INVALID_DATA              = 0x04,      // 数据无效 (业务层数据不符合规则定义要求:如协议字段长度错误等)
    LY_TBOX_ERROR_DEVICE_BUSY               = 0x05,      // 设备正忙 (监控平台或T-BOX正在处理其他事情,该情况下需要重发)
    LY_TBOX_ERROR_RC4_EXCEPTION             = 0x06,      // RC4异常(RC4错误/丢失/不存在)
    LY_TBOX_EEROR_NOT_SUPPORT_UPDATE        = 0x07,      // 不支持升级
    LY_TBOX_EEROR_CRC16_CHECK_ERR           = 0x08,      // CRC校验错误
    LY_TBOX_ERROR_RSA_EXCEPTION             = 0x09,      // RSA异常(RSA错误/丢失/不存在)
    LY_TBOX_EEROR_RSA_DECRYPT_ERR           = 0x0A,      // RSA解密错误 (解密失败/数据源长度不对)
    LY_TBOX_EEROR_NOT_LOGIN                 = 0x0B,      // 未登录(未注册(雷诺TBOX))
    LY_TBOX_ERROR_DB_ERROR                  = 0x0C,      // 数据库操作失败
    LY_TBOX_ERROR_RSA_GEN_FAIL              = 0x0D,      // RSA生成失败
	LY_TBOX_ERROR_AES_EXCEPTION             = 0x0E,      // RSA异常(RSA错误/丢失/不存在)
    LY_TBOX_EEROR_AES_DECRYPT_ERR           = 0x0F,      // RSA解密错误 (解密失败/数据源长度不对)

    // TODO: 以下错误码不应该有一样的，不好排查问题
	LY_TBOX_ERROR_PROTOBUF_PARSE_ERROR = 49,             //protobuf解析错误
    // 登录流程错误码***begin***
    LY_TBOX_EEROR_LOGIN_DCMNO_ERR = 50,                  // DCM编号错误(含不可见字符)
    LY_TBOX_EEROR_LOGIN_MSG_LEN_ERR = 51,                // 消息长度错误
    LY_TBOX_EEROR_NISSAN_LOGIN_4CODE_ERR = 52,           // 四码校验出错
    LY_TBOX_EEROR_LOGIN_VIN_ERR = 53,                    // VIN码错误(含不可见字符)
    LY_TBOX_EEROR_LOGIN_DASN_ERR = 54,                   // DASN错误(含不可见字符)
    LY_TBOX_EEROR_LOGIN_ICCID_ERR = 55,                  // ICCID错误(含不可见字符)
    LY_TBOX_EEROR_LOGIN_EXPIRE_REQ = 56,                 // 过期登录请求(TCU登录时间戳较当前时间太久)
    LY_TBOX_EEROR_LOGIN_INVALID_CERT = 57,               // 证书已吊销
    // 登录流程错误码***end***

    // 更新RC4流程错误码***begin***
    LY_TBOX_EEROR_RSA_DISENABLE = 60,                      // RSA没收到响应
    LY_TBOX_EEROR_RC4_LEN_ERR  = 61,                       // RC4长度不匹配
    LY_TBOX_EEROR_RC4_TOO_LONG = 62,                       // RC4长度超出范围
    LY_TBOX_EEROR_RC4_CRC_ERR  = 63,                       // RSA解密后的数据CRC校验出错
    // 更新RC4流程错误码***end***
    
    // 数据包流程错误码***begin***
    LY_TBOX_EEROR_PACK_PACK_CRC_ERR = 70,                  // 各包内的CRC校验错误
    LY_TBOX_EEROR_PACK_FORWORD_ERR = 71,                   // 转发失败
    // 数据包流程错误码***end***

    // 蓝牙连接状态错误码***begin***
    LY_TBOX_EEROR_BLUETOOTH_FORWORD_ERR = 50,             // 转发失败
    // 蓝牙连接状态错误码***end***

    // 电子围栏报警错误码***begin***
    LY_TBOX_EEROR_FENCEALERT_FORWORD_ERR = 50,             // 电子围栏报警 转发失败
    // 电子围栏报警错误码***end***

    // Rena Register错误码***begin***
    LY_TBOX_EEROR_RENA_REGISTER_DCMNO_ERR = 50,             // DCM编号错误
    // Rena Register错误码***end***

    // Rena Data 错误码***begin***
    LY_TBOX_ERROR_RENA_DATA_PACK_ERR = 50,                        // 分包错误
    LY_TBOX_EEROR_RENA_DATA_PACK_INDEX_ERR = 51,                  // 分包序号错误
    LY_TBOX_EEROR_RENA_DATA_PACK_LEN_ERR = 52,                    // 分包长度错误
    // Rena Data错误码***end***

    // T-BOX发送EBD状态(0x040E)错误码***begin***
    LY_TBOX_EEROR_EBD_STA_EBDNO_ERR = 50,               // DCM为空或者格式错误
    LY_TBOX_EEROR_EBD_STA_VIN_ERR = 51,                 // VIN码为空或者格式错误
    // T-BOX发送EBD状态(0x040E)错误码***end***

};

// TBOX类 (TBOX、雷诺TCU、日产TCU) 协议版本

// 支持的版本号
enum SUPPORT_TBOX_VERSION
{
    VERSION_TBOX_NUMBER_NULL               = 0x0200,        // 版本NULL  用于开始位置比较
    VERSION_TBOX_NUMBER_1                  = 0x0201,        // 版本1
    VERSION_TBOX_NUMBER_2                  = 0x0202,        // 版本2
    VERSION_TBOX_NUMBER_3                  = 0x0203,        // 版本3
    VERSION_TBOX_NUMBER_4                  = 0x0204,        // 版本4
    VERSION_TBOX_NUMBER_MAX,                                // 支持版本最大值
};

// 雷诺支持的版本
enum SUPPORT_RENAULT_VERSION
{
    VERSION_RENAULT_NUMBER_NULL               = 0x0300,         // 版本NULL  用于开始位置比较
    VERSION_RENAULT_NUMBER_1                  = 0x0301,         // 版本1
    VERSION_RENAULT_NUMBER_2                  = 0x0302,         // 版本2
    VERSION_RENAULT_NUMBER_3                  = 0x0303,         // 版本3
    VERSION_RENAULT_NUMBER_4                  = 0x0304,         // 版本4
    VERSION_RENAULT_NUMBER_MAX,                                 // 支持版本最大值
};

// 易租车支持的版本
enum SUPPORT_EASYCAR_VERSION
{
    VERSION_EASYCAR_NUMBER_NULL               = 0x0400,         // 版本NULL  用于开始位置比较
    VERSION_EASYCAR_NUMBER_1                  = 0x0401,         // 版本1
    VERSION_EASYCAR_NUMBER_MAX,                                 // 支持版本最大值
};

// 日产TCU支持的版本
enum SUPPORT_NISSANTBOX_VERSION
{
	VERSION_NISSANTBOX_NUMBER_NULL               = 0x0500,         // 版本NULL  用于开始位置比较
	VERSION_NISSANTBOX_NUMBER_01                 = 0x0501,         // 版本01 531、322
	VERSION_NISSANTBOX_NUMBER_02                 = 0x0502,         //雷诺hje版本协议
	VERSION_NISSANTBOX_NUMBER_10                 = 0x0510,         // 版本10   PDI
	VERSION_NISSANTBOX_NUMBER_11				 = 0x0511,         // 版本20   PDI
	VERSION_NISSANTBOX_NUMBER_MAX,                                 // 支持版本最大值
};

///@enum   LYDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM 消息类型
///@author jiangxiaob
///@note   
enum LYDCMMSGTYPE
{
    LY_DCM_MSG_TBOX_LOGIN_REQ         = 0x0001,                 // 登录请求 终端发送
    LY_DCM_MSG_TBOX_RENA_REGISTER_REQ = 0x0002,                 // T-BOX向服务端发送注册请求（兼容TCU）
    LY_DCM_MSG_TBOX_RENA_LOGOUT_REQ   = 0x007F,                 // T-BOX向服务端发送登出请求
    LY_DCM_MSG_TBOX_HEARTBEAT_REQ     = 0x0101,                 // 心跳请求 终端发送     
    LY_DCM_MSG_TBOX_RSA_KEY_RSP       = 0x0201,                 // 远传RSA密钥传递
    LY_DCM_MSG_TBOX_RC4_KEY           = 0x0202,                 // 远传RC4密钥传递
    LY_DCM_MSG_TBOX_AUTH_UPDATE       = 0x0301,                 // 鉴权更新
    LY_DCM_MSG_TBOX_CONFIGURE_RSP     = 0x0401,                 // 配置信息 终端发送 
    LY_DCM_MSG_TBOX_DATA_PACK         = 0x0402,                 // 打包数据 终端发送 
    LY_DCM_MSG_TBOX_UPDATE_REQ        = 0x0403,                 // T-BOX向监控平台发送软件版本信息
    LY_DCM_MSG_TBOX_UPDATE_DATA       = 0x0404,                 // T-BOX发送升级请求
    LY_DCM_MSG_TBOX_UPDATE_CHECK      = 0x0405,                 // T-BOX向服务端发送新软件包校验结果
    LY_DCM_MSG_TBOX_BLUETOOTH_CNT_STA = 0x0406,                 // T-BOX向服务端发送手机连接状态
    LY_DCM_MSG_TBOX_ELEC_FENCE_RSP    = 0x0407,                 // T-BOX响应电子围栏设置
    LY_DCM_MSG_TBOX_ELEC_FENCE_ALERT  = 0x0408,                 // T-BOX上传电子围栏报警
    LY_DCM_MSG_TBOX_RENA_DATA_ALERT   = 0x0409,                 // T-BOX向服务端发送数据和报警
    LY_DCM_MSG_TBOX_DEL_ELEC_FENCE_RSP = 0x040A,                // T-BOX响应删除电子围栏设置
    LY_DCM_MSG_TBOX_EMER_RESCUE_REQ   = 0x040B,                 // T-BOX发送紧急救援请求
    LY_DCM_MSG_TBOX_SET_PARAM_RSP     = 0x040C,                 // T-BOX响应服务端参数设置
    LY_DCM_MSG_TBOX_CONTROL_RSP       = 0x040D,                 // T-BOX响应服务端控制请求
    LY_DCM_MSG_TBOX_EBD_ON_OFF_LINE   = 0x040E,                 // EBD上线和下线通知

	LY_DCM_MSG_NISSAN_TBOX_LOGIN_REQ  = 0x0601,                 // NISSAN-T-BOX向监控平台发送注册请求
    LY_DCM_MSG_NISSAN_TBOX_RSA_LOGIN_REQ = 0x0602,              // NISSAN-T-BOX向监控平台发送注册请求(要求返回RSA密钥)
    LY_DCM_MSG_NISSAN_TBOX_RC4_KEY_REQ       = 0x0603,              // NISSAN-T-BOX远传RC4密钥传递
	LY_DCM_MSG_NISSAN_TBOX_HEARTBEAT_REQ     = 0x0701,                 // NISSAN-T-BOX心跳请求 终端发送
	LY_DCM_MSG_NISSAN_TBOX_RSA_KEY_RSP       = 0x0801,                 // NISSAN-T-BOX收到远传RSA公钥后向监控平台应答 远传RSA密钥传递
	LY_DCM_MSG_NISSAN_TBOX_RC4_KEY           = 0x0802,                 // NISSAN T-BOX向监控平台发送远传RC4密钥 远传RC4密钥传递
	LY_DCM_MSG_NISSAN_TBOX_AUTH_UPDATE       = 0x0901,                 // NISSAN T-BOX向监控平台请求更新鉴权码 鉴权更新
	LY_DCM_MSG_NISSAN_TBOX_CONFIGURE_RSP     = 0x0A01,                 // NISSAN T-BOX响应监控平台的配置请求 配置信息 终端发送
	LY_DCM_MSG_NISSAN_TBOX_QUERYINFO_RSP     = 0x0A02,                 // NISSAN T-BOX响应监控平台的查询信息请求 终端发送
	LY_DCM_MSG_NISSAN_TBOX_DATA              = 0x0A03,                 // NISSAN T-BOX向监控平台发送整车数据
    LY_DCM_MSG_NISSAN_TBOX_DATA_NEW          = 0x0B03,                 // NISSAN T-BOX向监控平台发送整车数据(新版本的协议)
	LY_DCM_MSG_NISSAN_TBOX_GPS               = 0x0A04,                 // NISSAN T-BOX向监控平台发送GPS数据
	LY_DCM_MSG_NISSAN_TBOX_ALERT             = 0x0A05,          // NISSAN T-BOX向监控平台发送报警数据
	LY_DCM_MSG_NISSAN_TBOX_CONTROL_RSP       = 0x0A06,          // NISSAN T-BOX响应监控平台的车辆反控请求
    LY_DCM_MSG_NISSAN_TBOX_RMTDIAG_RSP       = 0x0A09,          // T-BOX向监控平台发送故障检测应答
    LY_DCM_MSG_NISSAN_TBOX_WAKEUPDVR_RSP     = 0x0A0A,          // T-BOX向监控平台发送DVR唤醒应答
    LY_DCM_MSG_NISSAN_TBOX_FAULTLIST_REQ     = 0x0A10,          // T-BOX向监控平台上传支持的故障清单

    //这几个ID待定
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_VERSION    = 0x0403,                 // NISSAN T-BOX请求升级版本信息
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_DATA       = 0x0404,                 // NISSAN T-BOX请求升级包数据
    LY_DCM_MSG_NISSAN_TBOX_UPDATE_CHECK      = 0x0405,                 // NISSAN T-BOX上传升级状态

	//LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_START_REQ = 0x0B01,             // NISSAN T-BOX向监控平台发送启动升级通知
	LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_CANCEL_REQ = 0x0C02,            // NISSAN T-BOX向监控平台发送取消TCU升级响应 0x0C02
	LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_PROGRESS_REQ = 0x0C03,          // NISSAN T-BOX向监控平台发送升级进度 0x0C03

    LY_DCM_MSG_SERVER_LOGIN_RSP       = 0x8001,                 // 登录响应 服务端发送
    LY_DCM_MSG_SERVER_RENA_REGISTER_RSP = 0x8002,                 // 服务端响应注册请求（兼容TCU）
    LY_DCM_MSG_SERVER_RENA_LOGOUT_RSP = 0x807F,                 // 服务端响应登出请求
    LY_DCM_MSG_SERVER_HEARTBEAT_RSP   = 0x8101,                 // 心跳响应 服务端发送    
    LY_DCM_MSG_SERVER_RSA_KEY         = 0x8201,                 // 远传RSA密钥传递
    LY_DCM_MSG_SERVER_RC4_KEY         = 0x8202,                 // 远传RC4密钥传递
    LY_DCM_MSG_SERVER_AUTH_UPDATE     = 0x8301,                 // 鉴权更新
    LY_DCM_MSG_SERVER_CONFIGURE       = 0x8401,                 // 配置信息 服务端发送
    LY_DCM_MSG_SERVER_DATA_PACK       = 0x8402,                 // 打包数据 服务端发送
    LY_DCM_MSG_SERVER_UPDATE_CMD      = 0x8403,                 // 监控平台向T-BOX发送软件更新应答
    LY_DCM_MSG_SERVER_UPDATE_DATA     = 0x8404,                  // 监控平台响应T-BOX升级请求
    LY_DCM_MSG_SERVER_UPDATE_CHECK    = 0x8405,                 // 服务端对校验结果的应答
    LY_DCM_MSG_SERVER_BLUETOOTH_CNT_STA = 0x8406,               // 服务端收到手机连接状态后的应答
    LY_DCM_MSG_SERVER_ELEC_FENCE      = 0x8407,                 // 服务器向T-BOX发送电子围栏设置
    LY_DCM_MSG_SERVER_ELEC_FENCE_ALERT_RSP  = 0x8408,           // 服务器收到电子围栏预警的应答
    LY_DCM_MSG_SERVER_RENA_DATA_ALERT_RSP   = 0x8409,           // 服务端收到数据和报警后的应答（兼容TCU）
    LY_DCM_MSG_SERVER_DEL_ELEC_FENCE    = 0x840A,               // 服务端向T-BOX发送删除电子围栏设置
    LY_DCM_MSG_SERVER_EMER_RESCUE_RSP   = 0x840B,               // 服务端响应T-BOX紧急救援请求
    LY_DCM_MSG_SERVER_SET_PARAM_RSP     = 0x840C,               // 服务端向T-BOX下发参数设置请求
    LY_DCM_MSG_SERVER_CONTROL_RSP       = 0x840D,               // 服务端向T-BOX下发控制请求
    LY_DCM_MSG_SERVER_EBD_ON_OFF_LINE   = 0x840E,                // EBD上线和下线通知
    LY_DCM_MSG_SERVER_QUERY_PARAM       = 0x840F,               // 服务端向T-BOX下发参数查询请求

    LY_DCM_MSG_SERVER_NISSAN_LOGIN_RSP       = 0x8601,           // NISSAN T-BOX登录响应 服务端发送
    LY_DCM_MSG_SERVER_NISSAN_RSA_LOGIN_RSP   = 0x8602,           // NISSAN T-BOX登录响应 服务端发送(返回RSA密钥)
    LY_DCM_MSG_SERVER_NISSAN_RC4_KEY_RSP     = 0x8603,           // NISSAN 监控平台收到远传RC4密钥后向T-BOX应答 远传RC4密钥传递
    LY_DCM_MSG_SERVER_NISSAN_HEARTBEAT_RSP   = 0x8701,           // NISSAN T-BOX心跳响应 服务端发送 
    //LY_DCM_MSG_SERVER_NISSAN_RSA_KEY         = 0x8801,           // NISSAN 监控平台向T-BOX发送远传RSA公钥 远传RSA密钥传递
    //LY_DCM_MSG_SERVER_NISSAN_RC4_KEY         = 0x8802,           // NISSAN 监控平台收到远传RC4密钥后向T-BOX应答 远传RC4密钥传递
    //LY_DCM_MSG_SERVER_NISSAN_AUTH_UPDATE     = 0x8901,           // NISSAN 监控平台响应更新鉴权码请求 鉴权更新
    LY_DCM_MSG_SERVER_NISSAN_CONFIGURE       = 0x8A01,           // NISSAN 监控平台对T-BOX进行参数配置 配置信息 服务端发送
    LY_DCM_MSG_SERVER_NISSAN_QUERYINFO       = 0x8A02,           // NISSAN 监控平台查询T-BOX信息 配置信息 服务端发送
    //LY_DCM_MSG_SERVER_NISSAN_DATA_RSP        = 0x8A03,           // NISSAN 监控平台收到整车数据后的应答
    LY_DCM_MSG_SERVER_NISSAN_DATA_RSP_NEW    = 0x8B03,           // NISSAN 监控平台收到整车数据后的应答(新版本的协议)
    LY_DCM_MSG_SERVER_NISSAN_GPS_RSP         = 0x8A04,           // NISSAN 监控平台收到GPS数据后的应答
    LY_DCM_MSG_SERVER_NISSAN_ALERT_RSP       = 0x8A05,           // NISSAN 监控平台收到报警数据后的应答
    LY_DCM_MSG_SERVER_NISSAN_CONTROL         = 0x8A06,           // NISSAN 监控平台车辆反控请求
    LY_DCM_MSG_SERVER_NISSAN_NETWORKALARM_RSP = 0x8A07,          // NISSAN 监控平台发送流量统计
    LY_DCM_MSG_SERVER_NISSAN_RMTDIAG           = 0x8A09,         // NISSAN 监控平台车辆远程诊断请求
    LY_DCM_MSG_SERVER_NISSAN_WAKEUPDVR         = 0x8A0A,         // NISSAN 监控平台车辆DVR唤醒请求
    LY_DCM_MSG_SERVER_NISSAN_FAULTLIST_RSP     = 0x8A10,         // NISSAN 监控平台向T-BOX发送故障清单响应

    /*雷诺HJE部分整车消息ID begin ymj20181122*/    
    LY_DCM_MSG_RENAULT_TBOX_DATA             = 0x0B04,           // 雷诺hje T-BOX向监控平台发送整车数据
    LY_DCM_MSG_SERVER_RENAULT_DATA_RSP       = 0x8B04,           // 雷诺hje 监控平台收到整车数据后的应答
    LY_DCM_MSG_DIAGNOSIS_REQ          = 0x8A0E, //雷诺hje 监控平台向T-BOX发送诊断请求
	LY_DCM_MSG_DIAGNOSIS_RSP          = 0x0A0E, //雷诺hje T-BOX向监控平台发送诊断应答
    /*雷诺HJE部分整车消息ID end ymj20181122*/
    
    //这几个ID待定
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_VERSION  = 0x8403,           // NISSAN 监控平台返回升级信息(包括地址)    
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_DATA     = 0x8404,           // NISSAN 监控平台返回升级包信息
    LY_DCM_MSG_SERVER_NISSAN_UPDATE_CHECK    = 0x8405,           // NISSAN 监控平台处理升级状态响应

    LY_DCM_MSG_SERVER_NISSAN_UPDATEFILECONTROL_REQ = 0x8C01,     // NISSAN 监控平台向T-BOX发送升级控制请求
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPDATEFILECONTROL_RSP = 0x0C01,   // NISSAN T-BOX向监控平台发送升级控制响应
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_START_RSP = 0x8B01,       // 监控平台响应启动升级通知
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_CANCEL_RSP = 0x8C02,      // 监控平台向T-BOX发送取消TCU升级请求 0x8C02
    LY_DCM_MSG_NISSAN_TBOX_OTA_UPGRADE_PROGRESS_RSP = 0x8C03,    // 监控平台向T-BOX发送升级进度响应 0x8C03
    LY_DCM_MSG_TBOX_4G_EXTEND_CMD_RSP = LY_DCM_MSG_DIAGNOSIS_RSP,           // 监控平台下发扩展控制应答（含蓝牙钥匙功能）
    LY_DCM_MSG_TBOX_4G_EXTEND_CMD_REQ = LY_DCM_MSG_DIAGNOSIS_REQ,           // 监控平台下发扩展控制请求（含蓝牙钥匙功能）
    LY_DCM_MSG_TBOX_TCU_EXTEND_CMD_RSP = 0x8A0F,          // 监控平台向T-BOX发送扩展数据应答
    LY_DCM_MSG_TBOX_TCU_EXTEND_CMD_REQ = 0x0A0F,          // T-BOX发送扩展数据请求

	//证书下载相关
	LY_DCM_MSG_CERTIFICATE_STATUS_REQ = 0x0D01,			//T-BOX向后台发送证书请求/上报证书状态请求
	LY_DCM_MSG_CERTIFICATE_STATUS_RSP = 0x8D01,			//监控平台收到证书请求的应答
	LY_DCM_MSG_CERTIFICATE_DELIEVR_REQ = 0x8D02,	    //监控平台下发证书到T-BOX
	LY_DCM_MSG_CERTIFICATE_DELIEVR_RSP = 0x0D02,			//T-BOX收到监控平台下发证书数据的响应

    LY_DCM_MSG_NISSAN_TBOX_GET_VIN_REQ = 0x0E01,        // 雷诺 T-BOX向监控平台发送获取VIN请求 0x0D01
    LY_DCM_MSG_NISSAN_TBOX_GET_VIN_RSP = 0x8E01,        // 雷诺 T-BOX向监控平台发送获取VIN应答 0x0D01
    LY_DCM_MSG_NISSAN_TBOX_WRITE_VIN_REQ = 0x0E02,      // 雷诺 T-BOX向监控平台发送VIN码写入情况请求 0x0D02
    LY_DCM_MSG_NISSAN_TBOX_WRITE_VIN_RSP = 0x8E02,      // 雷诺 T-BOX向监控平台发送VIN码写入情况应答 0x0D02

    //可配置化动态协议 begin
    LY_DCM_MSG_DYNAMIC_DATA_UPLOAD_REQ   = 0x0CA0,      //T-BOX向平台发送可配置化整车数据请求
    LY_DCM_MSG_DYNAMIC_DATA_UPLOAD_RSP   = 0x8CA0,      //T-BOX向平台发送可配置化整车数据收到的响应
    LY_DCM_MSG_TCU_UPGRADE_DICT_REQ      = 0x8CA1,      //平台通知TCU升级车型字典请求
    LY_DCM_MSG_TCU_UPGRADE_DICT_RSP      = 0x0CA1,      //TCU向平台回复升级车型字典后的响应
    LY_DCM_MSG_TCU_UPLOAD_DICTIONARY_REQ = 0x0CA2,      //TCU启动时,向平台上传车型字典请求
    LY_DCM_MSG_TCU_UPLOAD_DICTIONARY_RSP = 0x8CA2,      //TCU启动时,向平台上传车型字典响应
    //可配置化动态协议 end
};

///@struct LYDCMMsgHead [DCMPacketHead.h]
///@brief  LY DCM 消息头
///@note   
struct LYDCMMsgHead
{
    char                                m_cPreFlag[LY_PACKET_PRE_FLAG_LEN]; // 前置部分，包头前置标志：ly
    unsigned short                      m_uPacketLen;                       // 包长度
    unsigned short                      m_uVersion;                         // 协议版本
    unsigned short                      m_uMsgID;                           // 业务ID 
    unsigned char                       m_cSecretFlag;                      // 加密标识

    ///构造函数
    ///return
    LYDCMMsgHead()
    {
        m_cPreFlag[0] = LY_PACKET_PRE_FLAG_1;
        m_cPreFlag[1] = LY_PACKET_PRE_FLAG_2;
        m_uPacketLen = 0;
        m_uVersion = VERSION_TBOX_NUMBER_1;   // 默认为版本1
        m_cSecretFlag = 0;            // 初始为不加密
    }
};

typedef std::shared_ptr<LYDCMMsgHead> LYDCMMsgHeadPtr;

//DCM消息头编码
//@param [in]    LYDCMPacketHead       消息头
//@param [out]   pEncodeBuffer      编码结果
//return int 成功返回0，否则返回失败
//@note  外部保证编码结果区域的长度大于等于消息头长
int EnCodeLYDCMMsgHead(const LYDCMMsgHead& stDCMMsgHead, char* pEncodeBuffer);


//DCM消息头解码
//@param [in]    pDecodeBuffer          编码结果
//@param [out]   stDCMMsgHead            消息头
//return int 成功返回0，否则返回失败
//@note  
int DeCodeLYDCMMsgHead(const char* pDecodeBuffer, LYDCMMsgHead& stDCMMsgHead);



//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////
// 元征协议定义
// 包头前缀
#define YZ_PACKET_PRE_FLAG_1 'L'
#define YZ_PACKET_PRE_FLAG_2 'Y'
#define YZ_PACKET_PRE_FLAG_LEN  2

// 帧字节长度
#define YZ_DCM_FRAME_LEN  2 

// 包头前置长度
#define YZ_PACKET_PRE_LEN (YZ_PACKET_PRE_FLAG_LEN + YZ_DCM_FRAME_LEN)

// 包头长度：报头+帧长+业务ID（2字节）+公钥（1字节）
#define YZ_PACKET_HEAD_LEN (YZ_PACKET_PRE_LEN + 3)

// CRC 16校验码长度 （2字节）
#define YZ_PACKET_CRC_LEN 2

// 元征时间戳
#define YZ_PACKE_TIME_LEN 4

// 包尾长度：时间戳（4字节） + CRC16校验码（2字节）
#define YZ_PACKET_TAIL_LEN (4 + YZ_PACKET_CRC_LEN)

// 最大消息长度
#define MAX_YZ_DCM_PACKET_LEN 1024 
// 默认消息长度
#define DEFAULT_YZ_DCM_PACKET_LEN 256 

///@enum   YZDCMMSGTYPE [DCMPacketHead.h]
///@brief  DCM 消息类型
///@author tangjie
///@note   
enum YZDCMMSGTYPE
{
    YZ_DCM_MSG_DCM_HEARTBEAT_REQ   = 0x0001,                 // 心跳请求 终端发送 
    YZ_DCM_MSG_DCM_LOGIN_REQ       = 0x0002,                 // 登录请求 终端发送 
    YZ_DCM_MSG_DCM_DATA_GPS        = 0x0003,                 // GPS数据 终端发送 
    YZ_DCM_MSG_DCM_DATA_FLOW       = 0x0004,                 // 数据流 终端发送 
    YZ_DCM_MSG_DCM_FAULT_REPORT    = 0x0005,                 // 故障上报 终端发送 
    YZ_DCM_MSG_DCM_CONFIGURE       = 0x0006,                 // 配置信息 终端发送 
    YZ_DCM_MSG_DCM_PUSH            = 0x0007,                 // 推送消息 终端发送 
    YZ_DCM_MSG_DCM_DATA_TRIP       = 0x0008,                 // 行程统计信息 终端发送 
    YZ_DCM_MSG_DCM_DATA_PACK       = 0x0009,                 // 打包数据 终端发送 
    YZ_DCM_MSG_DCM_ALERT_UP        = 0x000A,                 // 告警上报或告警清除
    YZ_DCM_MSG_DCM_VIN_UP          = 0x000B,                 // 上传VIN码

    YZ_DCM_MSG_SERVER_HEARTBEAT_RSP= 0x1001,                 // 心跳响应 服务端发送
    YZ_DCM_MSG_SERVER_LOGIN_RSP    = 0x1002,                 // 登录响应 服务端发送
    YZ_DCM_MSG_SERVER_FAULT_RSP    = 0x1005,                 // 故障码请求响应 服务端发送
    YZ_DCM_MSG_SERVER_CONFIGURE    = 0x1006,                 // 配置信息 服务端发送
    YZ_DCM_MSG_SERVER_PUSH         = 0x1007,                 // 推送消息 服务端发送
    YZ_DCM_MSG_SERVER_DATA_TRIP    = 0x1008,                 // 行程统计信息 服务端发送
    YZ_DCM_MSG_SERVER_DATA_PACK    = 0x1009,                 // 打包数据 服务端发送
    YZ_DCM_MSG_SERVER_ALERT_RSP    = 0x100A,                 // 告警上报响应 服务端发送
    YZ_DCM_MSG_SERVER_VIN_UP       = 0x100B,                 // 上传VIN码响应 服务端发送
};

///@struct YZDCMPacketHead [DCMPacketHead.h]
///@brief  YZ DCM 消息头
///@author tangjie
///@note   
struct YZDCMPacketHead
{
    char                                m_cPreFlag[YZ_PACKET_PRE_FLAG_LEN]; // 前置部分，包头前置标志：LY
    unsigned short                      m_uPacketLen;                       // 包长度
    unsigned short                      m_uMsgID;                           // 业务ID 
    unsigned char                       m_cPublicKey;                       // 公匙

    ///构造函数
    ///return
    YZDCMPacketHead()
    {
        m_cPreFlag[0] = YZ_PACKET_PRE_FLAG_1;
        m_cPreFlag[1] = YZ_PACKET_PRE_FLAG_2;
        m_uPacketLen = 0;
        m_cPublicKey = 1;            // 1 计算出来的密钥为不加密
    }
};


///是否元征协议消息  "LY" 0x4C 0x59
///@param [in]    pData            接收数据
///return bool 是元征协议返回true，否则返回false
///@note 
inline bool IsYZDCMPacket(const char* pData)
{
    return (YZ_PACKET_PRE_FLAG_1 == pData[0]);
}

///DCM消息头编码
///@param [in]    stYZPacketHead   消息头
///@param [out]   pEnCodeBuffer    编码结果
///return int 成功返回0，否则返回失败
///@note  
int EnCodeYZDCMPacketHead(const YZDCMPacketHead& stYZPacketHead, char* pEnCodeBuffer);

///DCM消息头解码
///@param [in]    pDecodeBuffer    数据
///@param [out]   stYZPacketHead   消息头
///return int 成功返回0，否则返回失败
///@note  
int DeCodeYZDCMPacketHead(const char* pDecodeBuffer, YZDCMPacketHead& stYZPacketHead);


//////////////////////////////////////////////////////////////////////////////////////

#endif  /*DCM_PACKET_HEAD_H*/
