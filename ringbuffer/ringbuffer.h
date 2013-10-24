//ringbuffer.h
//library for using a ring buffer
//useful for I/O 

#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H
#include <stdint.h> //uint8_t

//Ring Buffer object
typedef struct{
    unsigned int length;//size of buffer
    unsigned int head; //index to oldest data in buffer
    unsigned int tail; //index to next write position
    
    //these counters are used to check if the buffer is full and empty
    //if read_count - write count = 0, the buffer is empty
    //if write_count - read_count = length, the buffer is full
    int read_count; //number of reads performed
    int write_count;//number of writes performed
    
    uint8_t      *data; //data for buffer
}RingBuffer;

//Initialize RingBuffer
void ringbuffer_create(RingBuffer* buffer, unsigned int length);

//destroys ringbuffer and resets all its values
void ringbuffer_destroy(RingBuffer* buffer);

//check if RingBuffer is full
int ringbuffer_is_full(const RingBuffer* buffer);

//check if RingBuffer is empty
int ringbuffer_is_empty(const RingBuffer* buffer);

//write data to the RingBuffer
void ringbuffer_write(RingBuffer* b, const uint8_t data);

//read data from the RingBuffer
void ringbuffer_read(RingBuffer* b, uint8_t* data);

#endif //_RINGBUFFER_H
