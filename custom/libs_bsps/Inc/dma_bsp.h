#ifndef DMA_BSP_H
#define DMA_BSP_H

#include "usart.h"

extern void usart_printf(DMA_HandleTypeDef *hdma_usartx_tx,const char *fmt,...);
extern void DMA_TX_INIT(DMA_HandleTypeDef *hdma_usartx_tx,\
								 uint8_t *data,\
								 uint16_t len);

extern void DMA_RX_INIT(UART_HandleTypeDef *huartx,\
								 DMA_HandleTypeDef *hdma_usartx_rx,\
								 uint8_t *rx1_buf,\
								 uint8_t *rx2_buf,\
								 uint16_t dma_buf_num);
#endif
