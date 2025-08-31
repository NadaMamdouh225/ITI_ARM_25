# Session: IR
## Lab 1:
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"

volatile u8 G_u8Value = 0;
volatile u8 G_u8StartFlag = 0;
volatile u8 G_u8Counter = 0;
volatile u32 A_u32arr[50]={0};

void APP_Get_time(void);
void APP_DecodeBits(void);

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);
	MRCC_vEnableClk(RCC_APB2, 14);

	// gpio init
	GPIOx_PinConfig_t IR_pin = {.Port=GPIO_PORTA, .Pin= GPIO_PIN0,.Mode = GPIO_MODE_INPUT};
	MGPIO_vPinInit(&IR_pin);

	GPIOx_PinConfig_t Led_pin = {.Port=GPIO_PORTA, .Pin= GPIO_PIN7,.Mode = GPIO_MODE_OUTPUT, .Speed = GPIO_SPEED_LOW, .OutputType = GPIO_OT_PUSHPULL};
	MGPIO_vPinInit(&Led_pin);

	// Configure interrupt
	MNVIC_vEnable_Peripheral_INT(6);
	EXTI_Cng_t A_xCfg = {0,0};
	MEXTI_vInit(&A_xCfg);
	MEXTI_vEnableINT(EXTI_LINE0, EXTI_FALLING_EDGE);
	MEXTI_vSetCallBack(APP_Get_time, EXTI_LINE0);

	// Configure systick
	MSYSTICK_Config_t STK_cfg = {.InterruptEnable = INT_ENABLE, .CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(&STK_cfg);
	while(1)
	{
		switch(G_u8Value)
		{
		// 1 is pressed
		case 12:
			MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_HIGH);
			break;
			// 2 is pressed
		case 24:
			MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_LOW);
			break;
			// 8 is pressed
		case 82:
			MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN7, GPIO_LOW);
			break;
		}
	}

	return 0 ;
}

void APP_Get_time(void)
{
	if(G_u8StartFlag == 0)
	{
		//for startbit -> should be used one time only
		G_u8StartFlag = 1;
		//		MSYSTICK_vStartTimer(15);
		MSYSTICK_vSetInterval_Single(15, APP_DecodeBits);

	}else
	{
		// calculate
		A_u32arr[G_u8Counter++] = (MSYSTICK_u32GetElapsedTime_SingleShot()/3.125);
		//		MSYSTICK_vStartTimer(4);
		MSYSTICK_vSetInterval_Single(4, APP_DecodeBits);
	}
}
void APP_DecodeBits(void)
{
	G_u8Value = 0;
	for(u8 i =0; i<8; i++)
	{
		if((A_u32arr[17+i] >= 1000) && ((A_u32arr[17+i])<1250))
		{
			CLR_BIT(G_u8Value,i);
		}
		else if((A_u32arr[17+i] >=2000) && ((A_u32arr[17+i])<2450))
		{
			SET_BIT(G_u8Value,i);
		}
	}
	G_u8StartFlag = 0;
	G_u8Counter = 0;

	// reset frame data
	for(u8 i =0; i<50; i++)
		A_u32arr[i]=0;

}

```