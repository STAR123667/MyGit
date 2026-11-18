#include "ring_buffer.h"

void ring_buffer_init( ring_buf_t *q, uint8_t *pBuf, uint16_t size )
{
	q->data = pBuf;
	q->size = size;
	q->head = 0;
	q->tail = 0;
}

uint16_t ring_buffer_enqueue( ring_buf_t *q, uint8_t *pSrc, uint16_t len )
{
	uint16_t i;
	for ( i=0; i<len; i++ )
	{
		if ( ( ( q->head +1 ) % q->size ) == q->tail )
		{
			break;
		}
		q->data[ q->head ] = pSrc[ i ];
		q->head = ( q->head +1 ) % q->size;
	}
        return  i;
}

uint16_t ring_buffer_force_enqueue( ring_buf_t *q, uint8_t *pSrc, uint16_t len )
{
	uint16_t i;
	for ( i=0; i<len; i++ )
	{
		if ( ( ( q->head +1 ) % q->size ) == q->tail )
		{
			q->tail = ( q->tail +1 ) % q->size;;
		}
		q->data[ q->head ] = pSrc[ i ];
		q->head = ( q->head +1 ) % q->size;
	}

	return  i;
}

uint16_t ring_buffer_dequeue( ring_buf_t *q, uint8_t *pDst, uint16_t max )
{
	uint16_t i;
	for ( i = 0; i < max; i++ )
	{
		if ( q->head == q->tail )
		{
			break;
		}
		pDst[ i ] = q->data[ q->tail ];
		q->tail = ( q->tail + 1 ) % q->size;
	}
	return i;
}

uint16_t ring_buffer_get_data_len( ring_buf_t *q )
{
	return ( ( q->size + q->head - q->tail ) % q->size );
}

uint16_t ring_buffer_get_free_len( ring_buf_t *q )
{
	return ( q->size - ring_buffer_get_data_len(q) - 1 );
}

void ring_buffer_clean( ring_buf_t *q )
{
	q->head = 0;
	q->tail = 0;
}


