/*
 * TFT_prg.c
 *
 *  Created on: Sep 3, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/GPIO/GPIO_int.h"
#include "../../MCAL/SPI/SPI_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"

#include "TFT_int.h"
#include "TFT_cfg.h"

static u16 CurrentXStart;
static u16 CurrentXEnd;
static u16 CurrentYStart;
static u16 CurrentYEnd;


GPIOx_PinConfig_t TFT_RST_Pin  =
{
		.Port = GPIO_PORTA,
		.Pin = GPIO_PIN0,
		.Mode = GPIO_MODE_OUTPUT,
		.Speed= GPIO_SPEED_HIGH,
		.OutputType = GPIO_OT_PUSHPULL
};
GPIOx_PinConfig_t TFT_A0_Pin  =
{
		.Port = GPIO_PORTA,
		.Pin = GPIO_PIN1,
		.Mode = GPIO_MODE_OUTPUT,
		.Speed= GPIO_SPEED_HIGH,
		.OutputType = GPIO_OT_PUSHPULL
};
static void Write_cmd(u8 A_u8cmd)
{
	MGPIO_vSetPinValue(TFT_A0_Pin.Port, TFT_A0_Pin.Pin, GPIO_LOW);
	MSPI_u8Transceive(A_u8cmd);
}
static void Write_data(u8 A_u8data)
{
	MGPIO_vSetPinValue(TFT_A0_Pin.Port, TFT_A0_Pin.Pin, GPIO_HIGH);
	MSPI_u8Transceive(A_u8data);
}
static void Reset_Seq(void)
{
	MGPIO_vSetPinValue(TFT_RST_Pin.Port, TFT_RST_Pin.Pin, GPIO_HIGH);
	MSYSTICK_vSetDelay_us(100);
	MGPIO_vSetPinValue(TFT_RST_Pin.Port, TFT_RST_Pin.Pin, GPIO_LOW);
	MSYSTICK_vSetDelay_us(1);
	MGPIO_vSetPinValue(TFT_RST_Pin.Port, TFT_RST_Pin.Pin, GPIO_HIGH);
	MSYSTICK_vSetDelay_us(100);
	MGPIO_vSetPinValue(TFT_RST_Pin.Port, TFT_RST_Pin.Pin, GPIO_LOW);
	MSYSTICK_vSetDelay_us(100);
	MGPIO_vSetPinValue(TFT_RST_Pin.Port, TFT_RST_Pin.Pin, GPIO_HIGH);
	MSYSTICK_vSetDelay_ms(120);
}

void HTFT_vInit(void)
{
	// 0- Initialization
	MGPIO_vPinInit(&TFT_RST_Pin);
	MGPIO_vPinInit(&TFT_A0_Pin);

	MSPI_vInit();
	MSYSTICK_Config_t STK_cfg =
	{.InterruptEnable = INT_DISABLE, .CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(&STK_cfg);

	// 1- Reset Sequence
	Reset_Seq();

	// 2- sleep out mode
	Write_cmd(0x11);

	//3- wait 15ms
	MSYSTICK_vSetDelay_ms(15);

	//4 - send color command -> RGB565 ->0x05
	Write_cmd(0x3A);
	Write_data(0x05);

	//5- Display on
	Write_cmd(0x29);

}
void HTFT_vShowImg(const u16 A_u16ImgArr[],u16 A_u16ImgSize )
{
	u8 MSB = 0;
	u8 LSB = 0;
	//1.0 Set x position
	Write_cmd(0x2A);

	//1.1 send Xstart
	Write_data(0);
	Write_data(0);

	//1.2 send Xend
	Write_data(0);
	Write_data(127);

	//2.0 Set y position
	Write_cmd(0x2B);

	//2.1 send Ystart
	Write_data(0);
	Write_data(0);

	//2.2 send Yend
	Write_data(0);
	Write_data(159);

	//3.0 send img cmd
	Write_cmd(0x2C);

	//3.1 send img data
	for(u16 i =0; i<A_u16ImgSize; i++)
	{

		//MSB
		MSB = (A_u16ImgArr[i]& 0xff00)>>8 ;
		//LSB
		LSB = A_u16ImgArr[i] & 0x00ff;
		Write_data(MSB);
		Write_data(LSB);
	}

}

void HTFT_vSetXPos(u16 A_u16xStart, u16 A_u16xEnd)
{
	CurrentXStart = A_u16xStart;
	CurrentXEnd = A_u16xEnd;

	//1.0 Set x position
	Write_cmd(0x2A);

	//1.1 send Xstart
	Write_data(0);
	Write_data(A_u16xStart);

	//1.2 send Xend
	Write_data(0);
	Write_data(A_u16xEnd);
}
void HTFT_vSetYPos(u16 A_u16yStart, u16 A_u16yEnd)
{
	CurrentYStart = A_u16yStart;
	CurrentYEnd = A_u16yEnd;

	//2.0 Set y position
	Write_cmd(0x2B);

	//2.1 send Ystart
	Write_data(0);
	Write_data(A_u16yStart);

	//2.2 send Yend
	Write_data(0);
	Write_data(A_u16yEnd);
}
void HTFT_vFillBackgroundColor(u16 A_u16Color)
{
	HTFT_vSetXPos(0,127);

	HTFT_vSetYPos(0, 159);

	HTFT_vFillRectangle(A_u16Color);

}
void HTFT_vFillRectangle(u16 A_u16Color)
{
	u8 MSB = 0;
	u8 LSB = 0;

	u16 Pixels = (CurrentXEnd-CurrentXStart)*(CurrentYEnd-CurrentYStart);
	// send Color cmd
	Write_cmd(0x2C);

	// send Color data
	for(u16 i =0; i<Pixels; i++)
	{

		//MSB
		MSB = (A_u16Color& 0xff00)>>8 ;
		//LSB
		LSB = A_u16Color & 0x00ff;
		Write_data(MSB);
		Write_data(LSB);
	}
}
