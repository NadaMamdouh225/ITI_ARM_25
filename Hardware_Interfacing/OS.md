# Session: OS

## Lab 1: Blink 3 LED with different periodicity

```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../HAL/LEDMATRIX/LEDMATRIX_int.h"
#include "../OS/OS_int.h"

void led0(void);
void led1(void);
void led2(void);

int main(void)
{
	/* Enable Clock */
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);
	GPIOx_PinConfig_t leds[3] ={
			{GPIO_PORTA, GPIO_PIN0, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN2, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL}

	};
	for(u8 i=0;i<3;i++)
		MGPIO_vPinInit(&leds[i]);


	OS_u8CreateTask(led0, 5, 0, 0);
	OS_u8CreateTask(led1, 1, 1, 0);
	OS_u8CreateTask(led2, 10, 2, 0);

	OS_vStart();
	while(1)
	{

	}

	return 0 ;
}

void led0(void)
{
	MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN0);
}
void led1(void)
{
	MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN1);
}
void led2(void)
{
	MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN2);
}

```