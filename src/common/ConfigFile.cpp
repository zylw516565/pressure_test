#include "ConfigFile.h"

#include <common/ErrorCode.h>
#include <utils/INIReader.h>
#include <utils/CommonUtil.h>

#include <iostream>     // std::ios, std::istream, std::cout
#include <fstream>      // std::filebuf
#include <sstream>      // std::stringstream 



#ifdef WIN32
const string  ConfigFileName = "../etc/PressureTest.ini";
const string  JsonFileName = "../etc/zna_vehicle_info.json";
const string  LoginReqJson = "../etc/zna_login.json";
#else
const string  ConfigFileName = "etc/PressureTest.ini";
const string  JsonFileName = "etc/zna_vehicle_info.json";
const string  LoginReqJson = "etc/zna_login.json";
#endif


using std::ios;
using std::ifstream;
using std::stringstream;


int ConfigFile::init(bool reInit)
{
    INIReader reader(ConfigFileName);

    if (reader.ParseError() < 0)
    {
        PDEBUG("Load %s failed !!!", ConfigFileName.c_str());
        return ERROR;
    }
    
    {
        appConfig.log_dir = reader.GetString("CONFIG", "logfiledir", "logs/");
        PDEBUG("appConfig.log_dir [%s]", appConfig.log_dir.c_str());
        if (appConfig.log_dir.empty())
            return ERROR;
    }

    {
        appConfig.log_file_name = reader.GetString("CONFIG", "logfilename", "app");
        PDEBUG("appConfig.log_file_name [%s]", appConfig.log_file_name.c_str());
        if (appConfig.log_file_name.empty())
            return ERROR;
    }

    {
        appConfig.log_level = reader.GetInteger("CONFIG", "loglevel", 0);
        PDEBUG("appConfig.log_level [%d]", appConfig.log_level);
        if (appConfig.log_level < 0)
            return ERROR;
    }

    {
        appConfig.ip = reader.GetString("CONFIG", "ip", "");
        PDEBUG("appConfig.ip [%s]", appConfig.ip.c_str());
        if (appConfig.ip.empty())
            return ERROR;
    }

    {
        appConfig.port = reader.GetInteger("CONFIG", "port", 0);
        PDEBUG("appConfig.port [%d]", appConfig.port);
        if (appConfig.port < 0)
            return ERROR;
    }

    {
        appConfig.thread_count = reader.GetInteger("CONFIG", "threadcount", 1);
        PDEBUG("appConfig.thread_count [%d]", appConfig.thread_count);
        if (appConfig.thread_count <= 0)
            return ERROR;
    }

    {
        appConfig.session_count = reader.GetInteger("CONFIG", "sessioncount", 1);
        PDEBUG("appConfig.session_count [%d]", appConfig.session_count);
        if (appConfig.session_count <= 0)
            return ERROR;
    }

    {
        appConfig.timeout = reader.GetInteger("CONFIG", "timeout", 5000);  //单位:ms
        PDEBUG("appConfig.timeout [%d]", appConfig.timeout);
        if (appConfig.timeout <= 0)
            return ERROR;
    }

    {
        appConfig.isusessl = reader.GetBoolean("CONFIG", "isusessl", true);
        PDEBUG("appConfig.isusessl [%d]", appConfig.isusessl?1:0);
        if (NULL == &appConfig.isusessl)
            return ERROR;
    }

    {
        appConfig.isPressureMode_ = reader.GetBoolean("CONFIG", "isPressureMode", true);
        PDEBUG("appConfig.isPressureMode [%d]", appConfig.isPressureMode_?1:0);
        if (NULL == &appConfig.isPressureMode_)
            return ERROR;
    }

//***********CA*****************
    {
        appConfig.cacert = reader.GetString("CA_FILE", "cacert", "etc/ca_na.crt");
        PDEBUG("appConfig.cacert [%s]", appConfig.cacert.c_str());
        if (appConfig.cacert.empty())
            return ERROR;
    }

    {
        appConfig.privatekey = reader.GetString("CA_FILE", "privatekey", "etc/tsp_pri_na.key");
        PDEBUG("appConfig.privatekey [%s]", appConfig.privatekey.c_str());
        if (appConfig.privatekey.empty())
            return ERROR;
    }

    {
        appConfig.certfile = reader.GetString("CA_FILE", "certfile", "etc/tsp_na.cer");
        PDEBUG("appConfig.certfile [%s]", appConfig.certfile.c_str());
        if (appConfig.certfile.empty())
            return ERROR;
    }

    {
        appConfig.isverifyserver = reader.GetBoolean("CA_FILE", "isverifyserver", true);
        PDEBUG("appConfig.isverifyserver [%d]", appConfig.isverifyserver?1:0);
        if (NULL == &appConfig.isverifyserver)
            return ERROR;
    }

    {
        appConfig.calevel = reader.GetInteger("CONFIG", "calevel", 2);
        PDEBUG("appConfig.calevel [%d]", appConfig.calevel);
        if (appConfig.calevel <= 0)
            return ERROR;
    }
    //日志模块未初始化,以上读取配置不能打印日志.用PDEBUG代替.

    return readJsonFile();
}

int ConfigFile::readJsonFile()
{
    //读取整车数据配置
    ifstream inFile;
    inFile.open(JsonFileName, ios::in);
    if (!inFile.is_open())
    {
        PDEBUG("Open [%s] failed !!!", JsonFileName.c_str());
        return ERROR;
    }

    std::stringstream strBuffer;
    strBuffer << inFile.rdbuf();
    strJsonConfig_.assign(strBuffer.str());
    if (strJsonConfig_.empty())
    {
        PDEBUG("[%s]'s content is  empty !!!", JsonFileName.c_str());
        return ERROR;
    }

    //读取登陆请求配置
    ifstream inLoginFile;
    inLoginFile.open(LoginReqJson, ios::in);
    if (!inLoginFile.is_open())
    {
        PDEBUG("Open [%s] failed !!!", LoginReqJson.c_str());
        return ERROR;
    }

    std::stringstream loginBuffer;
    loginBuffer << inLoginFile.rdbuf();
    strLoginJson_.assign(loginBuffer.str());
    if (strLoginJson_.empty())
    {
        PDEBUG("[%s]'s content is  empty !!!", LoginReqJson.c_str());
        return ERROR;
    }

    return OK;
}
