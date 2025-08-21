# Session: EXTI

## Lab: Toggel an LED when EXTI is triggered

```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/EXTI/EXTI_int.h"

void TogLed(void);
int main(void)
{
	/* Enable Clock */
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);
	MRCC_vEnableClk(RCC_APB2, 14);

	/* Configure Pins */
	GPIOx_PinConfig_t led =
	{GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL};
	GPIOx_PinConfig_t button =
	{GPIO_PORTA, GPIO_PIN0, GPIO_MODE_INPUT, .PullType = GPIO_PULL_UP};

	MGPIO_vPinInit(&led);
	MGPIO_vPinInit(&button);

	/* Enable INT */
	EXTI_Cng_t x = {0,0};       // no need right now, just to keep init func as it is
	MEXTI_vInit(&x);
	MEXTI_vEnableINT(EXTI_LINE0, EXTI_FALLING_EDGE);
	MEXTI_vSetCallBack(TogLed,EXTI_LINE0);

	MNVIC_vEnable_Peripheral_INT(6);


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
