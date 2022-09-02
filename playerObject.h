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
	EPlayerStatus m_status; //玩家当前状态

public:
	CPlayerObject(std::string name, SOCKET id);

	void SendMessge();

	uint32_t RecvBuffer(char* buf, int len);

	void HandleMessge();//这里处理消息


};






#endif
