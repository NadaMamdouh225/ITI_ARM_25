/*
 * OS_int.h
 *
 *  Created on: Aug 24, 2025
 *      Author: Nada Mamdouh
 *      Version: 0.1
 */

#ifndef SRC_OS_OS_INT_H_
#define SRC_OS_OS_INT_H_

//typedef u8 ErrorState
void OS_vStart(void);

u8 OS_u8CreateTask(void (*A_xFptr)(void),u32 A_u32Periodicity,u8 A_u8Priority, u32 A_u32FirstDelay);
u8 OS_u8SuspendTask(u8 A_u8Priority);
u8 OS_u8ResumeTask(u8 A_u8Priority);
u8 OS_u8DeleteTask(u8 A_u8Priority);


/* Error States */
/*
 * OUT_OF_RANGE_ERROR
 * RESERVED_PRIORITY_ERROR
 * NO_TASK_ERROR
 */



#endif /* SRC_OS_OS_INT_H_ */
