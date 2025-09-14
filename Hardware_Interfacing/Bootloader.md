# Bootloader Session:
## Lab 1 : without USART
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
#define SCB_VTOR   *((volatile u32*)(0xE000ED00+0x08))

	void(*APP_CALL)(void);

	//1- initialize MSP
	u32 MSPAdress=*((volatile u32*)(SECTOR2_BASE_ADDR));
	__asm volatile("MSR MSP, %0"::"r"(MSPAdress));

	//2- Jump to reset handler
	u32 ResetHandlerAdress=*((volatile u32*)(SECTOR2_BASE_ADDR+4));
	APP_CALL=(void*)ResetHandlerAdress;

	//3- Vector table offset
	SCB_VTOR = SECTOR2_BASE_ADDR ;

	APP_CALL();
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
## Lab 2 `hint`: using 
```c
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/RCC/RCC_int.h"
#include "../MCAL/GPIO/GPIO_int.h"
#include "../MCAL/FMI/FMI_int.h"
#include "../MCAL/USART/USART_int.h"
#include "../MCAL/SYSTICK/SYSTICK_int.h"

#include "HexParser/HexParser_int.h"
//#include "test.h"
u8 TimeoutFlag = 0 ;
u8 G_pu8RxBuffer[50] ;
u8 G_u8RxBufferCounter = 0;
u8 EraseFlag = 0 ;

#define SECTOR2_BASE_ADDR	0x08008000

void JumpToApp(void)
{
#define SCB_VTOR   *((volatile u32*)(0xE000ED00+0x08))

	TimeoutFlag = 1 ;

	void(*APP_CALL)(void);

	//1- initialize MSP
	u32 MSPAdress=*((volatile u32*)(SECTOR2_BASE_ADDR));
	__asm volatile("MSR MSP, %0"::"r"(MSPAdress));

	//2- Jump to reset handler
	u32 ResetHandlerAdress=*((volatile u32*)(SECTOR2_BASE_ADDR+4));
	APP_CALL=(void*)ResetHandlerAdress;

	//3- Vector table offset
	SCB_VTOR = SECTOR2_BASE_ADDR ;

	APP_CALL();
}
int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, RCC_GPIOA);
	MRCC_vEnableClk(RCC_APB2, 4); // enable usart clk

	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_ENABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

	MUSART_vInit();
	MUSART_vEnable_RX_Interrupt();
	MNVIC_vEnable_Peripheral_INT(37); // uart interrupt
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

	GPIOx_PinConfig_t led={
			.Port = GPIO_PORTA,
			.Pin  = GPIO_PIN1,
			.Mode = GPIO_MODE_OUTPUT,
			.Speed= GPIO_SPEED_LOW,
			.OutputType= GPIO_OT_PUSHPULL
	};

	MGPIO_vPinInit(&led);

	/************************************************************/
//	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_HIGH);
//
//	MFMI_vSectorErase(Sector2);
//	for(u16 i=0; i<241; i++)
//	{
//		AHexParser_vParseRecord(arr[i]);
//	}
//
//	MGPIO_vSetPinValue(GPIO_PORTA, GPIO_PIN1, GPIO_LOW);
	/************************************************************/

	MSYSTICK_vSetInterval_Single(15000,JumpToApp);

	u8 L_u8UsartRXStatus = 0;
	while(TimeoutFlag == 0)
	{
		L_u8UsartRXStatus = MUSART_vReceive_synch(&G_pu8RxBuffer[G_u8RxBufferCounter]) ;
		if(L_u8UsartRXStatus == 1)
		{
			if(EraseFlag != 1)
			{
				EraseFlag = 1;
				MFMI_vSectorErase(Sector2);
			}


			/* stop the timeout */
			MSYSTICK_vStopTimer(); 

			if(G_pu8RxBuffer[G_u8RxBufferCounter] == '\n')
			{

				AHexParser_vParseData(G_pu8RxBuffer);
				MUSART_vSendString("ok");
				G_u8RxBufferCounter = 0 ;
			}
			else
			{
				G_u8RxBufferCounter++ ;
			}

			// End of file
			if(G_pu8RxBuffer[8] == '1')
			{
				MSYSTICK_vSetInterval_Single(10000,JumpToApp);
			}
		}
	}

	return 0 ;
}


```