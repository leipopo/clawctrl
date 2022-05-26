#include "main.h"
clawinfo last_cinfo;

int8_t palmdifangledectect(void)
{
	if((minfo[2].parameter.zerodir*cinfo.curmotorinfo.angle[2]-\
		minfo[3].parameter.zerodir*cinfo.curmotorinfo.angle[3])>maxpalmdifangle)
	{
		if(cinfo.clawmode==0x04)
		{
			ucomd.modeset=0x04;
		}
		return 0x10;
	}
	else if((minfo[2].parameter.zerodir*cinfo.curmotorinfo.angle[2]-\
		minfo[3].parameter.zerodir*cinfo.curmotorinfo.angle[3])<-maxpalmdifangle)
	{
		if(cinfo.clawmode==0x04)
		{
			ucomd.modeset=0x04;
		}
		return 0x01;
	}
	else
		return 0x00;
}

int8_t lockdetect(void)
{
	int16_t sig=0x00;
	if(cinfo.clawmode!=0x02)
	{
		for(int8_t i=0;i<4;i++)
		{
			if((cinfo.curmotorinfo.angle[i]-last_cinfo.curmotorinfo.angle[i])<0.5f \
				&&(cinfo.curmotorinfo.torque[i]>4.f))
			{
				sig=(sig<<4)+1;
			}
		}
	}
	return sig;
}

void detecttask()
{
	for(;;)
	{
		HAL_UART_DMAResume(&huart3);
		last_cinfo=cinfo;
		uint8_t detectmes[12]={NULL,};
		detectmes[0]=0xAA;
		//高八位先进 
		detectmes[1]=palmdifangledectect();
		detectmes[2]=lockdetect()>>8;
		detectmes[3]=lockdetect();
		
		detectmes[11]=0x0a;
		HAL_UART_Transmit_DMA(&huart3,detectmes,sizeof(detectmes));
		HAL_UART_DMAPause(&huart3);
	}
}
