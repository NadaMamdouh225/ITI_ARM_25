/*
 * LEDMATRIX_int.h
 *
 *  Created on: Aug 21, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.1
 */

#ifndef SRC_HAL_LEDMATRIX_INT_H_
#define SRC_HAL_LEDMATRIX_INT_H_


void HLEDMATRIX_vInit(GPIOx_PinConfig_t *A_xRows, u8 A_u8RowsNo, GPIOx_PinConfig_t *A_xCols, u8 A_u8ColNo);
void HLEDMATRIX_DisplayFrame(u8 A_u8Frame[], u32 A_u32FrameDelay);


#endif /* SRC_HAL_LEDMATRIX_INT_H_ */
