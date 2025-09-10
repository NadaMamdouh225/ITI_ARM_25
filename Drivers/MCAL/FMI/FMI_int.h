/*
 * FMI_int.h
 *
 *  Created on : Sep 10, 2025
 *      Author : Nada Mamdouh
 *      Version: 0.0
 */

#ifndef SRC_MCAL_FMI_FMI_INT_H_
#define SRC_MCAL_FMI_FMI_INT_H_

typedef enum
{
	Sector0 = 0,    //
	Sector1,
	Sector2,
	Sector3,
	Sector4,
	Sector5
}Sector_t;


void MFMI_vMassErase(void);
void MFMI_vSectorErase(Sector_t A_xSectorNo);
void MFMI_vProgramFlash(u32 A_u32Address, u16* A_PtrData, u16 Datalength);


#endif /* SRC_MCAL_FMI_FMI_INT_H_ */
