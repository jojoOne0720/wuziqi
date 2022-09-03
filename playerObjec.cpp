#include "playerObject.h"
#include <vector>
#include "logger.h"
CPlayerObject::CPlayerObject(std::string name, SOCKET id):m_name(name),m_clientSocket(id), m_status(EPlayerStatus::login), m_buffer(WHEATTCP_BUFFERSIZE) {}


void CPlayerObject::SendMessge(CBuffer& sendBuffer) {
	send(m_clientSocket, sendBuffer.getBuf(), sendBuffer.getBufReadSize(), 0);
}

uint32_t CPlayerObject::RecvBuffer(char* buf,int len) {
	//if (len > m_buffer.getBufReadSize()) {
	//	return 0;//环形缓存区自动增长，没实现
	//}

	m_buffer.putData(buf, len);
	HandleMessge();
	return 0;
}

void CPlayerObject::HandleMessge() {

	int packLen = m_buffer.getPackLen();
	if (packLen == 0) {
		return;
	}

	std::vector<int8_t> vecData;
	vecData.reserve(packLen);
	char* data = (char*)vecData.data();
	m_buffer.getData(data, packLen);
	int cmd = 0;
	std::memcpy((char*)&cmd, data + 4, 4);
	switch (cmd) {
	case::CMD::CMD_LOGIN: {
		//std::string str("Hello");
		//CBuffer sendBuffer(str.size());
		//sendBuffer.putData((char*)str.data(), str.size());
		//SendMessge(sendBuffer);
		std::string str("Hello");
		CBuffer sendBuffer(str.size());
		send(m_clientSocket, str.data(), str.size(), 0);
	}
	break;
	case::CMD::CMD_LOGOUT: {
		//std::string str("Hello");
		//CBuffer sendBuffer(str.size());
		//sendBuffer.putData((char*)str.data(), str.size());
		//SendMessge(sendBuffer);
	}
	break;
	default:
		LOG(WARNING) << "no find cmd" << cmd;
	}
}

CPlayerObject::~CPlayerObject() {
	m_clientSocket = 0;
	m_name.clear();
}