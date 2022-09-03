#include "Buffer.h"
#include <assert.h>

//源文件实现
CBuffer::CBuffer(uint32_t bufSize)
{
	m_writePos = 0;
	m_readPos = 0;
	m_readableSize = 0;
	m_maxBufSize = bufSize;
	m_buf = new char[m_maxBufSize];
	m_packHeadLength = sizeof(EleHeader);//EleHeader为"你自己定义的数据包头"。
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
	//判断队列的空闲区域大小
	assert(m_readableSize >= 0 && m_readableSize <= m_maxBufSize);
	m_mutex.lock();
	int resLen = m_maxBufSize - m_readableSize;//可写的总字节数

	if (len > resLen)
	{
		len = resLen;
	}

	//按字节拷贝
	for (int i = 0; i < len; i++)
	{
		m_buf[m_writePos] = data[i];
		//注意这里不能用rear++,既然是环形缓冲区，如果填充到底部之后，底部的索引要回到头部
		m_writePos = (m_writePos + 1) % m_maxBufSize;
	}
	m_readableSize += len;	//可读字节数 + len
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

	int temp = m_readPos;//获取数据的时候不能改变头部索引的值，全部处理完成之后才改变头部索引的位置
	for (int i = 0; i < len; i++)
	{
		buf[i] = m_buf[temp];
		//这里和上面一样，头部的索引也有可能跑到底部，得让它能跑回来
		temp = (temp + 1) % m_maxBufSize;
	}
	m_readPos = (m_readPos + len) % m_maxBufSize;
	m_readableSize -= len;	//可读字节数 - len
	m_mutex.unlock();
	return len;
}


//返回缓存区中的可读字节数量
int CBuffer::getBufReadSize()
{
	return m_readableSize;
}

//提供给使用者的接口
//重置缓冲区
void CBuffer::resetBuffer()
{
	m_mutex.lock();
	m_writePos = 0;
	m_readPos = 0;
	m_readableSize = 0;
	m_mutex.unlock();
}

