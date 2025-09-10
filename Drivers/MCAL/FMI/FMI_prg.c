/*
 * FMI_prg.c
 *
 *  Created on : Sep 10, 2025
 *      Author : Nada Mamdouh
 *      Version: 0.0
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "FMI_int.h"
#include "FMI_prv.h"
#include "FMI_cfg.h"

void MFMI_vMassErase(void)
{
	//1- wait on busy flag
	while(GET_BIT(FMI->SR, BSY))
		;
	//2- if locked CR register -> unlock
	if(GET_BIT(FMI->CR, LOCK))
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}

	//3- Set the MER bit in the FLASH_CR
	SET_BIT(FMI->CR, MER);

	//4- Set the STRT bit in the FLASH_CR
	SET_BIT(FMI->CR, STRT);

	//5- Wait for the BSY bit to be cleared
	while(GET_BIT(FMI->SR, BSY))
		;
	//6- Turn off mass erase
	CLR_BIT(FMI->CR, MER);

}
void MFMI_vSectorErase(Sector_t A_xSectorNo)
{
	//1- wait on busy flag
	while(GET_BIT(FMI->SR, BSY))
		;
	//2- if locked CR register -> unlock
	if(GET_BIT(FMI->CR, LOCK))
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	//3- Select sector to erase
	FMI->CR &= ~(0b1111<<SNB);
	FMI->CR |= (A_xSectorNo<<SNB);

	//4- Select sector erase
	SET_BIT(FMI->CR, SER);

	//4- Set the STRT bit in the FLASH_CR
	SET_BIT(FMI->CR, STRT);

	//5- Wait for the BSY bit to be cleared
	while(GET_BIT(FMI->SR, BSY))
		;
	//6- Turn off mass erase
	CLR_BIT(FMI->CR, SER);
}
void MFMI_vProgramFlash(u32 A_u32Address, u16* A_PtrData, u16 Datalength)
{
	//1- wait on busy flag
	while(GET_BIT(FMI->SR, BSY))
		;
	//2- if locked CR register -> unlock
	if(GET_BIT(FMI->CR, LOCK))
	{
		FMI->KEYR = KEY1;
		FMI->KEYR = KEY2;
	}
	//3- Select width (16 bit) to be programmed
	FMI->CR &= ~(0b11<<PSIZE);
	FMI->CR |= (1<<PSIZE);

	// Select programming mode
	SET_BIT(FMI->CR, PG);

	for(u16 i=0; i<Datalength; i++)
	{
		// save data in address
		*((volatile u16*)A_u32Address)  = A_PtrData[i];
		A_u32Address+=2;

		//wait on busy flag
		while(GET_BIT(FMI->SR, BSY))
			;
	}
	// Stop programming mode
	CLR_BIT(FMI->CR, PG);


}
