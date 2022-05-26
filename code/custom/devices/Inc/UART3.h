#ifndef UART3_H
#define UART3_H

#include "usart.h"

#define RX_BUF_NUM 24

#define FRAME_LENGTH 12

void USART3_inIRQHandler(void);
	

void Ut_init(void);
extern uint8_t Ut_ready;

typedef struct _user_command
{
	uint8_t modeset; //0x00 rel_postionctrl 0x01 abs_postionctrl 0x02 torquectrl 0x03 loose 0x04 zero 0x00 neutral
	float motoranglechange[4];
	float motorangle[4];
	float motorspeed[4];
	float motortorque[4];

}usercommand;
extern usercommand ucomd;
void USART3_inIRQHandler(void);
#endif
