/*
 * ESP8266_prg.c
 *
 *  Created on: Sep 8, 2025
 *      Author: pc
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/USART/USART_int.h"
#include "../../MCAL/SYSTICK/SYSTICK_int.h"

#include "ESP8266_int.h"

volatile char recv_buffer[BUFFER_SIZE];
static u32 BufferIterator = 0;
void USART_CB(void)
{
	recv_buffer[BufferIterator] = MUSART_u8Retreive_USART1_DataRegister();
	BufferIterator++;
}


void HESP8266_vInit(void)
{
	// Enter  -> \r
	// ctrl+j -> \n
	MSYSTICK_Config_t STK_cfg = {.InterruptEnable= INT_DISABLE ,.CLK_SRC = CLK_SRC_AHB_8};
	MSYSTICK_vInit(& STK_cfg);

	MUSART_vInit();  //Modify: set baud rate to 115200 & enable interrupt & NVIC
	MUSART_vUSARTCallBack(1, USART_CB);

	// no Echo
	MUSART_vSendString("ATE0\r\n");

	// Mode: station = 1
	MUSART_vSendString("AT+CWMODE=1\r\n");

}
void HESP8266_vConnectAccessPoint(char* A_s8SSID, char* A_s8Password)
{
	MUSART_vSendString("AT+CWJAP =\"");
	MUSART_vSendString(A_s8SSID);
	MUSART_vSendString("\", \"");
	MUSART_vSendString(A_s8Password);
	MUSART_vSendString("\"\r\n");

	// return error state | delay
	MSYSTICK_vSetDelay_ms(2000);
}
void HESP8266_vOpenServerTCPConnection(char* IP, char *SocketNo)
{
	MUSART_vSendString("AT+CIPSTART=\"TCP\",");
	MUSART_vSendString(IP);
	MUSART_vSendString("\",");
	MUSART_vSendString(SocketNo);
	MUSART_vSendString("\r\n");

	// busy wait delay
	MSYSTICK_vSetDelay_ms(2000);
}

void HESP8266_vSendHttpRequest(char* URL)
{
	u16 DataLength = sizeof(URL)/sizeof(URL[0]);
	MUSART_vSendString("AT+CIPSEND=");

	DataLength+=6; // GET(3 char + 1 space +\r\n 2 chars) = 6
	// implement this function
	InttoStr(DataLength, numStr);

	MUSART_vSendString(numStr);
	MUSART_vSendString("\r\n");

	// busy wait delay
	MSYSTICK_vSetDelay_ms(2000);

	MUSART_vSendString("GET ");
	MUSART_vSendString(URL);
	MUSART_vSendString("\r\n");

	// busy wait delay
	MSYSTICK_vSetDelay_ms(2000);

}
