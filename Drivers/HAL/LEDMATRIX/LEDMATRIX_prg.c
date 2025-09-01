/*
 * LEDMATRIX_prg.c
 *
 *  Created on: Aug 21, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.2
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"
#include "../../HAL/S2P/S2P_int.h"

#include "LEDMATRIX_int.h"
#include "LEDMATRIX_prv.h"
#include "LEDMATRIX_cfg.h"

static void HLEDMATRIX_vEnableCurrentCol(u8 A_u8ColNo);
static void HLEDMATRIX_SetRowValue(u8 A_u8RowValue);
static void HLEDMATRIX_vDisableAllCol(void);

GPIOx_PinConfig_t *rows;
GPIOx_PinConfig_t *cols;
u8 NO_ROWS;
u8 NO_COLS;

void HLEDMATRIX_vInit_S2P(S2P_Init_t* A_xInit)
{
	S2P_vInit(A_xInit);

	/* Initialize Systick */
	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_DISABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

}
void HLEDMATRIX_vInit(GPIOx_PinConfig_t *A_xRows, u8 A_u8RowsNo, GPIOx_PinConfig_t *A_xCols, u8 A_u8ColNo)
{
	rows = A_xRows;
	cols = A_xCols;
	NO_ROWS = A_u8RowsNo;
	NO_COLS = A_u8ColNo;

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
#if METHOD == DIRECT_LEDMATRIX
			/* Set Row Value */
			HLEDMATRIX_SetRowValue(A_u8Frame[i]);

			/* Enable Current Col */
			HLEDMATRIX_vEnableCurrentCol(i);

			/* Calculated delay */
			MSYSTICK_vSetDelay_ms(SCAN_TIME);

			/* Disable All Cols */
			HLEDMATRIX_vDisableAllCol();
#endif
#if METHOD == S2P_CONNECTION
			// 1- disable cols
			//2- set row & enable current col
			//3- delay

#endif

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
