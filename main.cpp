#include <iostream>
#include <winsock.h>
#include <string>
#include "logger.h"
//#include "ProjectCommon.h"
#include "WheatTCPServer.h"
//#include "WheatCommand.h"

//#include "WheatChatRecorder.h"

#define MYPORT 11451

int main() {
	system("chcp 65001"); // 设置为 Unicode(UTF-8 带签名) - 代码页 65001
	initLogger("log/info.log", "log/warning.log", "log/error.log");
	LOG(INFO) << "info " << "server init";

	WheatTCPServer::instance()->Run();
	//WheatTCPServer myServer(MYPORT);

	//myServer.Run();

	//myServer.CloseServer();

	return 0;
}