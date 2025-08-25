# Session: FreeRTOS
## Environment Setup:
<img src="../assets/_3.png" width="400px">
<br>

<img src="../assets/_4.png" width="400px">
<br>

## Lab 1: We have two tasks. First task blinks a LED every 200 msec and the other one blinks a LED every 1000 msec.
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

void Task_LED1(void *A_Pv);
void Task_LED2(void *A_Pv);


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

	/* Create Task */
	xTaskCreate(Task_LED1,(const char * const) "LED1", 100,  NULL, 1, NULL);
	xTaskCreate(Task_LED2,(const char * const) "LED2", 100,  NULL, 3, NULL);


	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0 ;
}


void Task_LED1(void *A_Pv)
{
	while(1)
	{
		MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN0);
		vTaskDelay(200);
	}
}
void Task_LED2(void *A_Pv)
{
	while(1)
	{
		MGPIO_TogPinValue(GPIO_PORTA, GPIO_PIN1);
		vTaskDelay(1000);
	}

}

```