#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>


#define RING_BUF_CLONE(dst,src)  do{(dst)->data=(src)->data; \
						(dst)->head=(src)->head; \
						(dst)->tail=(src)->tail; \
						(dst)->size=(src)->size; \
						}while(0);


typedef struct
{
    uint8_t* data;
    uint16_t head;
    uint16_t tail;
    uint16_t size;
}ring_buf_t;


void ring_buffer_init( ring_buf_t *q, uint8_t *pBuf, uint16_t size );
uint16_t ring_buffer_enqueue( ring_buf_t *q, uint8_t *pSrc, uint16_t len );
uint16_t ring_buffer_force_enqueue( ring_buf_t *q, uint8_t *pSrc, uint16_t len );
uint16_t ring_buffer_dequeue( ring_buf_t *q, uint8_t *pDst, uint16_t max );
uint16_t ring_buffer_get_data_len( ring_buf_t *q );
uint16_t ring_buffer_get_free_len( ring_buf_t *q );
void ring_buffer_clean( ring_buf_t *q );

#endif
