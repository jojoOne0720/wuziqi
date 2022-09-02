#include "playerObject.h"

CPlayerObject::CPlayerObject(std::string name, SOCKET id):m_name(name),m_clientSocket(id), m_status(EPlayerStatus::login), m_buffer(WHEATTCP_BUFFERSIZE) {}


void CPlayerObject::SendMessge() {

}

uint32_t CPlayerObject::RecvBuffer(char* buf,int len) {
	if (len > m_buffer.getBufReadSize()) {
		return 0;//环形缓存区自动增长，没实现
	}

	m_buffer.putData(buf, len);
	HandleMessge();
	return 0;
}

void CPlayerObject::HandleMessge() {

}