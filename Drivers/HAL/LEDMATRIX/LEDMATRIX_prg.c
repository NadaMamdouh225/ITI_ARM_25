/*
 * LEDMATRIX_prg.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"

#include "LEDMATRIX_int.h"
#include "LEDMATRIX_cfg.h"

static void HLEDMATRIX_vEnableCurrentCol(u8 A_u8ColNo);
static void HLEDMATRIX_SetRowValue(u8 A_u8RowValue);
static void HLEDMATRIX_vDisableAllCol(void);

GPIOx_PinConfig_t rows[NO_ROWS] = {
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN0, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN1, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN2, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN3, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN4, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN5, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN6, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTA,.Pin = GPIO_PIN7, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
};

GPIOx_PinConfig_t cols[NO_COLS] = {
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN0, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN1, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN2, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN5, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN6, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN7, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN8, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
		{.Port = GPIO_PORTB,.Pin = GPIO_PIN9, .Mode = GPIO_MODE_OUTPUT, .OutputType = GPIO_OT_PUSHPULL, .Speed = GPIO_SPEED_LOW},
};

void HLEDMATRIX_vInit(void)
{

	for(u8 i=0; i<NO_ROWS; i++)
	{
		MGPIO_vPinInit(&rows[i]);
	}
	for(u8 i=0; i<NO_COLS; i++)
	{
		MGPIO_vPinInit(&cols[i]);
	}
	/* Initialize Systick */
	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_DISABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

}
void HLEDMATRIX_DisplayFrame(u8 A_u8Frame[], u32 A_u32FrameDelay)
{
	for(u32 j = 0; j< A_u32FrameDelay; j++)
	{

		for(u8 i = 0; i<NO_COLS; i++)
		{
			/* Set Row Value */
			HLEDMATRIX_SetRowValue(A_u8Frame[i]);

			/* Enable Current Col */
			HLEDMATRIX_vEnableCurrentCol(i);

			/* Calculated delay */
			MSYSTICK_vSetDelay_ms(SCAN_TIME);

			/* Disable All Cols */
			HLEDMATRIX_vDisableAllCol();
		}
	}

}

void HLEDMATRIX_vEnableCurrentCol(u8 A_u8ColNo)
{
	MGPIO_vSetPinValue(cols[A_u8ColNo].Port,cols[A_u8ColNo].Pin ,GPIO_LOW );
}
static void HLEDMATRIX_SetRowValue(u8 A_u8RowValue)
{
	for(u8 i = 0; i< NO_ROWS; i++)
		MGPIO_vSetPinValue(rows[i].Port, rows[i].Pin, GET_BIT(A_u8RowValue,i) );
}
static void HLEDMATRIX_vDisableAllCol(void)
{
	for(u8 i = 0; i< NO_COLS; i++)
		MGPIO_vSetPinValue(cols[i].Port,cols[i].Pin ,GPIO_HIGH );
}
