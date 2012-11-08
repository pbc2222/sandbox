#include <stdlib.h>
/*
  Ring buffer 
 */
class CircularBuffer
{
public:
  CircularBuffer(size_t capacity);
  ~CircularBuffer();

  // Return number of bytes in the data array
  // Retrieve the internal circular data buffer as a liniar array
  // NOTE: overrun may occur if memory allocated to data is too small
  size_t retrieveDataArray(char *data); // Pointer to memory where buffer data is put

  // Return number of bytes used 
  size_t bytesUsed(void);

  // Return number of free bytes 
  size_t bytesFree(void);
  //
  // Return number of bytes actually written.
  size_t write(
    const char *data, // Pointer to data to be written
    size_t bytes);    // Number of bytes to be written

  // Return number of bytes read.
  // NOTE: overrun may occur if memory allocated to data is too small
  size_t read(
    char *data,    // Pointer to memory where read data is put
    size_t bytes); // Number of bytes to read

private:
  size_t m_beginIndex;
  size_t m_endIndex;
  size_t size_;      // Number of bytes contained in buffer
  size_t m_capacity;  // Number of bytes allocated for buffer
  char *data_;
};
