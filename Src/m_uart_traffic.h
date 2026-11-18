#ifndef M_UART_TRAFFIC_H
#define M_UART_TRAFFIC_H
#include "stm32f4xx_hal.h"

#define UART_BLE	USART3

#define UART_RX_BUBF_SIZE	255

#define UART_RX_QUEUE_SIZE	20

typedef struct
{
	UART_HandleTypeDef *uart;
	uint8_t *dma_cache;
	uint16_t cache_size;
}m_uart_buf_t;


typedef enum
{
	UART_MSG_TYPE_RX_DONE=0,
}uart_msg_type_t;

typedef struct 
{
	UART_HandleTypeDef *uart;
	uint16_t data_len;
	uint8_t data[UART_RX_BUBF_SIZE];
}uart_msg_rx_pkt_t;

typedef union
{
	uart_msg_rx_pkt_t pkt;

}uart_msg_content_t;

typedef struct
{
	UART_HandleTypeDef *uart;
	uart_msg_type_t type;
	uart_msg_content_t content;
}uart_msg_t;

typedef void(*uart_msg_handle_t)(uart_msg_content_t *content);

typedef struct
{
	UART_HandleTypeDef *uart;
	uart_msg_type_t type;
	uart_msg_handle_t handle;
}uart_msg_handle_entry_t;


void m_uart_traffic_init( void );

void m_stop_checking_role(void);

#endif


