/*
 * bsp.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

/* 가장 공통으로 쓰일 기본적인 함수를  작성합니다. */


#ifndef SRC_BSP_BSP_H_
#define SRC_BSP_BSP_H_



#include "def.h"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_conf.h"



void bspInit(void);

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

uint32_t millis(void);


void Error_Handler(void);


#endif /* SRC_BSP_BSP_H_ */
