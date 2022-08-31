#pragma once

#ifndef _BUFFER_H
#define _BUFFER_H
#include <stdint.h>

struct SPackHead
{
    int16_t head;
};

class CBuffer {
public:

    //�ж��Ƿ���һ��Э��ͷ�ĳ���
    bool HasData() const;

    ~CBuffer();

    CBuffer(uint32_t size);
    //��ȡ��д����
    uint32_t getCanWriteSize();
    //���buffer�ĳ��Ȳ������ú������Զ���������
    int reallocBuffer() { return 0; };

    //��ȡ����ͷ��ַ
    uint32_t getBuffer(char*& buffer);

    //��ȡ�ɶ�����
    uint32_t getCanReadSize();

    void fillDate(uint32_t  size);

    //ȥ������
    void removeDate(uint32_t size);

protected:
    //ָ��buffer��ָ��
    char* m_buffer;
    //buffer��ʼλ
    uint32_t m_bufferbegin;
    //buffer����λ
    uint32_t m_bufferend;
    //buffer�ܳ���
    uint32_t m_bufferlenght;

    //��ʵ���ݳ��ȣ�ʹ�û��η�ʽ�������ݣ�
    uint32_t m_realSize;
};

#endif
