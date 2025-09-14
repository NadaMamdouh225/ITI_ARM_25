# Bootloader Session:
## Lab 1:
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/FMI/FMI_int.h"

#include "HexParser/HexParser_int.h"
#include "test.h"

#define SECTOR2_BASE_ADDR	0x08008000

void JumpToApp(void)
{
#define SCB_VTOR	*((volatile u32*)(0xE000ED00+ 0x08))

	void (*APP)(void);

	//1- initialize MSP with value inside sector2 base address
	u32 MSPValue = *((volatile u32*)(SECTOR2_BASE_ADDR));
	__asm volatile("MSR MSP, %0"::"r"(MSPValue));

	//2- Jump to reset handler
	APP = *((volatile u32*)(SECTOR2_BASE_ADDR+4));

	//3- Vector table offset
	SCB_VTOR = SECTOR2_BASE_ADDR;

	APP();


}
int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);

	GPIOx_PinConfig_t led={
			.Port = GPIO_PORTA,
			.Pin  = GPIO_PIN1,
			.Mode = GPIO_MODE_OUTPUT,
			.Speed= GPIO_SPEED_LOW,
			.OutputType= GPIO_OT_PUSHPULL
	};

	MGPIO_vPinInit(&led);
	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_HIGH);

	MFMI_vSectorErase(Sector2);
	for(u16 i=0; i<241; i++)
	{
		AHexParser_vParseRecord(arr[i]);
	}

	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_LOW);
	JumpToApp();

	while(1)
	{

	}

	return 0 ;
}


```