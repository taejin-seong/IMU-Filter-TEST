/*
 * main.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */


#include "main.h"



int main(void)
{
	hwInit();
	apInit();

//	apBoardTest();



/* TODO: Select IMU Filter (2) */

//	apKalman();
//	apComplementary();
	apMahony();
//	apMadgwick();


	return 0;
}
