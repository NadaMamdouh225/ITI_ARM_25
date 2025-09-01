/*
 * USART_int.h
 *
 *  Created on: Sep 1, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */

#ifndef SRC_MCAL_USART_USART_INT_H_
#define SRC_MCAL_USART_USART_INT_H_


void MUSART_vInit(void);
void MUSART_vSendData(u8 A_u8Data);
u8   MUSART_u8ReceiveData();

#endif /* SRC_MCAL_USART_USART_INT_H_ */
