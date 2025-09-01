/*
 * USART_prg.c
 *
 *  Created on: Sep 1, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "USART_int.h"
#include "USART_prv.h"
#include "USART_cfg.h"

void MUSART_vInit(void)
{
	// oversample by 16
	CLR_BIT(USART1->CR1, OVER8);

	// word length 8 data
	CLR_BIT(USART1->CR1, 12);

	// no parity
	CLR_BIT(USART1->CR1, 10);

	// baudrate 9600, APB2 clk is 25MHz
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

