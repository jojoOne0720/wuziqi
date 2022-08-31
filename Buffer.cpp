#pragma once
#include "Buffer.h"

CBuffer::CBuffer(uint32_t size) :m_bufferbegin(0), m_bufferend(0), m_realSize(0), m_bufferlenght(size) {
    m_buffer = new char[m_bufferlenght];
}

CBuffer::~CBuffer() {
    if (nullptr != m_buffer) {
        delete[] m_buffer;
        m_buffer = nullptr;
    }
}

uint32_t CBuffer::getCanWriteSize() {
    return m_bufferlenght - m_realSize;
}

uint32_t CBuffer::getBuffer(char*& buffer) {
    buffer = m_buffer;
    return getCanWriteSize();
}

uint32_t CBuffer::getCanReadSize() {
    return m_realSize;
}

void CBuffer::fillDate(uint32_t size) {
    m_realSize += size;
    if (m_bufferlenght - m_bufferend <= size)
    {
        size -= m_bufferlenght - m_bufferend;
        m_bufferend = 0;
    }
    m_bufferend -= size;
}

void CBuffer::removeDate(uint32_t size) {
    m_realSize -= size;
    if (m_bufferlenght - m_bufferbegin <= size)
    {
        size -= m_bufferlenght - m_bufferbegin;
        m_bufferbegin = 0;
    }
    m_bufferbegin += size;
}

bool CBuffer::HasData() const {
    //判断是否有真正有意义的数据
    if (m_realSize < 0)
        return false;
    //
    if (m_realSize < (sizeof(int16_t) + sizeof(int16_t)))
        return false;

    return true;
}

