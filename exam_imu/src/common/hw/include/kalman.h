/*
 * kalman.h
 *
 *  Created on: Jun 13, 2021
 *      Author: sungt
 */

#ifndef SRC_COMMON_CORE_KALMAN_H_
#define SRC_COMMON_CORE_KALMAN_H_


#include "hw_def.h"

#ifdef _USE_HW_KALMAN




typedef struct{

  double Q_angle;
  double Q_bias;
  double R_measure;
  double angle;
  double bias;
  double P[2][2];

}Kalman_t;


double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt);





#endif /* _USE_HW_KALMAN */
#endif /* SRC_COMMON_CORE_KALMAN_H_ */
