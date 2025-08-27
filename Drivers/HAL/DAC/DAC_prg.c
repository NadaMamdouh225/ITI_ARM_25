/*
 * DAC_prg.c
 *
 *  Created on: Aug 27, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"

#include "DAC_int.h"

u8 PortID ;
void HDAC_vInit(GPIOx_PinConfig_t *A_xPins, u8 A_u8PinsNo)
{

	PortID = A_xPins->Port;
	for(u8 i=0; i<A_u8PinsNo; i++)
		MGPIO_vPinInit(&A_xPins[i]);

	MSYSTICK_Config_t stk_cfg = {.InterruptEnable = INT_ENABLE, .CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(&stk_cfg);
}
void HDAC_vSendSample(const u8* A_u8Ptr, u32 A_u32Index)
{
	for(u8 i=0; i<8; i++)
	{
		MGPIO_vSetPinValue(PortID, i, GET_BIT(A_u8Ptr[A_u32Index],i));
	}
}
