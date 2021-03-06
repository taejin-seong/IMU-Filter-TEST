/*
 * ap.c
 *
 *  Created on: Mar 14, 2021
 *      Author: sungt
 */

#ifndef SRC_AP_AP_C_
#define SRC_AP_AP_C_


#include "ap.h"


MPU6050_t MPU6050;
uint32_t count = 0;

float q[4] = {1.0f, 0.0f, 0.0f, 0.0f};
float a12, a22, a31, a32, a33;



void apInit(void)
{
   uartOpen(_DEF_UART1, 115200);

}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM1)
	{

	     /* TODO: Select IMU Filter (1) */

	      //Process_IMU_Madgwick();
		Process_IMU_Mahony();

		q[0] = q0;
		q[1] = q1;
		q[2] = q2;
		q[3] = q3;


		a12 =   2.0f * (q[1] * q[2] + q[0] * q[3]);
		a22 =   q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3];
		a31 =   2.0f * (q[0] * q[1] + q[2] * q[3]);
		a32 =   2.0f * (q[1] * q[3] - q[0] * q[2]);
		a33 =   q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3];



		double sinp = a32;
		if (abs(sinp) >= 1)
		{
		  pitch = copysign(M_PI/2,sinp);
		}

		else
		{
		   pitch =  asin(sinp);
		  // pitch = -asinf(a32);
		   roll  = atan2f(a31, a33);
		   yaw   = atan2f(a12, a22);

		   pitch *= 180.0f / pi;
		   yaw = atan2f(sinf(yaw),cosf(yaw));
		   yaw   *= 180.0f / pi;

		   roll  *= 180.0f / pi;
		}

	  }

}



void apBoardTest(void)
{
   while(1)
   {
       /* Board Test */
       LedToggle(_DEF_LED1);
       delay_ms(100);

   }
}



void apKalman(void)
{

#ifdef _USE_HW_MPU6050

  while (init_mpu6050(&hi2c1) == 1);

#endif /* _USE_HW_MPU6050 */

  while(1)
  {

    Process_IMU_Kalman(&MPU6050);

    delay_ms(10);

    uartPrintf(_DEF_UART1, "Roll:%2.2f, Ptich:%2.2f \n\r",MPU6050.KalmanAngleX, MPU6050.KalmanAngleY);

  }

}



void apMadgwick(void)
{


   if (Check_Connection(0x71) == 1)
   {
 	Calibration_IMU();
 	delay_ms(100);

   }
   else
   {
        count += 1;
        uartPrintf(_DEF_UART1, "check connection...%ds\n\r",count);
   }

#ifdef _USE_HW_MAG

   Calib_Magnetometer();

#endif /* _USE_HW_MAG */

   HAL_TIM_Base_Start_IT(&htim3);
   HAL_TIM_Base_Start_IT(&htim1);

  while(1)
  {

	  uartPrintf(_DEF_UART1, "Roll:%2.2f, Ptich:%2.2f \n\r",roll,pitch);
   	  delay_ms(10);

  }


}


void apMahony(void)
{

    if (Check_Connection(0x71) == 1)
    {
  	Calibration_IMU();
  	delay_ms(100);

    }
    else
    {
         count += 1;
         uartPrintf(_DEF_UART1, "check connection...%ds\n\r",count);
    }

#ifdef _USE_HW_MAG
    Calib_Magnetometer();
#endif /* _USE_HW_MAG */

    HAL_TIM_Base_Start_IT(&htim3);
    HAL_TIM_Base_Start_IT(&htim1);

   while(1)
   {


 	  uartPrintf(_DEF_UART1, "Roll:%2.2f, Ptich:%2.2f \n\r",roll,pitch);
    	  delay_ms(10);

   }
}




void apComplementary(void)
{
  if (Check_Connection(0x71) == 1)
  {
	Calibration_IMU();
	delay_ms(100);

  }
  else
  {
       count += 1;
       uartPrintf(_DEF_UART1, "check connection...%ds\n\r",count);
  }

  while(1)
  {
    Process_IMU_Complementary();

    delay_ms(10);

    uartPrintf(_DEF_UART1, "Roll:%2.2f, Ptich:%2.2f \n\r",roll, pitch);

  }
}






#endif /* SRC_AP_AP_C_ */
