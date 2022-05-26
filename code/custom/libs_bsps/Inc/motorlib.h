#ifndef ctrltask_H
#define ctrltask_H

#include "pid.h"
#include "stm32f4xx.h"

#define PIDoutercyclerate 2

#define asinwave 0x01
#define atriwave 0x02
#define stepwave 0x03

#define speedupcps 0

float kictrl(PID_regulator *pid,float effctarea);



typedef struct _Motor_Info
{
	struct
	{
		
		float angle_limit[2];//角度限制，无限制则为{-180，180}，代码内使用单位度
		float speed_limit;//速度限制，查询电机电调套装手册，代码内使用单位rpm
		float current_limit[2];//电流限制，查询电机电调套装手册，代码内使用单位A
		float current2torquecoe;//电流转矩系数
		float reductiongearratio;//电机及其所在机构构成的减速倍率，减速时代码内此值应大于一
		float inpositioncurrent;//撞限位的电流值，使用单位A
		float installationangle;//安装角度，即电机归零时的角度，针对增量式编码器（3508/2006）和绝对值编码器（6020）有不同的使用方法
		int16_t pidoutcycrate;
		uint8_t sumangle;//0x1累计角度
		int8_t reversed;//0x1反装
		int8_t zerodir;//归零方向
	}parameter;
	
	struct
	{
		float angle;
		float speed;
		float currentsum;
		float pidcount;
		float anglechanged;
		float temp_angle[2];

	}tempdata;//用于解算角度的临时参数
	
	struct
	{
		float angle;
		float speed;
		float current;//2006直接反馈转矩常(电流转矩常数为一)，3508反馈转矩电流
	}tarmotorinfo;//记录电机目标参数
	
	struct
	{
		float angle;
		float speed;
		float current[5];
	}curmotorinfo;//记录电机目标角度
	
}MotorInfo;

typedef struct _wave_HandleTypeDef
{
	uint8_t wavetpye;
	float waveperiod;
	float taskperiod;
	float amplitude;
}wave_HandleTypeDef;

void gearmotor_angledecoder(MotorInfo *Motor);
void gearmotor_angledecoder_sum(MotorInfo *Motor);
void motaspid_calc(MotorInfo *minfo,PID_regulator *anglepid,PID_regulator *speedpid);
void motcurrentsensor(MotorInfo *minfo);
void canrxtomotinfo(MotorInfo *minfo,uint8_t rx[8]);
float anglecircle(float angle);
float anglelimit(float angle,float anglemax,float anglemin);
float currentlimit(float current,float currentmax);
float speedlimit(float speed,float speedmax);

#endif
