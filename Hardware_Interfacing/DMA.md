# Session: DMA

## Lab 1:
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/NVIC/NVIC_int.h"
#include "../MCAL/DMA/DMA_int.h"


void func (void);
u32 arr1[10] = {1,4,2,6,7,33,55,25,13,5};
u32 arr2[10] = {0};

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);
	MRCC_vEnableClk(RCC_AHB1, 22);  // Enable DMA2

	GPIOx_PinConfig_t Led = {
			.Port = GPIO_PORTA,
			.Pin = GPIO_PIN0,
			.Mode = GPIO_MODE_OUTPUT,
			.Speed = GPIO_SPEED_LOW,
			.OutputType = GPIO_OT_PUSHPULL
	};
	MGPIO_vPinInit(&Led);

	MNVIC_vEnable_Peripheral_INT(56);

	MDMA2_vInit(0);
	MDMA2_vSetStreamCfg(0, arr1, arr2, Word, Word, 10, FIFO_FULL);
	MDMA2_vCallBack(0,func);
	MDMA2_vEnableStream(0);


	while(1)
	{

	}

	return 0 ;
}

void func (void)
{
	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN0, GPIO_HIGH);
}

```