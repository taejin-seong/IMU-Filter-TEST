/*
 * kalman.c
 *
 *  Created on: Jun 13, 2021
 *      Author: sungt
 */

#include "kalman.h"



double Kalman_getAngle(Kalman_t *Kalman, double newAngle, double newRate, double dt)
{
  //step 1
  double rate = newRate - Kalman->bias;
  Kalman->angle += dt * rate;

  //step 2
  Kalman->P[0][0] += dt * (dt * Kalman->P[1][1] - Kalman->P[0][1] - Kalman->P[1][0] + Kalman->Q_angle);
  Kalman->P[0][1] -= dt * Kalman->P[1][1];
  Kalman->P[1][0] -= dt * Kalman->P[1][1];
  Kalman->P[1][1] += Kalman->Q_bias * dt;

  //step 3
  double y = newAngle - Kalman->angle;

  //step 4
  double S = Kalman->P[0][0] + Kalman->R_measure;

  //step 5
  double K[2];
  K[0] = Kalman->P[0][0] / S;
  K[1] = Kalman->P[1][0] / S;

  //step 6
  Kalman->angle += K[0] * y;
  Kalman->bias += K[1] * y;

  //step 7
  double P00_temp = Kalman->P[0][0];
  double P01_temp = Kalman->P[0][1];

  Kalman->P[0][0] -= K[0] * P00_temp;
  Kalman->P[0][1] -= K[0] * P01_temp;
  Kalman->P[1][0] -= K[1] * P00_temp;
  Kalman->P[1][1] -= K[1] * P01_temp;

  return Kalman->angle;

}
