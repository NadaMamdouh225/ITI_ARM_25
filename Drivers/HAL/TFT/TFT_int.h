/*
 * TFT_int.h
 *
 *  Created on: Sep 3, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */

#ifndef SRC_HAL_TFT_TFT_INT_H_
#define SRC_HAL_TFT_TFT_INT_H_

void HTFT_vInit(void);
void HTFT_vShowImg(const u16 A_u16ImgArr[],u16 A_u16ImgSize );

void HTFT_vSetXPos(u16 A_u16xStart, u16 A_u16xEnd);
void HTFT_vSetYPos(u16 A_u16yStart, u16 A_u16yEnd);
void HTFT_vFillBackgroundColor(u16 A_u16Color);
void HTFT_vFillRectangle(u16 A_u16Color);


#endif /* SRC_HAL_TFT_TFT_INT_H_ */
