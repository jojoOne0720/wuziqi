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

	// ����ָ��
	// destSocket				Ŀ��ͻ��˵� Socket
	// sleeperIdWhoMakeThisCommand	��д��������ָ���˯�͵� ˯��Id
	//void SendCommand(SOCKET destSocket, int sleeperIdWhoMakeThisCommand, const WheatCommand& command);
	//void SendCommandToFdSet(fd_set destFdSet, int fdMax, int sleeperIdWhoMakeThisCommand, const WheatCommand& command, SOCKET skipSocket = -1);

	// ������ָ��ϰ���һ�η���
	//void SendMultiCommand(SOCKET destSocket, std::vector<int>& sleeperIdWhoMakeTheseCommands, const std::vector<WheatCommand>& command);

	//// �������� buf ������һ���µ� buf���м��� '\0' �ָ�
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

