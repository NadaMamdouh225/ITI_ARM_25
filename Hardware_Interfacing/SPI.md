# Session: SPI

## Lab 1:

```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../MCAL/SPI/SPI_int.h"


int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);
	MRCC_vEnableClk(RCC_APB2, 12); // enable SPI1 clk

	MSPI_vInit();

	GPIOx_PinConfig_t led = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN1,
			.Mode = GPIO_MODE_OUTPUT,
			.Speed = GPIO_SPEED_LOW,
			.OutputType = GPIO_OT_PUSHPULL,
			.PullType = GPIO_NO_PULL
	};

	MGPIO_vPinInit(&led);

	// Init SPI pins

	GPIOx_PinConfig_t MISO = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN6,
			.Mode = GPIO_MODE_ALF,
			.Altfunc = GPIO_AF5
	};
	MGPIO_vPinInit(&MISO);

	GPIOx_PinConfig_t MOSI = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN7,
			.Mode = GPIO_MODE_ALF,
			.Altfunc = GPIO_AF5
	};
	MGPIO_vPinInit(&MOSI);


	GPIOx_PinConfig_t SCK = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN5,
			.Mode = GPIO_MODE_ALF,
			.Altfunc = GPIO_AF5
	};
	MGPIO_vPinInit(&SCK);

	u8 data = 0;
	data = MSPI_u8Transceive('T');
	if(data == 'T')
	{
		MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_HIGH);
	}


	while(1)
	{

	}

	return 0 ;
}


```