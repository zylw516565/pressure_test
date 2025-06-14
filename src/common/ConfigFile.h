#pragma once

#include <muduo/base/noncopyable.h>
#include <muduo/base/Singleton.h>
#include <string>

using std::string;

typedef struct APP_CONFIG_
{
    string log_dir;
    string log_file_name;
    int    log_level;
    string ip;
    int    port;
    int    thread_count;
    int    session_count;
    int    timeout;
    bool   isusessl;
    bool   isPressureMode_;

    string cacert;
    string privatekey;
    string certfile;
    bool   isverifyserver;
    int    calevel;
}APP_CONFIG;


class ConfigFile : muduo::noncopyable
{
public:
    ConfigFile() = default;
    ~ConfigFile() = default;

    static ConfigFile& instance() { return muduo::Singleton<ConfigFile>::instance(); }

    int init(bool reInit = false);

    const string& getLogDir() const {return appConfig.log_dir; }
    const string& getLogFileName() const {return appConfig.log_file_name; }
    const int getLogLevel()const { return appConfig.log_level; }
    const string& getIP() const { return appConfig.ip; }
    const int getPort() const { return appConfig.port; }
    const int getThreadCount()const { return appConfig.thread_count; }
    const int getSessionCount()const { return appConfig.session_count; }
    const int getTimeOut()const { return appConfig.timeout; }
    const bool isUseSSL()const { return appConfig.isusessl; }
    const bool isPressureMode()const { return appConfig.isPressureMode_; }
    const string& getCACert()const { return appConfig.cacert; }
    const string& getPrivateKey()const { return appConfig.privatekey; }
    const string& getCertFile()const { return appConfig.certfile; }
    const bool isVerifyServer()const { return appConfig.isverifyserver; }
    const int getCALevel()const { return appConfig.calevel; }

    const string& getJsonConfig()const { return strJsonConfig_; }
    const string& getLoginJson()const { return strLoginJson_; }

private:
    int readJsonFile();

private:

    string               strJsonConfig_;
    string               strLoginJson_;
    APP_CONFIG           appConfig;
};
