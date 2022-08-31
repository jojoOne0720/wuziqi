#include "playerObject.h"

CPlayerObject::CPlayerObject(std::string name, SOCKET id):m_name(name),m_clientSocket(id),m_buffer(WHEATTCP_BUFFERSIZE) {}


void CPlayerObject::SendMessge() {

}

uint32_t CPlayerObject::RecvBuffer() {

	return 0;
}