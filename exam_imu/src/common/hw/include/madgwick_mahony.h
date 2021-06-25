/*
 * madgwick.h
 *
 *  Created on: Jun 13, 2021
 *      Author: sungt
 */

#ifndef SRC_COMMON_CORE_MADGWICK_H_
#define SRC_COMMON_CORE_MADGWICK_H_

#include "hw_def.h"

#ifdef _USE_HW_Mad_Mah


// Variable declaration

//extern volatile float beta;			// algorithm gain

extern volatile float twoKp;			// 2 * proportional gain (Kp)
extern volatile float twoKi;			// 2 * integral gain (Ki)
extern volatile float q0, q1, q2, q3;		// quaternion of sensor frame relative to auxiliary frame
float q[4];

//---------------------------------------------------------------------------------------------------
// Function declarations

void MahonyAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MahonyAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
	// vector to hold integral error for Mahony method
//---------------------------------------------------------------------------------------------------
// Function declarations

void MadgwickAHRSupdate(float gx, float gy, float gz, float ax, float ay, float az, float mx, float my, float mz);
void MadgwickAHRSupdateIMU(float gx, float gy, float gz, float ax, float ay, float az);
void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
//---------------------------------------------------------------------------------------------------
// Function declarations

float invSqrt(float x);


#endif /* USE_HW_Mad_Mah */
#endif /* SRC_COMMON_CORE_MADGWICK_H_ */
