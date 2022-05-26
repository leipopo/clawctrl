#ifndef INFO_H
#define INFO_H

#include "stdint.h"




typedef struct _Claw_Info
{
	uint8_t clawmode;//0x00 rel_postionctrl 0x01 abs_postionctrl 0x02 torquectrl 0x03 loose 0x04 zero 0x05 ready 0x06moving
	uint8_t motorstate[4];//0x00 loose 0x01 zeroing 0x10 inpostion 0x11 moving 
	
	
	struct
	{
		float angle[4];
		float speed[4];
		float torque[4];//2006直接反馈转矩常(电流转矩常数为1/3)，3508反馈转矩电流
	}tarmotorinfo;//记录电机目标参数
	
	struct
	{
		float angle[4];
		float speed[4];
		float torque[4];//2006直接反馈转矩常(电流转矩常数为1/3)，3508反馈转矩电流
	}curmotorinfo;//记录电机目标参数
	
}clawinfo;


extern clawinfo cinfo;



#endif
