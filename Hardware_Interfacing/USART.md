# Session: USART

## Lab 1:

```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../MCAL/USART/USART_int.h"


int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);
	MRCC_vEnableClk(RCC_APB2, 4); // enable usart clk

	MUSART_vInit();
	GPIOx_PinConfig_t led = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN8,
			.Mode = GPIO_MODE_OUTPUT,
			.Speed = GPIO_SPEED_LOW,
			.OutputType = GPIO_OT_PUSHPULL,
			.PullType = GPIO_NO_PULL
		};
	MGPIO_vPinInit(&led);

	// init USART pins

	GPIOx_PinConfig_t tx = {
		.Port = GPIO_PORTA,
		.Pin = GPIO_PIN9,
		.Mode = GPIO_MODE_ALF,
		.Altfunc = GPIO_AF7
	};
	GPIOx_PinConfig_t rx = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN10,
			.Mode = GPIO_MODE_ALF,
			.Altfunc = GPIO_AF7
		};

	MGPIO_vPinInit(&tx);
	MGPIO_vPinInit(&rx);

	MUSART_vSendData('A');
	u8 storeData = MUSART_u8ReceiveData();
	if(storeData == 'A')
	{
		MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN8, GPIO_HIGH);
	}

	while(1)
	{

	}

	return 0 ;
}


```