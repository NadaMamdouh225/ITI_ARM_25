# Session: SYSTICK

## Lab1: Use Systick Timer as Delay
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"



int main(void)
{
	/* Enable Clock */
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);

	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_DISABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

	/* Configure Pins */
	GPIOx_PinConfig_t led =
	{GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL};
	MGPIO_vPinInit(&led);




	while(1)
	{
		MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_HIGH);
		MSYSTICK_vSetDelay_ms(1000);
		MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_LOW);
		MSYSTICK_vSetDelay_ms(1000);
	}

	return 0 ;
}


```

## Lab2: Toggle LED with Interrupt
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"

void TogLed(void);

int main(void)
{
	/* Enable Clock */
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);

	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_ENABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

	/* Configure Pins */
	GPIOx_PinConfig_t led =
	{GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL};
	MGPIO_vPinInit(&led);

	MSYSTICK_vSetInterval_Multi(500, TogLed);


	while(1)
	{

	}

	return 0 ;
}

void TogLed(void)
{
	MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN1);
}

```