# Session: TFT

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
#include "../HAL/TFT/TFT_int.h"
#include "Pic.h"

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);
	MRCC_vEnableClk(RCC_APB2, 12); // enable SPI1 clk

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

	HTFT_vInit();

	//	u16 size = sizeof(arr)/sizeof(arr[0]);
	//	HTFT_vShowImg(arr, size);

	HTFT_vFillBackgroundColor(0x0000);

	HTFT_vSetXPos(20, 20+50);
	HTFT_vSetYPos(20, 20+70);
	HTFT_vFillRectangle(0xFFFF);


	while(1)
	{

	}

	return 0 ;
}

```