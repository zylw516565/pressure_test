/**
 *  文件服务程序入口函数
 *  zhangyl 2017.03.09
 **/
#include <iostream>
#include <stdlib.h>
#include <memory>

#include <muduo/base/AsyncLogging.h>
#include <muduo/base/Logging.h>
#include <common/Platform.h>

#include <muduo/base/Singleton.h>
#include <muduo/net/EventLoop.h>
#include <common/ConfigFile.h>


#ifndef WIN32
#include <string.h>
#include <utils/DaemonRun.h>
#endif 

#include "TCU.h"

using namespace muduo;
using namespace muduo::net;

#ifdef WIN32
//初始化Windows socket库
NetworkInitializer windowsNetworkInitializer;
#endif

off_t kRollSize = 500*1000*1000;
muduo::AsyncLogging* g_asyncLog = NULL;
void asyncOutput(const char* msg, int len)
{
  g_asyncLog->append(msg, len);
}

EventLoop g_mainLoop;
std::unique_ptr<TCU> gTCU(nullptr);

#ifndef WIN32
void prog_exit(int signo)
{
    std::cout << "program recv signal [" << signo << "] to exit." << std::endl;
    if(gTCU){
      gTCU->uninit();
    }

    g_mainLoop.quit();
    g_asyncLog->stop();
    exit(0);
}
#endif

int main(int argc, char* argv[])
{
#ifndef WIN32
    //设置信号处理
    signal(SIGCHLD, SIG_DFL);
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, prog_exit);
    signal(SIGTERM, prog_exit);


    int ch;
    bool bdaemon = false;
    while ((ch = getopt(argc, argv, "d")) != -1)
    {
        switch (ch)
        {
        case 'd':
            bdaemon = true;
            break;
        }
    }

    if (bdaemon)
        daemon_run();
#endif

    //1,先读取基本配置,如日志路径,等级
    int nRet = ConfigFile::instance().init();
    if (nRet != 0)
    {
        printf("ConfigFile::init failed!!!");
        return nRet;
    }

#ifndef WIN32
    const string logfilepath = ConfigFile::instance().getLogDir();
    if (logfilepath.empty())
    {
        printf("logdir is not set in config file");
        return 1;
    }

    //如果log目录不存在则创建之
    DIR* dp = opendir(logfilepath.c_str());
    if (dp == NULL)
    {
        if (mkdir(logfilepath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
        {
            printf("create base dir error, %s , errno: %d, %s", logfilepath.c_str(), errno, strerror(errno));
            return 1;
        }
    }
    closedir(dp);
#endif

    //2,初始化日志模块
    char name[256] = { '\0' };
    strncpy(name, argv[0], sizeof name - 1);
    muduo::AsyncLogging log(ConfigFile::instance().getLogDir() + ::basename(name), kRollSize);
    log.start();
    g_asyncLog = &log;
    muduo::Logger::setOutput(asyncOutput);
    muduo::Logger::setLogLevel(
        static_cast<Logger::LogLevel>(
        ConfigFile::instance().getLogLevel()
        ));

    //TODO:日志模块初始化完后,记录程序配置信息
    LOG_INFO << "JsonConfig:\n" << ConfigFile::instance().getJsonConfig();

    ConfigParam appParam;
    const string ip = ConfigFile::instance().getIP();
    uint16_t port = static_cast<uint16_t>(ConfigFile::instance().getPort());
    appParam.threadCount = ConfigFile::instance().getThreadCount();
    appParam.timeout = ConfigFile::instance().getTimeOut();

    fprintf(stderr, "Usage: client <total_press_time>\n");
    fprintf(stderr, "cmdtype: 0:VehicleData, 1:DictReq\n");
    fprintf(stderr, "total_press_time:n's\n");

    if (argc <= 1)
    {
        LOG_ERROR << "argc is too small!!!  argc:" << argc;
        // CAsyncLog::uninit();
        return -1;
    }

    appParam.totalPressureTime = atoi(argv[1]);
    InetAddress serverAddr(ip, port);
    gTCU = std::make_unique<TCU>(&g_mainLoop, serverAddr);
    gTCU->init(appParam);

    LOG_INFO << "TCU is init, Start Test!!!";
    g_mainLoop.loop();
    LOG_INFO << "exit TCU.";

    return 0;
}
