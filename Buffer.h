#pragma once
# include	<stdint.h>
# include	<mutex>
/**
 * 数据包头，每次存往环形队列的数据长度可能不一致，所以每次先存一个EleHeader用于指示长度，然后再存实际的数据。
 */
struct EleHeader
{
	int payloadLen;//实际消息的长度
};

/**
 * 此环形队列不考虑多线程问题，默认一进(putData)一出(getData)
 */

class CBuffer
{
public:
	CBuffer(uint32_t bufSize);
	~CBuffer();

private:
	char* m_buf;           //指向环形缓冲区的指针
	int		m_readPos;        //缓冲区读位置索引
	int		m_writePos;       //缓冲区写位置索引
	int     m_readableSize;   //缓存区中可读的字节数（已经写但是还未读的字节数,取值范围为[0,m_maxBufSize]）
	int		m_maxBufSize;     //缓冲区的最大值(根据业务不同，设置合适的值)
	int		m_packHeadLength; //数据包头长度(如果是定长包，那么这里可以是整个数据包。如果是不
	//定长的，那么这里就是包头的长度)
	std::mutex   m_mutex;
public:
	/**
	 * 把接收到的数据拷贝到缓冲区中
	 * 返回值: -1:出错。 >=0:实际写入的字节数。
	 */
	int putData(char* data, int len);

	/**
	* 从缓冲区中获取指定长度的数据，存到buf中
	* 返回值: -1:出错。 >=0:实际获取到的字节数。
	*/
	int getData(char* buf, int len);

	//返回缓存区中的可读字节数量
	int getBufReadSize();

	//重置缓冲区    
	void resetBuffer();

	//缓冲区是否为空
	bool Empty();
};
