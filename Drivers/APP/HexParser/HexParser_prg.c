/*
 * HexParser_prg.c
 *
 *  Created on: Sep 11, 2025
 *  Author    : Nada Mamdouh
 *  Version   : 0.0
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/FMI/FMI_int.h"

#include "HexParser_int.h"


#define G_HIGH_ADDRESS	0x08000000

static u8 AHexParser_u8ASCCI_to_Hex(u8 A_u8ASCCI)
{
	u8 L_u8Value = 0;
	if(A_u8ASCCI >= '0' &&  A_u8ASCCI <='9')
	{
		L_u8Value =  A_u8ASCCI - '0';
	}else
	{
		L_u8Value = A_u8ASCCI - 55;
	}

	return L_u8Value;
}

void AHexParser_vParseRecord(const s8* A_s8Record)
{
	u8 L_u8Var = AHexParser_u8ASCCI_to_Hex(A_s8Record[8]);
	switch(L_u8Var)
	{
	case 0:
		AHexParser_vParseData(A_s8Record);
		break;
	case 1:
		// end of file
		break;
	case 4:
		// set high address
		break;
	default:
		break;
	}
}
void AHexParser_vParseData(const s8* A_s8Record)
{
	// Set Character count
	u8 CC_high = AHexParser_u8ASCCI_to_Hex(A_s8Record[1]);
	u8 CC_low = AHexParser_u8ASCCI_to_Hex(A_s8Record[2]);
	u8 CC = (CC_high<<4) | CC_low;

	// Low Part Address
	u8 Address0 = AHexParser_u8ASCCI_to_Hex(A_s8Record[3]);
	u8 Address1 = AHexParser_u8ASCCI_to_Hex(A_s8Record[4]);
	u8 Address2 = AHexParser_u8ASCCI_to_Hex(A_s8Record[5]);
	u8 Address3 = AHexParser_u8ASCCI_to_Hex(A_s8Record[6]);

	// 0b 0000 0000 Address2 Address3
	u16 LowAddress =  (Address0<<12) | (Address1<<8) | (Address2<<4) | Address3;

	u32 Address = G_HIGH_ADDRESS | LowAddress;

	u16 Data[10] = {0};

	for(u8 i=0; i<(CC/2); i++)
	{
		u8 digit0 = AHexParser_u8ASCCI_to_Hex(A_s8Record[9  + (4*i)]);
		u8 digit1 = AHexParser_u8ASCCI_to_Hex(A_s8Record[10 + (4*i)]);
		u8 digit2 = AHexParser_u8ASCCI_to_Hex(A_s8Record[11 + (4*i)]);
		u8 digit3 = AHexParser_u8ASCCI_to_Hex(A_s8Record[12 + (4*i)]);

//		Data[i] = (digit0<<12) | (digit1<<8) | (digit2<<4) | (digit3); //
		Data[i] = (digit0<<4) | (digit1) | (digit2<<12) | (digit3<<8); //

	}

	MFMI_vProgramFlash(Address, Data, (CC/2));
}
