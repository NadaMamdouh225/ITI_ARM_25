# Session: DAC

## Lab 1:
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"
#include "../HAL/DAC/DAC_int.h"

#include "song.h"

void DAC_handler (void);

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIO_PORTA);

	GPIOx_PinConfig_t dac_pins[8] = {
			{GPIO_PORTA, GPIO_PIN0, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN1, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN2, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN3, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN4, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN5, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN6, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},
			{GPIO_PORTA, GPIO_PIN7, GPIO_MODE_OUTPUT, GPIO_OT_PUSHPULL, GPIO_SPEED_LOW, GPIO_NO_PULL},

	};

	HDAC_vInit(dac_pins, 8);

	MSYSTICK_vSetInterval_Multi(391,DAC_handler);

	while(1)
	{

	}

	return 0 ;
}

void DAC_handler (void)
{
	//	0x7f
	//	0b0111 11 1 1
	//	          A1  A0
	static u32 iterator = 0;
	HDAC_vSendSample(new_raw, iterator);

	if (iterator < new_raw_len)
	{
		iterator++;
	}else
	{
		iterator = 0;
	}


}
```