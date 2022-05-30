#include "main.h"
void device_init(void)
{
	
	while(!Ut_ready)
	{
		Ut_init();
	}
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_2,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_3,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_5,GPIO_PIN_SET);
	while(!CAN1_ready)
	{
		can_filter_init();
	}
	
	MX_IWDG_Init();
}
