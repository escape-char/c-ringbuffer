#include <stdlib.h>
#include<string.h>
#include<stdio.h>
#include "ringbuffer.h"

void ringbuffer_create(RingBuffer* buffer, unsigned int len){
    buffer->length = len;
    buffer->head = buffer->tail = 0;
    buffer->read_count = buffer->write_count = 0;

    //allocate memory space for data
    buffer->data = (uint8_t*)calloc(buffer->length, sizeof(uint8_t));

    //initialize data to all zeros
    bzero(buffer->data, sizeof(buffer->data));
}
void ringbuffer_destroy(RingBuffer* buffer){
    if(buffer->data){
        free(buffer->data);
        buffer->data = NULL;
    }
    buffer->length = buffer->head = buffer->tail = 0;
    buffer->read_count = buffer->write_count = 0;
}
int ringbuffer_is_full(const RingBuffer* b){
    return (b->write_count - b->read_count) == (int) b->length;
}
int ringbuffer_is_empty(const RingBuffer* b){
    return (b->read_count - b->write_count) == 0;
}
void ringbuffer_write(RingBuffer* b, const uint8_t data){
    b->data[b->tail] = data; //write data to buffer

    //update new write position
    b->tail = (b->tail + 1) % b->length;
    b->write_count = (b->write_count + 1) % b->length;
    
    //overwrite data if tail reaches head
    if(b->head == b->tail)
        b->head = (b->head + 1) & b->length;
}
void ringbuffer_read(RingBuffer* b, uint8_t* data){
    *data = b->data[b->head]; //get data from head
    //update head to next oldest data in buffer
    b->head= (b->head + 1) % b->length;

    b->read_count = (b->read_count + 1) % b->length;
}
