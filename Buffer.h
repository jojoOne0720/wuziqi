#pragma once
# include	<stdint.h>
# include	<mutex>
/**
 * ���ݰ�ͷ��ÿ�δ������ζ��е����ݳ��ȿ��ܲ�һ�£�����ÿ���ȴ�һ��EleHeader����ָʾ���ȣ�Ȼ���ٴ�ʵ�ʵ����ݡ�
 */
struct EleHeader
{
	int payloadLen;//ʵ����Ϣ�ĳ���
};

/**
 * �˻��ζ��в����Ƕ��߳����⣬Ĭ��һ��(putData)һ��(getData)
 */

class CBuffer
{
public:
	CBuffer(uint32_t bufSize);
	~CBuffer();

private:
	char* m_buf;           //ָ���λ�������ָ��
	int		m_readPos;        //��������λ������
	int		m_writePos;       //������дλ������
	int     m_readableSize;   //�������пɶ����ֽ������Ѿ�д���ǻ�δ�����ֽ���,ȡֵ��ΧΪ[0,m_maxBufSize]��
	int		m_maxBufSize;     //�����������ֵ(����ҵ��ͬ�����ú��ʵ�ֵ)
	int		m_packHeadLength; //���ݰ�ͷ����(����Ƕ���������ô����������������ݰ�������ǲ�
	//�����ģ���ô������ǰ�ͷ�ĳ���)
	std::mutex   m_mutex;
public:
	/**
	 * �ѽ��յ������ݿ�������������
	 * ����ֵ: -1:���� >=0:ʵ��д����ֽ�����
	 */
	int putData(char* data, int len);

	/**
	* �ӻ������л�ȡָ�����ȵ����ݣ��浽buf��
	* ����ֵ: -1:���� >=0:ʵ�ʻ�ȡ�����ֽ�����
	*/
	int getData(char* buf, int len);

	//���ػ������еĿɶ��ֽ�����
	int getBufReadSize();

	//���û�����    
	void resetBuffer();

	//�������Ƿ�Ϊ��
	bool Empty();
};
