#include "Buffer.h"
#include <assert.h>

//Դ�ļ�ʵ��
CBuffer::CBuffer(uint32_t bufSize)
{
	m_writePos = 0;
	m_readPos = 0;
	m_readableSize = 0;
	m_maxBufSize = bufSize;
	m_buf = new char[m_maxBufSize];
	m_packHeadLength = sizeof(EleHeader);//EleHeaderΪ"���Լ���������ݰ�ͷ"��
}

CBuffer::~CBuffer()
{
	if (m_buf)
	{
		delete[] m_buf;
		m_buf = NULL;
	}
}


bool CBuffer::Empty()
{
	return m_readableSize == 0;
}

int  CBuffer::getPackLen() {
	if (getBufReadSize() < sizeof(int)) {
		return 0;
	}

	int len = 0;
	memcpy((char*)&len, m_buf + m_readPos, sizeof(int));

	if (m_readableSize < len) {
		return 0;
	}

	return len;
}

int CBuffer::putData(char* data, int len)
{
	if (len <= 0)
	{
		return 0;
	}
	//�ж϶��еĿ��������С
	assert(m_readableSize >= 0 && m_readableSize <= m_maxBufSize);
	m_mutex.lock();
	int resLen = m_maxBufSize - m_readableSize;//��д�����ֽ���

	if (len > resLen)
	{
		len = resLen;
	}

	//���ֽڿ���
	for (int i = 0; i < len; i++)
	{
		m_buf[m_writePos] = data[i];
		//ע�����ﲻ����rear++,��Ȼ�ǻ��λ������������䵽�ײ�֮�󣬵ײ�������Ҫ�ص�ͷ��
		m_writePos = (m_writePos + 1) % m_maxBufSize;
	}
	m_readableSize += len;	//�ɶ��ֽ��� + len
	m_mutex.unlock();
	return len;
}

int CBuffer::getData(char* buf, int len)
{
	if (len <= 0)
	{
		return 0;
	}
	assert(m_readableSize >= 0);
	m_mutex.lock();
	if (m_readableSize < len)
	{
		len = m_readableSize;
	}

	int temp = m_readPos;//��ȡ���ݵ�ʱ���ܸı�ͷ��������ֵ��ȫ���������֮��Ÿı�ͷ��������λ��
	for (int i = 0; i < len; i++)
	{
		buf[i] = m_buf[temp];
		//���������һ����ͷ��������Ҳ�п����ܵ��ײ������������ܻ���
		temp = (temp + 1) % m_maxBufSize;
	}
	m_readPos = (m_readPos + len) % m_maxBufSize;
	m_readableSize -= len;	//�ɶ��ֽ��� - len
	m_mutex.unlock();
	return len;
}


//���ػ������еĿɶ��ֽ�����
int CBuffer::getBufReadSize()
{
	return m_readableSize;
}

//�ṩ��ʹ���ߵĽӿ�
//���û�����
void CBuffer::resetBuffer()
{
	m_mutex.lock();
	m_writePos = 0;
	m_readPos = 0;
	m_readableSize = 0;
	m_mutex.unlock();
}

