#ifndef _PLAYER_OBJECT_H
#define _PLAYER_OBJECT_H
#include <string>
#include <winsock.h>
#include "Buffer.h"
#include "struct.h"
#define WHEATTCP_BUFFERSIZE 4396
class CPlayerObject {
private:
	std::string m_name; //player_name
	SOCKET  m_clientSocket; 
	CBuffer m_buffer; //���绺����
	EPlayerStatus m_status; //��ҵ�ǰ״̬

public:
	CPlayerObject(std::string name, SOCKET id);

	~CPlayerObject();

	void SendMessge(CBuffer& sendBuffer);

	uint32_t RecvBuffer(char* buf, int len);

	void HandleMessge();//���ﴦ����Ϣ


};






#endif
