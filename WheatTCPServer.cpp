#include "WheatTCPServer.h"
#include <iostream>
#include "logger.h"
#pragma comment(lib, "ws2_32.lib")

WheatTCPServer* WheatTCPServer::m_myServer = nullptr;

WheatTCPServer* WheatTCPServer::instance() {
	if (m_myServer == nullptr)
		m_myServer = new WheatTCPServer();
	return m_myServer;
}



bool WheatTCPServer::Init(int port) {
	m_mapSocket2Name.clear();
	if (WSAStart() == false) {
		return false;
	}
	if (SocketInit() == false) {
		return false;
	}
	SetServerAddress(port);
	if (Bind() == false) {
		return false;
	}
	if (Listen() == false) {
		return false;
	}

	SetSocketOpt(m_socket);
	return true;
}

void WheatTCPServer::CloseServer() {
	closesocket(m_socket);
	WSACleanup();
}

void WheatTCPServer::HandleMessge(SOCKET socket) {


	//Socket2Name::iterator iter = m_mapSocket2Name.find(socket);
	//if (iter == m_mapSocket2Name.end()) {
	//}
	//Name2Player::iterator palyer = m_mapName2Player.find(iter->second);
	//if (palyer == m_mapName2Player.end()) {

	//}
}

void WheatTCPServer::Run()
{
	LOG(INFO) << "Server Start to Run";
	//WheatChatRecorder wheatChatRecorder;

	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(m_socket, &fd);

	int fdMax = static_cast<int>(m_socket);

	while (1) {
		fd_set readSet = fd;

		timeval time = { 0, 5000 };

		int selectRes = select(0, &readSet, NULL, NULL, &time);

		// printf("selectRes = %d\n", selectRes);
		// printf("FD_ISSET = %d\n", FD_ISSET(m_socket, &fdTemp));

		if (selectRes > 0) {
			if (FD_ISSET(m_socket, &readSet)) {
				sockaddr_in clientAddr;
				int len = sizeof(sockaddr_in);

				SOCKET clientSocket = accept(m_socket, (sockaddr*)&clientAddr, &len);
				FD_SET(clientSocket, &fd);
				SetSocketOpt(clientSocket);
				CPlayerObject* newPlayer = new CPlayerObject(std::to_string(clientSocket), clientSocket);
				m_mapSocket2Player[clientSocket] = newPlayer;

				LOG(INFO) << "client connect, sockoct_id:  " << clientSocket;
				std::string str("Hello");
				CBuffer sendBuffer(str.size());
				send(clientSocket, str.data(), str.size(), 0);
				if (selectRes <= 1) {
					continue;
				}
			}

			for (int i = 0; i <= selectRes; i++) {
				if (readSet.fd_array[i] == m_socket) {
					continue;
				}
				if (!FD_ISSET(readSet.fd_array[i], &readSet)) {
					continue;
				}

				char buf[1024];
				int recvRes = recv(readSet.fd_array[i], buf, 1024, 0);
				if (recvRes == SOCKET_ERROR) {
					continue;
					//std::map<SOCKET, CPlayerObject*>::iterator iter = m_mapSocket2Player.find(readSet.fd_array[i]);
					//if (iter != m_mapSocket2Player.end()) {
					//	m_mapSocket2Player.erase(iter);
					//}
					//closesocket(readSet.fd_array[i]);
					//FD_CLR(readSet.fd_array[i], &fd);
				}
				std::map<SOCKET, CPlayerObject*>::iterator iter = m_mapSocket2Player.find(readSet.fd_array[i]);
				if (iter == m_mapSocket2Player.end()) {
					continue;
				}
				iter->second->RecvBuffer(buf, recvRes);
			}

			std::map<SOCKET, CPlayerObject*>::iterator iter = m_mapSocket2Player.begin();
			for (; iter != m_mapSocket2Player.end();) {
				iter->second->HandleMessge();
				++iter;
			}
		}
	}
}

void WheatTCPServer::SetSocketOpt(int socket) {
	bool addr = true;
	setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&addr, sizeof(addr));

	int netTimeout = 3000;
	setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&netTimeout, sizeof(netTimeout));
	 //setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&netTimeout, sizeof(netTimeout));
	 unsigned long ul=1;

	int ref = ioctlsocket(socket, FIONBIO, (unsigned long*)&ul);
	if (ref == -1){
		LOG(INFO) << "SetSocketOpt erro";
	}
	// if(ret==SOCKET_ERROR)//????????
	// {
	//     std::cout<<"ioctlsocket erro"<<std::endl;
	// }
}

//void WheatTCPServer::SendCommand(SOCKET destSocket, int sleeperIdWhoMakeThisCommand, const WheatCommand& command)
//{
//	int& sleeperId = sleeperIdWhoMakeThisCommand;
//	std::string strSleeperId = "";
//	std::string strMessage = "";
//	size_t bufSendSize = 0;
//	char* bufSend = nullptr;
//
//	strSleeperId = std::to_string(sleeperId);
//	strMessage = m_pCommandProgrammer->MakeMessage(command);
//
//	bufSendSize = strSleeperId.length() + 1 + strMessage.length() + 1;
//
//	bufSend = new char[bufSendSize];
//
//	BufferCatenate(bufSend, strSleeperId.c_str(), strSleeperId.length(), strMessage.c_str(), strMessage.length());
//
//	send(destSocket, bufSend, int(bufSendSize), 0);
//
//	printf("%s %s, Socket = %zd\n", bufSend, bufSend + 2, destSocket);
//
//	delete[] bufSend;
//	bufSend = nullptr;
//}

//void WheatTCPServer::SendCommandToFdSet(fd_set destFdSet, int fdMax, int sleeperIdWhoMakeThisCommand, const WheatCommand& command, SOCKET skipSocket)
//{
//	int& sleeperId = sleeperIdWhoMakeThisCommand;
//	std::string strSleeperId = "";
//	std::string strMessage = "";
//	size_t bufSendSize = 0;
//	char* bufSend = nullptr;
//
//	strSleeperId = std::to_string(sleeperId);
//	strMessage = m_pCommandProgrammer->MakeMessage(command);
//
//	bufSendSize = strSleeperId.length() + 1 + strMessage.length() + 1;
//
//	bufSend = new char[bufSendSize];
//
//	BufferCatenate(bufSend, strSleeperId.c_str(), strSleeperId.length(), strMessage.c_str(), strMessage.length());
//
//	SendBufferToFdSet(destFdSet, fdMax, bufSend, bufSendSize, skipSocket);
//
//	delete[] bufSend;
//	bufSend = nullptr;
//}

//void WheatTCPServer::SendMultiCommand(SOCKET destSocket, std::vector<int>& sleeperIdWhoMakeTheseCommands, const std::vector<WheatCommand>& commands)
//{
//	std::vector<int>& sleeperIds = sleeperIdWhoMakeTheseCommands;
//	std::string strSleeperId = "";
//	std::string strMessage = "";
//	size_t bufSendSize = 0;
//	size_t bufCatenateOffset = 0;
//	size_t strLen = 0;
//	char* bufSend = nullptr; // = new char[20000];
//	char* bufTemp;
//
//	for (int i = 0; i < commands.size(); i++) {
//		strSleeperId = std::to_string(sleeperIds[i]);
//		strMessage = m_pCommandProgrammer->MakeMessage(commands[i]);
//		strLen = strSleeperId.length() + 1 + strMessage.length() + 1;
//
//		bufCatenateOffset = bufSendSize;
//
//		bufSendSize += strLen;
//
//		// bufTemp ????????????????????????????strSleeperId ?? strMessage??
//		bufTemp = new char[strLen];
//
//		// BufferCatenate(bufSend, bufCatenateOffset, strSleeperId.c_str(), strSleeperId.length(), strMessage.c_str(), strMessage.length());
//		BufferCatenate(bufTemp, 0, strSleeperId.c_str(), strSleeperId.length(), strMessage.c_str(), strMessage.length());
//
//		// ??bufSend??????
//		char* bufSave = new char[bufCatenateOffset];
//		memcpy(bufSave, bufSend, bufCatenateOffset);
//
//		// ????????bufSend????????????
//		if (bufSend != nullptr)
//			delete[] bufSend;
//		bufSend = new char[bufSendSize];
//
//		// ???????????????? bufSend ????????
//		memcpy(bufSend, bufSave, bufCatenateOffset);
//
//		// ???????????????? bufTemp ????????
//		memcpy(bufSend + bufCatenateOffset, bufTemp, strLen);
//
//		// ???? bufTemp ?? bufSave
//		delete[] bufSave;
//		delete[] bufTemp;
//	}
//
//	if (bufSend != nullptr) {
//		send(destSocket, bufSend, int(bufSendSize), 0);
//
//		delete[] bufSend;
//		bufSend = nullptr;
//	}
//}

//void WheatTCPServer::BufferCatenate(char* destBuf, const char* buf1, size_t buf1Size, const char* buf2, size_t buf2Size)
//{
//	memcpy(destBuf, buf1, buf1Size + 1);
//	memcpy(destBuf + buf1Size + 1, buf2, buf2Size + 1);
//}
//
//void WheatTCPServer::BufferCatenate(char* destBuf, size_t offset, const char* buf1, size_t buf1Size, const char* buf2, size_t buf2Size)
//{
//	memcpy(destBuf + offset, buf1, buf1Size + 1);
//	memcpy(destBuf + offset + buf1Size + 1, buf2, buf2Size + 1);
//}
//
//void WheatTCPServer::SendBufferToFdSet(fd_set inputFdSet, int fdMax, const char* str) {
//	SendBufferToFdSet(inputFdSet, fdMax, str, strlen(str));
//}
//
//void WheatTCPServer::SendBufferToFdSet(fd_set inputFdSet, int fdMax, const char* str, size_t len, SOCKET skipSocket)
//{
//	for (int i = 0; i <= fdMax; i++) {
//		if (i == skipSocket || i == m_socket) {
//			continue;
//		}
//		if (FD_ISSET(i, &inputFdSet)) {
//			send(i, str, int(len), 0);
//		}
//	}
//}

bool WheatTCPServer::WSAStart() {
	if (WSAStartup(MAKEWORD(2, 2), &m_WSAData) != 0) {
		LOG(INFO) << "WSAStartup Failed!";
		return false;
	}
	LOG(INFO) << "WSAStartup Succeed.";
	return true;
}

bool WheatTCPServer::SocketInit()
{
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET) {
		LOG(INFO) << "socket Error!!" << WSAGetLastError();
		WSACleanup();
		return false;
	}
	printf("socket Succeed.\n");
	return true;
}

void WheatTCPServer::SetServerAddress(int port) {
	m_address.sin_family = AF_INET;
	m_address.sin_port = htons(port);
	m_address.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
}

bool WheatTCPServer::Bind()
{
	int bindRes = bind(m_socket, (sockaddr*)&m_address, sizeof(SOCKADDR_IN));
	if (bindRes == SOCKET_ERROR) {
		printf("bind Error!!\n");
		CloseServer();
		return false;
	}
	printf("bind Succeed.\n");
	return true;
}

bool WheatTCPServer::Listen()
{
	int listenRes = listen(m_socket, SOMAXCONN);
	if (listenRes == SOCKET_ERROR) {
		printf("listen Error!!\n");
		CloseServer();
		return false;
	}
	printf("listen Succeed.\n");
	return true;
}
