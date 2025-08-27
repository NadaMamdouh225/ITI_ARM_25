/*
 * DAC_int.h
 *
 *  Created on: Aug 27, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.0
 */

#ifndef SRC_HAL_DAC_DAC_INT_H_
#define SRC_HAL_DAC_DAC_INT_H_

void HDAC_vInit(GPIOx_PinConfig_t *A_xPins, u8 A_u8PinsNo);
void HDAC_vSendSample(const u8* A_u8Ptr, u32 A_u32Index);


#endif /* SRC_HAL_DAC_DAC_INT_H_ */
