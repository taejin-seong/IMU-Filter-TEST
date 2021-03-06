/*
 * hw_def.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/*hw 폴더 밑에 만들어지는 모듈들이 공통으로 쓰는 하드웨어 관련 정의를 선언합니다.*/

#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"
#include "bsp.h"


/* TODO: HW 설정 - "컴파일 유무 선언" (2) */



/* Peripheral */
#define   _USE_HW_UART
#define   _USE_HW_I2C
#define   _USE_HW_TIM


/*    Hardware   */
#define   _USE_HW_IMU
#define   _USE_HW_LED
//#define   _USE_HW_MPU6050
//#define   _USE_HW_MAG


/* Filter define */
#define   _USE_HW_KALMAN
#define   _USE_HW_Mad_Mah


/* Parameter */
#define  HW_LED_MAX_CH			1
#define  HW_UART_MAX_CH			1





#endif /* SRC_HW_HW_DEF_H_ */
