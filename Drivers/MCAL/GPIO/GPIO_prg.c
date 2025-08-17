/*
 * GPIO_prg.c
 *
 *  Created on: Aug 17, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "GPIO_int.h"
#include "GPIO_prv.h"
#include "GPIO_cfg.h"

/*Forbidden
 * PortA = A13, A14, A15
 * PortB = B4, B3
 * */
void MGPIO_vSetMode(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Mode)
{
	if(GPIOA->MODER && (A_u8PinNum == 13|| A_u8PinNum == 14|| A_u8PinNum == 15))
	{

	}else{


		switch(A_u8PortID)
		{
		case GPIO_PORTA:
			GPIOA->MODER &= ~(0b11<<(A_u8PinNum*2));
			GPIOA->MODER |= (A_u8Mode<<(A_u8PinNum*2));
			break;
		case GPIO_PORTB:
			GPIOB->MODER &= ~(0b11<<(A_u8PinNum*2));
			GPIOB->MODER |= (A_u8Mode<<(A_u8PinNum*2));
			break;
		case GPIO_PORTC:
			GPIOC->MODER &= ~(0b11<<(A_u8PinNum*2));
			GPIOC->MODER |= (A_u8Mode<<(A_u8PinNum*2));
			break;
		}
	}
}
void MGPIO_vSetOutputType(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputType)
{
	if(A_u8OutputType == PushPull )
	{
		switch(A_u8PortID)
		{
		case GPIO_PORTA:
			CLR_BIT(GPIOA -> OTYPER, A_u8PinNum);
			break;
		case GPIO_PORTB:
			CLR_BIT(GPIOB -> OTYPER, A_u8PinNum);
			break;
		case GPIO_PORTC:
			CLR_BIT(GPIOC -> OTYPER, A_u8PinNum);
			break;
		}
	}else if(A_u8OutputType == OpenDrain )
	{
		switch(A_u8PortID)
		{
		case GPIO_PORTA:
			SET_BIT(GPIOA -> OTYPER, A_u8PinNum);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB -> OTYPER, A_u8PinNum);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC -> OTYPER, A_u8PinNum);
			break;
		}
	}
}
void MGPIO_vSetOutputSpeed(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8OutputSpeed)
{
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOA->OSPEEDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOA->OSPEEDR |= (A_u8OutputSpeed<<(A_u8PinNum*2));
		break;
	case GPIO_PORTB:
		GPIOB->OSPEEDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOB->OSPEEDR |= (A_u8OutputSpeed<<(A_u8PinNum*2));
		break;
	case GPIO_PORTC:
		GPIOC->OSPEEDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOC->OSPEEDR |= (A_u8OutputSpeed<<(A_u8PinNum*2));
		break;
	}
}
void MGPIO_vSetPUSH_PULL(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8PushPull)
{
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOA->PUPDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOA->PUPDR |= (A_u8PushPull<<(A_u8PinNum*2));
		break;
	case GPIO_PORTB:
		GPIOB->PUPDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOB->PUPDR |= (A_u8PushPull<<(A_u8PinNum*2));
		break;
	case GPIO_PORTC:
		GPIOC->PUPDR &= ~(0b11<<(A_u8PinNum*2));
		GPIOC->PUPDR |= (A_u8PushPull<<(A_u8PinNum*2));
		break;
	}
}
void MGPIO_vSetPinValue(u8 A_u8PortID, u8 A_u8PinNum, u8 A_u8Value)
{
	if (A_u8Value == GPIO_HIGH)
	{
		switch(A_u8PortID)
		{
		case GPIO_PORTA:
			SET_BIT(GPIOA -> ODR, A_u8PinNum);
			break;
		case GPIO_PORTB:
			SET_BIT(GPIOB -> ODR, A_u8PinNum);
			break;
		case GPIO_PORTC:
			SET_BIT(GPIOC -> ODR, A_u8PinNum);
			break;
		}
	}else if(A_u8Value == GPIO_LOW)
	{
		switch(A_u8PortID)
		{
		case GPIO_PORTA:
			CLR_BIT(GPIOA -> ODR, A_u8PinNum);
			break;
		case GPIO_PORTB:
			CLR_BIT(GPIOB -> ODR, A_u8PinNum);
			break;
		case GPIO_PORTC:
			CLR_BIT(GPIOC -> ODR, A_u8PinNum);
			break;
		}
	}

}
u8 MGPIO_u8GetPinValue(u8 A_u8PortID, u8 A_u8PinNum)
{
	u8 L_u8Value;
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		L_u8Value = GET_BIT(GPIOA -> IDR, A_u8PinNum);
		break;
	case GPIO_PORTB:
		L_u8Value = GET_BIT(GPIOB -> IDR, A_u8PinNum);
		break;
	case GPIO_PORTC:
		L_u8Value = GET_BIT(GPIOC -> IDR, A_u8PinNum);
		break;
	}
	return L_u8Value;

}
void MGPIO_vSetAlt(u8 A_u8PortID, u8 A_u8PinNum, u16 A_u16AFx)
{

}



