#include "main.h"



void DMA_RX_INIT(UART_HandleTypeDef *huartx,\
								 DMA_HandleTypeDef *hdma_usartx_rx,\
								 uint8_t *rx1_buf,\
								 uint8_t *rx2_buf,\
								 uint16_t dma_buf_num)
{
		SET_BIT(huartx->Instance->CR3, USART_CR3_DMAR);
	__HAL_UART_ENABLE_IT(huartx, UART_IT_IDLE);
	__HAL_DMA_DISABLE(huartx->hdmarx);
  while(hdma_usartx_rx->Instance->CR & DMA_SxCR_EN)
  {
    __HAL_DMA_DISABLE(huartx->hdmarx);
  }
	hdma_usartx_rx->Instance->PAR = (uint32_t) & (huartx->Instance->DR);
	hdma_usartx_rx->Instance->M0AR = (uint32_t)(rx1_buf);
	hdma_usartx_rx->Instance->M1AR = (uint32_t)(rx2_buf);
  hdma_usartx_rx->Instance->NDTR = dma_buf_num;
	SET_BIT(hdma_usartx_rx->Instance->CR, DMA_SxCR_DBM);
	__HAL_DMA_ENABLE(huartx->hdmarx);
}

//单独使能tx加上SET_BIT(huartx.Instance->CR3, USART_CR3_DMAR);
//void DMA_TX_INIT(DMA_HandleTypeDef *hdma_usartx_tx,\
//								 uint8_t *data,\
//								 uint16_t len)
//{
//		
//		__HAL_DMA_DISABLE(hdma_usartx_tx);
//    while(hdma_usartx_tx->Instance->CR & DMA_SxCR_EN)
//    {
//        __HAL_DMA_DISABLE(hdma_usartx_tx);
//    }

//    //clear flag
//    //清除标志位
//    __HAL_DMA_CLEAR_FLAG(hdma_usartx_tx, DMA_HISR_TCIF7);
//    __HAL_DMA_CLEAR_FLAG(hdma_usartx_tx, DMA_HISR_HTIF7);

//    //set data address
//    //设置数据地址
//    hdma_usartx_tx->Instance->M0AR = (uint32_t)(data);
//    //set data length
//    //设置数据长度
//    hdma_usartx_tx->Instance->NDTR = len;

//    //enable DMA
//    //使能DMA
//    __HAL_DMA_ENABLE(hdma_usartx_tx);
//		
//}

//void usart1_printf(DMA_HandleTypeDef *hdma_usartx_tx,const char *fmt,...)
//{
//		
//    static uint8_t tx_buf[256] = {0};
//    static va_list ap;
//    static uint16_t len;
//    va_start(ap, fmt);

//    //return length of string 
//    //返回字符串长度
//    len = vsprintf((char *)tx_buf, fmt, ap);

//    va_end(ap);

//    DMA_TX_INIT(hdma_usartx_tx,tx_buf, len);
//		
//}


