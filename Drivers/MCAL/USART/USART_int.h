/*
 * USART_int.h
 *
 *  Created on: Sep 1, 2025
 *      Author: Nada Mamdouh
 *      Version:0.1
 */

#ifndef SRC_MCAL_USART_USART_INT_H_
#define SRC_MCAL_USART_USART_INT_H_


void MUSART_vInit(void);
void MUSART_vSendData(u8 A_u8Data);
u8   MUSART_u8ReceiveData();

// TODO
void MUSART_vSendString(u8* A_u8ptrStr);
u8*  MUSART_u8ptrReceiveString(void); // check '\r' | '\n'
void MUSART_vUSARTCallBack(u8 A_u8USARTNo, void(*Fptr)(void));
u8   MUSART_u8Retreive_USART1_DataRegister(void);


#endif /* SRC_MCAL_USART_USART_INT_H_ */
