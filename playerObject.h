#ifndef _PLAYER_OBJECT_H
#define _PLAYER_OBJECT_H
#include <string>
#include <winsock.h>
#include "Buffer.h"
#include "struct.h"
#define WHEATTCP_BUFFERSIZE 1024
class CPlayerObject {
private:
	std::string m_name; //player_name
	SOCKET  m_clientSocket; 
	CBuffer m_buffer; //网络缓冲区
	EPlzyerStatus m_status; //玩家当前状态

public:
	CPlayerObject(std::string name, SOCKET id);

	void SendMessge();

	uint32_t RecvBuffer();



};






#endif
