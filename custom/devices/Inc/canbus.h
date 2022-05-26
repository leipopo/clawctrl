#ifndef CANBUS__H
#define CANBUS__H

#include "stdint.h"
#include "can.h"

void can_filter_init(void);

void CAN_send(uint32_t address,\
							CAN_HandleTypeDef hcanx,\
							int16_t message[4]
							);
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);

extern uint8_t CAN1_ready;
extern uint8_t CAN2_ready;
#endif
