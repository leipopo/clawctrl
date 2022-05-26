#include "main.h"
PID_regulator mspid[4]={finger_speed_pid,finger_speed_pid,palm_speed_pid,palm_speed_pid}\
							,mapid[4]={finger_angle_pid,finger_angle_pid,palm_angle_pid,palm_angle_pid};
MotorInfo minfo[4]={finger1_default_config,finger2_default_config,palm1_default_config,palm2_default_config};
int16_t mes[4];

void motorctrl()
{
	for(int8_t i=0;i<2;i++)
	{
		mspid[i].kp=400;
		mspid[i].ki=5;
		mspid[i].kd=50;
		mapid[i].kp=10;
		mapid[i].ki=0;
		mapid[i].kd=0;
	}
	for(int8_t i=2;i<4;i++)
	{
		mspid[i].kp=400;
		mspid[i].ki=5;
		mspid[i].kd=100;
		mapid[i].kp=10;
		mapid[i].ki=0;
		mapid[i].kd=0;
	}
//	  mspid[0].kp=500;
//		mspid[0].ki=5;
//		mspid[0].kd=50;
//		mapid[0].kp=10;
//		mapid[0].ki=0;
//		mapid[0].kd=0;
//		
//		mspid[1].kp=500;
//		mspid[1].ki=5;
//		mspid[1].kd=50;
//		mapid[1].kp=10;
//		mapid[1].ki=0;
//		mapid[1].kd=0;
//		
//		mspid[2].kp=500;
//		mspid[2].ki=5;
//		mspid[2].kd=50;
//		mapid[2].kp=10;
//		mapid[2].ki=0;
//		mapid[2].kd=0;
//		
//		mspid[3].kp=500;
//		mspid[3].ki=5;
//		mspid[3].kd=50;
//		mapid[3].kp=10;
//		mapid[3].ki=0;
//		mapid[3].kd=0;
//		
		minfo[0].parameter.inpositioncurrent=3.5f;
		minfo[1].parameter.inpositioncurrent=3.5f;
		minfo[2].parameter.inpositioncurrent=4.f;
		minfo[3].parameter.inpositioncurrent=4.f;
	for(;;)
	{
		for(int8_t i=0;i<4;i++)
		{
			motaspid_calc(&minfo[i],&mapid[i],&mspid[i]);
			mes[i]=minfo[i].parameter.reversed*mspid[i].output;
			if(cinfo.clawmode==0x02)
				mes[i]=minfo[i].parameter.reversed*cinfo.tarmotorinfo.torque[i]*tccoe*maxcurrentvalue/maxcurrent;		
			if(cinfo.clawmode==0x03)
			{			
					mes[i]=0;
			}
		}
		
		CAN_send(0x200,hcan1,mes);
		osDelayUntil(tp);
	}
}
