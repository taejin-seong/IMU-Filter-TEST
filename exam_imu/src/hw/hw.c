/*
 * hw.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "hw.h"


void hwInit(void)
{
	bspInit();

/*  TODO: HW 설정 - "하드웨어 초기화" (3) */

	uartInit();
	LedInit();

	MX_I2C1_Init();
	MX_TIM1_Init();
	MX_TIM3_Init();

	Init_IMU();

#ifdef _USE_HW_MPU6050

	Init_MPU6050(&hi2c1);

#endif /* _USE_HW_MPU6050  */


#ifdef _USE_HW_MAG

	Init_Magnetometer();

#endif /* _USE_HW_MAG*/



}
