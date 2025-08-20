# Session: NVIC

# Lab: Test NVIC
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"


int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);

	GPIOx_PinConfig_t led =
	{GPIO_PORTA, GPIO_PIN0, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL};

	MGPIO_vPinInit(&led);

	MNVIC_vSetPendingFlag(6);
	MNVIC_vEnable_Peripheral_INT(6);

	while(1)
	{}

	return 0 ;
}

void EXTI0_IRQHandler(void)
{
	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_HIGH);
}

```
