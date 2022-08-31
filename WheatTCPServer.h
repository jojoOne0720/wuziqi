#pragma once
#define FD_SETSIZE 1024
#include <winsock.h>
#include <vector>
#include "playerObject.h"
#include <map>
const int port = 134567;

class WheatTCPServer {
public:
	//WheatTCPServer() {};

	static WheatTCPServer* instance();

	WheatTCPServer() { Init(port); };
	// virtual ~WheatTCPServer();

	bool Init(int port);
	void CloseServer();

	void Run();

private:

	// 发送指令
	// destSocket				目标客户端的 Socket
	// sleeperIdWhoMakeThisCommand	填写产生这条指令的睡客的 睡客Id
	//void SendCommand(SOCKET destSocket, int sleeperIdWhoMakeThisCommand, const WheatCommand& command);
	//void SendCommandToFdSet(fd_set destFdSet, int fdMax, int sleeperIdWhoMakeThisCommand, const WheatCommand& command, SOCKET skipSocket = -1);

	// 将多条指令合包后一次发送
	//void SendMultiCommand(SOCKET destSocket, std::vector<int>& sleeperIdWhoMakeTheseCommands, const std::vector<WheatCommand>& command);

	//// 连接两个 buf 而生成一个新的 buf，中间用 '\0' 分隔
	//void BufferCatenate(char* destBuf, const char* buf1, size_t buf1Size, const char* buf2, size_t buf2Size);
	//void BufferCatenate(char* destBuf, size_t offset, const char* buf1, size_t buf1Size, const char* buf2, size_t buf2Size);

	//void SendBufferToFdSet(fd_set inputFdSet, int fdMax, const char* str);
	//void SendBufferToFdSet(fd_set inputFdSet, int fdMax, const char* str, size_t len, SOCKET skipSocket = -1);

	std::map<std::string, CPlayerObject> m_mapName2Player;
	std::map<SOCKET, std::string> m_mapSocket2Name;


	WSADATA m_WSAData;
	SOCKET m_socket;
	sockaddr_in m_address;
	static WheatTCPServer* m_myServer;

	bool WSAStart();
	bool SocketInit();
	void SetServerAddress(int port);
	bool Bind();
	bool Listen();
};

