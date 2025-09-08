/*
 * USART_prg.c
 *
 *  Created on: Sep 1, 2025
 *      Author: Nada Mamdouh
 *      Version:0.1
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_int.h"
#include "USART_prv.h"
#include "USART_cfg.h"

u8 G_Buffer[50];
void (*G_Fpt[3])(void)={NULL};
// G_Fpt[0] -> USART1
// G_Fpt[1] -> USART2
// G_Fpt[2] -> USART6
void MUSART_vInit(void)
{
	// oversample by 16
	CLR_BIT(USART1->CR1, OVER8);

	// word length 8 data
	CLR_BIT(USART1->CR1, 12);

	// no parity
	CLR_BIT(USART1->CR1, 10);

	// baudrate 9600
	USART1->BRR = 162<<4 | 13;

	// 1 stop bit
	CLR_BIT(USART1->CR2, 12);
	CLR_BIT(USART1->CR2, 13);

	// Enable transmit
	SET_BIT(USART1->CR1, 3);

	// Enable Receive
	SET_BIT(USART1->CR1, 2);

	// enable usart
	SET_BIT(USART1->CR1, 13);
}
void MUSART_vSendData(u8 A_u8Data)
{
	/* Check whether register empty or not */
	while(!GET_BIT(USART1->SR,7))
		;
	USART1->DR = A_u8Data;

	/* Wait until data is transmitted */
	while(!GET_BIT(USART1->SR,6))
		;
	/* clear TC bit */
	CLR_BIT(USART1->SR, 6);
}
u8   MUSART_u8ReceiveData()
{
	while(!GET_BIT(USART1->SR,5))
		;
	return USART1->DR;
}
void MUSART_vSendString(u8* A_u8ptrStr)
{
	u8 L_u8Index = 0;
	while(A_u8ptrStr[L_u8Index]!='\0')
		MUSART_vSendData(A_u8ptrStr[L_u8Index++]);

}
u8*  MUSART_u8ptrReceiveString(void) // check '\r' | '\n'
{
	u8 L_u8index = 0;
	// carrige return
	while(MUSART_u8ReceiveData()!='\r')
	{
		G_Buffer[L_u8index] = MUSART_u8ReceiveData();
		L_u8index++;
	}
	G_Buffer[L_u8index] = '\0';
	return G_Buffer;
}
void MUSART_vUSARTCallBack(u8 A_u8USARTNo, void(*Fptr)(void))
{
	// G_Fpt[0] -> USART1
	// G_Fpt[1] -> USART2
	// G_Fpt[2] -> USART6
	u8 L_u8index = (A_u8USARTNo==1)?0:(A_u8USARTNo==2)?1:2;
	G_Fpt[L_u8index] = Fptr;
}
u8   MUSART_u8Retreive_USART1_DataRegister(void)
{
	return USART1->DR;
}

void USART1_IRQHandler(void)
{
	if(G_Fpt[0] != NULL)
	{
		G_Fpt[0]();
	}
	USART1->SR = 0;
}
