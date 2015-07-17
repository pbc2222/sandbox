#include <memory.h>
#include <stdio.h>
#include "Buffer.h"

/* Comment line for Feature_1 branch */

Buffer::Buffer(size_t capacity)
  : m_beginIndex(0)
  , m_endIndex(0)
  , size_(0)
  , m_capacity(capacity)
{
  data_ = new char[capacity];
}

Buffer::~Buffer()
{
  delete[] data_;
}

size_t Buffer::retrieveDataArray(char *data)
{
  if (size_ != 0)
  {
    // copy in a single step
    if (m_endIndex > m_beginIndex)
    {
      memcpy(data, data_ + m_beginIndex, size_);
    }
    // copy in two steps
    else
    {
      int bytesToWrite = m_capacity - m_beginIndex;
      memcpy(data, data_ + m_beginIndex, bytesToWrite);
      memcpy(data+bytesToWrite, data, m_endIndex);
    }
  }
  return(size_);
}

size_t Buffer::bytesUsed(void)
{
  return(size_);
}

size_t Buffer::bytesFree(void)
{
  return(m_capacity - size_);
} 

size_t Buffer::write(const char *data, size_t bytes)
{
  if (bytes == 0) return 0;

  size_t capacity = m_capacity;
  size_t bytes_to_write = (bytes > (capacity - size_)?(capacity - size_):bytes);

  // Write in a single step
  if (bytes_to_write <= capacity - m_endIndex)
  {
    memcpy(data_ + m_endIndex, data, bytes_to_write);
    m_endIndex += bytes_to_write;
    if (m_endIndex == capacity) m_endIndex = 0;
  }
  // Write in two steps
  else
  {
    size_t size_1 = capacity - m_endIndex;
    memcpy(data_ + m_endIndex, data, size_1);
    size_t size_2 = bytes_to_write - size_1;
    memcpy(data_, data + size_1, size_2);
    m_endIndex = size_2;
  }

  size_ += bytes_to_write;
  return bytes_to_write;
}

/*
  
 */
size_t Buffer::read(char *data, size_t bytes)
{
  if (bytes == 0) return 0;

  size_t capacity = m_capacity;
  size_t bytes_to_read = (bytes > size_?size_:bytes);

  // Read in a single step
  if (bytes_to_read <= capacity - m_beginIndex)
  {
    memcpy(data, data_ + m_beginIndex, bytes_to_read);
    m_beginIndex += bytes_to_read;
    if (m_beginIndex == capacity) m_beginIndex = 0;
  }
  // Read in two steps
  else
  {
    size_t size_1 = capacity - m_beginIndex;
    memcpy(data, data_ + m_beginIndex, size_1);
    size_t size_2 = bytes_to_read - size_1;
    memcpy(data + size_1, data_, size_2);
    m_beginIndex = size_2;
  }

  size_ -= bytes_to_read;
  return bytes_to_read;
}
