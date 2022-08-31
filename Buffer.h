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

    //判断是否有一个协议头的长度
    bool HasData() const;

    ~CBuffer();

    CBuffer(uint32_t size);
    //获取可写长度
    uint32_t getCanWriteSize();
    //如果buffer的长度不够，该函数会自动增长长度
    int reallocBuffer() { return 0; };

    //获取数据头地址
    uint32_t getBuffer(char*& buffer);

    //获取可读长度
    uint32_t getCanReadSize();

    void fillDate(uint32_t  size);

    //去除数据
    void removeDate(uint32_t size);

protected:
    //指向buffer的指针
    char* m_buffer;
    //buffer开始位
    uint32_t m_bufferbegin;
    //buffer结束位
    uint32_t m_bufferend;
    //buffer总长度
    uint32_t m_bufferlenght;

    //真实数据长度（使用环形方式接收数据）
    uint32_t m_realSize;
};

#endif
