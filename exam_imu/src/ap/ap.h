/*
 * ap.h
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */
/* 실질적으로  Main 함수를 담당하는 부분입니다.*/

#ifndef SRC_AP_AP_H_
#define SRC_AP_AP_H_


#include "hw.h"

#define pi 3.141592653589793238462




void apInit(void);
void apBoardTest(void);


void apKalman(void);
void apComplementary(void);
void apMahony(void);
void apMadgwick(void);







#endif /* SRC_AP_AP_H_ */
