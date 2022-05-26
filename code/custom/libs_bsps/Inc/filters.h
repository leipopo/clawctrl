#ifndef __MATHTOOLS_H__
#define __MATHTOOLS_H__

#define LIMIT( X,MIN,MAX ) ( (X) < (MIN) ? (MIN) : ((X) > (MAX) ? (MAX) : (X)) )
#define MIN( A,B ) ( (A) < (B) ? (A) : (B) )
#define MAX( A,B ) ( (A) > (B) ? (A) : (B) )
#define ABS( X ) ( (X) > 0 ? (X) : (-(X)) )
#define REAL_DEADZONE_CAL( GET,OFFSET,DEADZONE ) ( ((GET) - (OFFSET)) > (DEADZONE) ? ((GET) - (OFFSET)) : (((OFFSET) - (GET)) > (DEADZONE) ? ((GET) - (OFFSET)) : 0) )

#define LIMIT_CAMERA(X) (X>100 ? (X-200) : X)
#define PI 3.14159f

#include "stdint.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "math.h"
#include "string.h"



typedef struct{

	float data_in[4];					//输入参数
	float data_out[4];				//输出参数
	float den;
	float a;                  //x[n]的系数
	float b;                  //y[n-1]的系数
	float c;                  //y[n-2]的系数
}filter_date;


float first_order_filter(float filter_in ,float filter_out, uint16_t filter_parameter);
float first_order_filter_dail(float *filter,float filter_in ,float filter_out, float filter_parameter);
float GetMedianNum(float * bArray, int iFilterLen, float mean_in);
float my_deathzoom(float x,float zoom);

float glide_filter(float ADNum,uint8_t count_number);

void Calculate_FilteringCoefficient(float Time, float Cut_Off);
float ACC_IIR_Filter( float date_in,float date_out);
int isNaN(float f);
typedef struct{
	float raw_date1;   									//未滤波的原始数据
	float raw_date2;   									//参与滤波的数据
	float last_raw_date;								//上一次滤波后的数据
	float T;
	float K1;
}filtering_;
float Complementary_filtering(volatile filtering_ *p);


#endif
