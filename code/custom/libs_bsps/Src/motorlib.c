#include "main.h"

/*-------------------------------------
* 函数名：测试用波形发生器
* 描述  ：波形发生器
* 输入  ：dddd
* 输出  ：dddd
作者：LPGUAIA
日期：2021.7.7
-----------------------------------------*/
wave_HandleTypeDef sinwave={0x01,\
														1000,\
														5,\
														90};

float wavegenerator (wave_HandleTypeDef *SinWave)
{
	uint16_t samplenum = SinWave->waveperiod/SinWave->taskperiod;
	static uint16_t count;
	float output;
	
	if(count<samplenum)
		count++;
	else
		count=0;
	
	switch(SinWave->wavetpye)
	{
		case asinwave:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
		case atriwave:
			output=SinWave->amplitude*count/samplenum;break;
		case stepwave:
			output=SinWave->amplitude*((int)((2*count-1)/samplenum));break;
		default:
			output=SinWave->amplitude*sin(2*PI*count/samplenum);break;
	}
	
	return output;
}



/*-------------------------------------
* 函数名：减速电机角度解算
* 描述  ：计算减速后的角度
* 输入  ：电机结构体
* 输出  ：无

作者：LPGUAIA
日期：2021.4.27
-----------------------------------------*/ 

void gearmotor_angledecoder(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
	
	if(ABS(Motor->tempdata.anglechanged + Motor->curmotorinfo.angle)<180)
		Motor->curmotorinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorinfo.angle;
	else if(Motor->tempdata.anglechanged + Motor->curmotorinfo.angle<=-180)
		Motor->curmotorinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorinfo.angle + 360;
	else if(Motor->tempdata.anglechanged + Motor->curmotorinfo.angle>=180)
		Motor->curmotorinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorinfo.angle - 360;
}
/*-------------------------------------
* 函数名：减速电机角度解算
* 描述  ：计算减速后的累计角度
* 输入  ：电机结构体
* 输出  ：无

作者：LPGUAIA
日期：2021.4.27
-----------------------------------------*/ 
void gearmotor_angledecoder_sum(MotorInfo *Motor)
{
	
	Motor->tempdata.anglechanged=Motor->tempdata.temp_angle[1] - Motor->tempdata.temp_angle[0];
	Motor->tempdata.temp_angle[0]=Motor->tempdata.temp_angle[1];
	
	
	if(ABS(Motor->tempdata.anglechanged)<=300)
		Motor->tempdata.anglechanged=Motor->tempdata.anglechanged/Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged>300)
		Motor->tempdata.anglechanged = (Motor->tempdata.anglechanged-360) / Motor->parameter.reductiongearratio;
	else if(Motor->tempdata.anglechanged<-300)
		Motor->tempdata.anglechanged = (360 + Motor->tempdata.anglechanged) / Motor->parameter.reductiongearratio;
	
		Motor->curmotorinfo.angle = Motor->tempdata.anglechanged + Motor->curmotorinfo.angle;

}

/*-------------------------------------
* 函数名：角度跟速度环计算
* 描述  ：角度跟速度环的简单计算
* 输入  ：电机结构体，角度和速度pid结构体
* 输出  ：无

作者：LPGUAIA
日期：2022.4
-----------------------------------------*/ 

void motaspid_calc(MotorInfo *minfo,PID_regulator *anglepid,PID_regulator *speedpid)
{
	
	if(minfo->tempdata.pidcount<minfo->parameter.pidoutcycrate&&minfo->tempdata.pidcount>=0)
		minfo->tempdata.pidcount++;
	else
		minfo->tempdata.pidcount=0;
	
	
	if(minfo->tempdata.pidcount==minfo->parameter.pidoutcycrate)
	{
		
		anglepid->tar=minfo->tarmotorinfo.angle;
		anglepid->cur=minfo->curmotorinfo.angle;
		anglepid->outputMax=minfo->tarmotorinfo.speed;
		PID_angle_calc(anglepid,1,300);
		minfo->tempdata.pidcount=0;
	}
		
		speedpid->tar=anglepid->output;
		speedpid->cur=minfo->curmotorinfo.speed;
	
		PID_calc(speedpid,1);
}
/*-------------------------------------
* 函数名：电机电流感应
* 描述  ：更新电流数据，保存五次采样值
* 输入  ：电机结构体
* 输出  ：无

作者：LPGUAIA
日期：2022.4
-----------------------------------------*/ 
void motcurrentsensor(MotorInfo *minfo)
{
	
	for(uint8_t i=4;i>0;i--)
	{
		minfo->curmotorinfo.current[i]=minfo->curmotorinfo.current[i-1];
	}
	for(int8_t i=4;i>=0;i--)
	{
		minfo->tempdata.currentsum+=ABS(minfo->curmotorinfo.current[i]);
	}
	if(ABS(minfo->curmotorinfo.current[0])>=minfo->parameter.inpositioncurrent&&ABS(minfo->curmotorinfo.current[1])>=minfo->parameter.inpositioncurrent)\
	{
		minfo->tempdata.angle=minfo->curmotorinfo.angle;
	}
}
/*-------------------------------------
* 函数名：can解码成电机数据
* 描述  ：将can的数据解算成电机数据
* 输入  ：电机结构体，can的数据
* 输出  ：无

作者：LPGUAIA
日期：2022.4
-----------------------------------------*/ 
void canrxtomotinfo(MotorInfo *minfo,uint8_t rx[8])
{
	
	
		minfo->tempdata.temp_angle[1] = ((int16_t)minfo->parameter.reversed*((rx[0]<<8)|(rx[1])))*360.0f/0x1fff-180.f;
		if(minfo->parameter.sumangle)
			gearmotor_angledecoder_sum(minfo);
		else
			gearmotor_angledecoder(minfo);
		minfo->curmotorinfo.speed = ((int16_t)(minfo->parameter.reversed*((rx[2]<<8)|(rx[3]))))/minfo->parameter.reductiongearratio;
		motcurrentsensor(minfo);
		minfo->curmotorinfo.current[0] = ((int16_t)(minfo->parameter.reversed*((rx[4]<<8)|(rx[5]))))/(minfo->parameter.current_limit[0])*minfo->parameter.current_limit[1];

}

float anglecircle(float angle)
{
	while(angle>180.f)
	{
		angle=angle-360.f;
	}
	while(angle<-180.f)
	{
		angle=angle+360.f;
	}

	return angle;
}

float anglelimit(float angle,float anglemax,float anglemin)
{
	return LIMIT(angle,anglemin,anglemax);
}

float currentlimit(float current,float currentmax)
{
	return LIMIT(current,-currentmax,currentmax);;
}

float speedlimit(float speed,float speedmax)
{
	return MIN( speed,speedmax );
}

