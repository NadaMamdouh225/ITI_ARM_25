/*
 * GPIO_int.h
 *
 *  Created on: Aug 17, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */

#ifndef MCAL_GPIO_GPIO_INT_H_
#define MCAL_GPIO_GPIO_INT_H_


#define GPIO_PORTA	0
#define GPIO_PORTB	1
#define GPIO_PORTC	2


void MGPIO_vSetMode(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Mode);
void MGPIO_vSetOutputType(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputType);
void MGPIO_vSetOutputSpeed(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputSpeed);
void MGPIO_vSetPUSH_PULL(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8PushPull);
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Value);
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinNum);
void MGPIO_vSetAlt(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8AFx);

#endif /* MCAL_GPIO_GPIO_INT_H_ */
