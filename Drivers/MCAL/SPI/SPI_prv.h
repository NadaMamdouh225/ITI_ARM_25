/*
 * SPI_prv.h
 *
 *  Created on: Sep 2, 2025
 *      Author: Nada Mamdouh
 */

#ifndef SRC_MCAL_SPI_SPI_PRV_H_
#define SRC_MCAL_SPI_SPI_PRV_H_

#define SP1_BASE_ADDR		0x40013000U
#define SP2_BASE_ADDR		0x40003800U
#define SP3_BASE_ADDR		0x40003C00U
#define SP4_BASE_ADDR		0x40013400U

typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SR;
	u32 DR;
	u32 CRCPR;
	u32 RXCRCR;
	u32 TXCRCR;
	u32 I2SCFGR;
	u32 I2SPR;

}SPIx_MemMap_t;

#define SPI1	((volatile SPIx_MemMap_t*)(SP1_BASE_ADDR))
#define SPI2	((volatile SPIx_MemMap_t*)(SP2_BASE_ADDR))
#define SPI3	((volatile SPIx_MemMap_t*)(SP3_BASE_ADDR))
#define SPI4	((volatile SPIx_MemMap_t*)(SP4_BASE_ADDR))

/* Registers */
#define DFF			11
#define SSM			9
#define SSI			8
#define LSBFIRST	7
#define SPE			6
#define MSTR		2
#define CPOL		1
#define CPHA		0

#define TXE			1
#define RXNE		0

#endif /* SRC_MCAL_SPI_SPI_PRV_H_ */
