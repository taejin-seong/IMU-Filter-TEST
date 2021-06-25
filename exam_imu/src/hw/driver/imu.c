/*
 * mpu9250.c
 *
 *  Created on: 2021. 6. 14.
 *      Author: sungt
 */


#include "imu.h"

#include "i2c.h"
#include "kalman.h"
#include "madgwick_mahony.h"


I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart3;
TIM_HandleTypeDef htim3;


//TODO 1. 칼만 필터 적용 코드 - (2)

uint32_t timer;

Kalman_t KalmanX = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f
};

Kalman_t KalmanY = {
        .Q_angle = 0.001f,
        .Q_bias = 0.003f,
        .R_measure = 0.03f,
};



int Check_Connection(uint8_t return_true_val)
{
	// Check WHO_AM_I
	uint8_t who_i_am = (uint8_t)WHO_AM_I_MPU9250;
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;


	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&who_i_am,1,1000)!= HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1,mpu_address,&temp,1,1000) != HAL_OK);
	if (temp == return_true_val)
	  return 1;
	else
	  return 0;

}

void IMU_Set_Clock_Source(MPU9250_clock_source_t clock_source)
{
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;
	uint8_t d[2];

	d[0] = PWR_MGMT_1;
	d[1] = clock_source;
	while(HAL_I2C_Master_Transmit(&hi2c1,mpu_address,(uint8_t *)d,2,100)!= HAL_OK);
}


void Set_Accel_Range(MPU9250_ACCEL_FULL_SCALE accel_FS)
{
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;
	uint8_t d[2];
	uint8_t reg1 = ACCEL_CONFIG;
	//uint8_t reg2 = ACCEL_CONFIG2;

	uint8_t c;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg1,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address,&c, 1, 1000) != HAL_OK);
//	c[0] &=  ~0x18; // Clear AFS bits [4:3]
//	c[0] |= accel_FS; // Set full scale range for the gyro

	d[0] = ACCEL_CONFIG;
	d[1] = (c & 0xE7) | (uint8_t)accel_FS ;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);


//	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg2,1,1000) != HAL_OK);
//	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address,c, 1, 1000) != HAL_OK);
//	c[0] &= ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
//	c[0] |=  0x03; // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
	d[0] = ACCEL_CONFIG2;
	d[1] = 0x05;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,1000)!=HAL_OK);
}

void Set_Gyro_Range(MPU9250_GYRO_FULL_SCALE gyro_FS)
{

//	uint8_t reg = GYRO_CONFIG;
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;
	uint8_t d[2];
//	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg,1,1000) != HAL_OK);
//	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address,c, 1, 1000) != HAL_OK);
//	c[0] &=  ~0x02; // Clear Fchoice bits [1:0]
//	c[0] &=  ~0x18; // Clear AFS bits [4:3]
//	c[0] |= gyro_FS;
	d[0] = GYRO_CONFIG;
	d[1] = gyro_FS;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);

}


void Reset_MPU()
{
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;
	uint8_t d[2];
	d[0] = PWR_MGMT_1;
	d[1] = 0x00;
	while(HAL_I2C_Master_Transmit(&hi2c1,mpu_address,(uint8_t *)d,2,100)!= HAL_OK);
	HAL_Delay(1000);
}


void Init_IMU()
{

	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;
	uint8_t d[2];
	/* Check if device is connected */
	while(HAL_I2C_IsDeviceReady(&hi2c1,mpu_address,2,3) != HAL_OK);

	/* Wakeup MPU6050 */
	/* Try to transmit via I2C */
	d[0] = PWR_MGMT_1;
	d[1] = 0x00;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);
	HAL_Delay(100);

	// Set clock source to be PLL with x-axis gyroscope reference, bits 2:0 = 001
	IMU_Set_Clock_Source(MPU9250_CLOCK_PLL_XGYRO);

	//CONGFIG
	d[0] = CONFIG;
	d[1] = 0x09;//0x05//0x03
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);

	/* Set data sample rate */
	d[0] = SMPLRT_DIV;   // sample rate = SAMPLE_RATE/(1 + 7) = 1khz
	d[1] = SAMPLE_RATE_1khz;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);
	// config accelerometer
	Set_Accel_Range(MPU9250_ACCEL_FS_2);
	// config gyro
	Set_Gyro_Range(MPU9250_GYRO_FS_250);
	d[0] = USER_CTRL;
	d[1] = 0x00;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,100) != HAL_OK);
	d[0] = INT_ENABLE;
	d[1] = 0x01;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,1000)!=HAL_OK);
	d[0] = INT_PIN_CFG;
	d[1] = 0x22;  // turn on AK8963
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,(uint8_t *)d,2,1000)!=HAL_OK);

}


#ifdef _USE_HW_MPU6050

uint8_t Init_MPU6050(I2C_HandleTypeDef *I2Cx)
{
    uint8_t check;
    uint8_t Data;

    // check device ID WHO_AM_I

    HAL_I2C_Mem_Read(I2Cx, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, i2c_timeout);

    if (check == 104) // 0x68 will be returned by the sensor if everything goes well
    {
        // power management register 0X6B we should write all 0's to wake the sensor up
        Data = 0;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, i2c_timeout);

        // Set DATA RATE of 1KHz by writing SMPLRT_DIV register
        Data = 0x07;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, i2c_timeout);

        // Set accelerometer configuration in ACCEL_CONFIG Register
        // XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, i2c_timeout);

        // Set Gyroscopic configuration in GYRO_CONFIG Register
        // XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
        Data = 0x00;
        HAL_I2C_Mem_Write(I2Cx, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, i2c_timeout);
        return 0;
    }
    return 1;
}

#endif /*_USE_HW_MPU6050 */


#ifdef _USE_HW_MAG

void Get_Magnetometer()
{
	uint8_t raw_data[7];
	uint8_t reg_ST1 = ST1;
	uint8_t mag_address = MAG_ADDRESS_DEFAULT;
	uint8_t reg = XOUT_L;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,&reg_ST1,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1,(uint16_t)mag_address,raw_data,1,1000) != HAL_OK);
	if (raw_data[0] & 0x01)
	{
		while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,&reg,1,1000) != HAL_OK);
		while(HAL_I2C_Master_Receive(&hi2c1,(uint16_t)mag_address,raw_data,7,1000) != HAL_OK);
		// Read the six raw data and ST2 registers sequentially into data arra
		if(!(raw_data[6] & 0x08))// Check if magnetic sensor overflow set, if not then report data
		{
			Mag_x = (int16_t)((raw_data[1]<<8) | raw_data[0] );
			Mag_y = (int16_t)((raw_data[3]<<8) | raw_data[2] );
			Mag_z = (int16_t)((raw_data[5]<<8) | raw_data[4] );
		}


		Mag_X_calib = (float)Mag_x * asax * mag_sensitivity - mag_offset[0];
		Mag_Y_calib = (float)Mag_y * asay * mag_sensitivity - mag_offset[1];
		Mag_Z_calib = (float)Mag_z * asaz * mag_sensitivity - mag_offset[2];

		Mag_X_calib *=scale_x;
		Mag_Y_calib *=scale_y;
		Mag_Z_calib *=scale_z;

	}
}


#endif /* _USE_HW_MAG */

#ifdef _USE_HW_MAG


void Init_Magnetometer()
{
	uint8_t mag_address = MAG_ADDRESS_DEFAULT;
	uint8_t d[2];

	while(HAL_I2C_IsDeviceReady(&hi2c1,mag_address,3,200)!=HAL_OK);
	d[0] = CNTL;
	d[1] = 0x00;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,(uint8_t *)d,2,1000) != HAL_OK);
	HAL_Delay(100);
	d[0] = CNTL;
	d[1] = 0x1F;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,(uint8_t *)d,2,1000) != HAL_OK);
	HAL_Delay(100);
	uint8_t raw_data[3];
	uint8_t Sensitivity = ASAX ;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,&Sensitivity,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1,mag_address,(uint8_t*)raw_data,3,1000) != HAL_OK);

	asax = (float)(raw_data[0] - 128)/256.0f +1.0f;  // Return x-axis sensitivity adjustment values, etc.
	asay = (float)(raw_data[1] - 128)/256.0f +1.0f;
	asaz = (float)(raw_data[2] - 128)/256.0f +1.0f;
	//Please note that we has to change the chip to power-down mode first then switch it to another mode
	 //reset the Magnetometer to power down mode

	d[0] = CNTL;
	d[1] = 0x00;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,(uint8_t *)d,2,1000) != HAL_OK);
	HAL_Delay(100);
	MPU9250_MAG_FULL_SCALE mag_fs = MFS_16BITS;
	d[0] = CNTL;
	d[1] = (mag_fs<<4)|0x06;
	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,(uint8_t *)d,2,1000) != HAL_OK);
	HAL_Delay(100);    //wait for the mode changes
	/*
	 *
	 * REG : CNTL
	 *  *MODE[3:0]: Operation mode setting
	"0000": Power-down mode
	"0001": Single measurement mode
	"0010": Continuous measurement mode 1
	"0110": Continuous measurement mode 2
	"0100": External trigger measurement mode
	"1000": Self-test mode
	"1111": Fuse ROM access mode
	Other code settings are prohibited
	BIT: Output bit setting
	"0": 14-bit output
	"1": 16-bit output*/
}
#endif /* _USE_HW_MAG */



//TODO 1. 칼만 필터 적용 코드 - (3)
void Process_IMU_Kalman(MPU6050_t *DataStruct) // 최근 수정일: 21/06/14/월
{
        //read raw data
        uint8_t Rec_Data[14];


       HAL_I2C_Mem_Read(&hi2c1, MPU9250_ADDRESS_DEFAULT, ACCEL_XOUT_H, 1, Rec_Data, 14, 100);

       DataStruct->Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
       DataStruct->Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
       DataStruct->Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

       DataStruct->Gyro_X_RAW = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
       DataStruct->Gyro_Y_RAW = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
       DataStruct->Gyro_Z_RAW = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);

       DataStruct->Ax = DataStruct->Accel_X_RAW / 16384.0;
       DataStruct->Ay = DataStruct->Accel_Y_RAW / 16384.0;
       DataStruct->Az = DataStruct->Accel_Z_RAW / 14418.0;

       DataStruct->Gx = DataStruct->Gyro_X_RAW / 131.0;
       DataStruct->Gy = DataStruct->Gyro_Y_RAW / 131.0;
       DataStruct->Gz = DataStruct->Gyro_Z_RAW / 131.0;


       // Kalman angle solve
       double dt = (double)(HAL_GetTick() - timer) / 1000;
       timer = HAL_GetTick();
       double roll;
       double roll_sqrt = sqrt(
       DataStruct->Accel_X_RAW * DataStruct->Accel_X_RAW + DataStruct->Accel_Z_RAW * DataStruct->Accel_Z_RAW);
       if (roll_sqrt != 0.0)
       {
              roll = atan(DataStruct->Accel_Y_RAW / roll_sqrt) * RAD2DEG;
       }
       else
       {
              roll = 0.0;
       }
       double pitch = atan2(-DataStruct->Accel_X_RAW, DataStruct->Accel_Z_RAW) * RAD2DEG;
       if ((pitch < -90 && DataStruct->KalmanAngleY > 90) || (pitch > 90 && DataStruct->KalmanAngleY < -90))
       {
              KalmanY.angle = pitch;
              DataStruct->KalmanAngleY = pitch;
       }
       else
       {
              DataStruct->KalmanAngleY = Kalman_getAngle(&KalmanY, pitch, DataStruct->Gy, dt);
       }
       if (fabs(DataStruct->KalmanAngleY) > 90)
           DataStruct->Gx = -DataStruct->Gx;
       DataStruct->KalmanAngleX = Kalman_getAngle(&KalmanX, roll, DataStruct->Gx, dt);


}


//TODO 2. 상보 필터 적용 코드
void Process_IMU_Complementary()
{

	//read raw data
	uint8_t data[14];
	uint8_t reg = ACCEL_XOUT_H;
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;


	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address, data, 14, 1000) != HAL_OK);

	/*-------- Accel ---------*/
	Accel_x = (int16_t)((int16_t)( data[0] << 8 ) | data[1]);
	Accel_y = (int16_t)((int16_t)( data[2] << 8 ) | data[3]);
	Accel_z = (int16_t)((int16_t)( data[4] << 8 ) | data[5]);

	/*-------- Gyrometer --------*/
	Gyro_x = (int16_t)((int16_t)( data[8] << 8  ) | data[9]);
	Gyro_y = (int16_t)((int16_t)( data[10] << 8 ) | data[11]);
	Gyro_z = (int16_t)((int16_t)( data[12] << 8 ) | data[13]);


	Accel_X = 10*(float)((int32_t)Accel_x - Accel_x_bias)/(float)accel_sensitivity;
	Accel_Y = 10*(float)((int32_t)Accel_y - Accel_y_bias)/(float)accel_sensitivity;
	Accel_Z =  10*(float)((int32_t)Accel_z - Accel_z_bias)/(float)accel_sensitivity ;

	Gyro_X =  (float)(((int32_t)Gyro_x - Gyro_x_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Y =  (float)(((int32_t)Gyro_y - Gyro_y_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Z =  (float)(((int32_t)Gyro_z - Gyro_z_bias)/(float)gyro_sensitivity)*M_PI/180.0f;


	double dt = (double)(HAL_GetTick() - timer) / 1000;
	timer = HAL_GetTick();

	float accel_roll  = atan((double)Accel_Y / sqrt(pow((double)Accel_X, 2) + pow((double)Accel_Z, 2)))*RAD2DEG;
	float accel_pitch = atan((double)Accel_X / sqrt(pow((double)Accel_Y, 2) + pow((double)Accel_Z, 2)))*RAD2DEG;
	float accel_yaw   = atan(sqrt(pow((double)Accel_X, 2) + pow((double)Accel_Y, 2)) /(double) Accel_Z)*RAD2DEG;

	roll = alpha*(roll + dt*Gyro_X) + (1-alpha)*accel_roll;
	pitch = alpha*(pitch + dt*Gyro_Y) + (1-alpha)*accel_pitch;
	yaw = alpha * yaw + (1-alpha) * accel_yaw;


}



//TODO 3. 마호니 필터 적용 코드
void Process_IMU_Mahony() // 최근 수정일: 21/06/14/월
{

	//read raw data
	uint8_t data[14];
	uint8_t reg = ACCEL_XOUT_H;
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;


	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address, data, 14, 1000) != HAL_OK);

	/*-------- Accel ---------*/
	Accel_x = (int16_t)((int16_t)( data[0] << 8 ) | data[1]);
	Accel_y = (int16_t)((int16_t)( data[2] << 8 ) | data[3]);
	Accel_z = (int16_t)((int16_t)( data[4] << 8 ) | data[5]);

	/*-------- Gyrometer --------*/
	Gyro_x = (int16_t)((int16_t)( data[8] << 8  ) | data[9]);
	Gyro_y = (int16_t)((int16_t)( data[10] << 8 ) | data[11]);
	Gyro_z = (int16_t)((int16_t)( data[12] << 8 ) | data[13]);


	Accel_X = 10*(float)((int32_t)Accel_x - Accel_x_bias)/(float)accel_sensitivity;
	Accel_Y = 10*(float)((int32_t)Accel_y - Accel_y_bias)/(float)accel_sensitivity;
	Accel_Z =  10*(float)((int32_t)Accel_z - Accel_z_bias)/(float)accel_sensitivity ;

	Gyro_X =  (float)(((int32_t)Gyro_x - Gyro_x_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Y =  (float)(((int32_t)Gyro_y - Gyro_y_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Z =  (float)(((int32_t)Gyro_z - Gyro_z_bias)/(float)gyro_sensitivity)*M_PI/180.0f;


#ifdef _USE_HW_MAG
	// Get data of Magnetometer
	 Get_magnetometer();
#endif /* _USE_HW_MAG */

	 MahonyAHRSupdateIMU(Gyro_X,Gyro_Y,Gyro_Z,Accel_X,Accel_Y,Accel_Z);



}


//TODO 4. 매드윅 필터 적용 코드
void Process_IMU_Madgwick() // 최근 수정일: 21/06/14/월
{
	//read raw data
	uint8_t data[14];
	uint8_t reg = ACCEL_XOUT_H;
	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;


	while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg,1,1000) != HAL_OK);
	while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address, data, 14, 1000) != HAL_OK);

	/*-------- Accel ---------*/
	Accel_x = (int16_t)((int16_t)( data[0] << 8 ) | data[1]);
	Accel_y = (int16_t)((int16_t)( data[2] << 8 ) | data[3]);
	Accel_z = (int16_t)((int16_t)( data[4] << 8 ) | data[5]);

	/*-------- Gyrometer --------*/
	Gyro_x = (int16_t)((int16_t)( data[8] << 8  ) | data[9]);
	Gyro_y = (int16_t)((int16_t)( data[10] << 8 ) | data[11]);
	Gyro_z = (int16_t)((int16_t)( data[12] << 8 ) | data[13]);


	Accel_X = 10*(float)((int32_t)Accel_x - Accel_x_bias)/(float)accel_sensitivity;
	Accel_Y = 10*(float)((int32_t)Accel_y - Accel_y_bias)/(float)accel_sensitivity;
	Accel_Z =  10*(float)((int32_t)Accel_z - Accel_z_bias)/(float)accel_sensitivity ;

	Gyro_X =  (float)(((int32_t)Gyro_x - Gyro_x_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Y =  (float)(((int32_t)Gyro_y - Gyro_y_bias)/(float)gyro_sensitivity)*M_PI/180.0f;
	Gyro_Z =  (float)(((int32_t)Gyro_z - Gyro_z_bias)/(float)gyro_sensitivity)*M_PI/180.0f;

#ifdef _USE_HW_MAG
	// Get data of Magnetometer
	 Get_magnetometer();
#endif /* _USE_HW_MAG */


	MadgwickAHRSupdateIMU(Gyro_X,Gyro_Y,Gyro_Z,Accel_X,Accel_Y,Accel_Z);


}




void Calibration_IMU()
{
	uint8_t data[14];
	uint8_t reg = ACCEL_XOUT_H;

	uint8_t mpu_address = MPU9250_ADDRESS_DEFAULT;

	for(int i=0; i < 100; i++){
		while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mpu_address,&reg,1,1000) != HAL_OK);
		while(HAL_I2C_Master_Receive(&hi2c1, (uint16_t)mpu_address, data, 14, 1000) != HAL_OK);

				/*-------- Accel ---------*/
		Accel_x = (int16_t)( (int16_t)( data[0] << 8 ) | data[1]);
		Accel_y = (int16_t)( (int16_t)( data[2] << 8 ) | data[3]);
		Accel_z = (int16_t)( (int16_t)( data[4] << 8 ) | data[5]);

				/*-------- Gyrometer --------*/
		Gyro_x = (int16_t)( (int16_t)( data[8]  << 8 ) | data[9]);
		Gyro_y = (int16_t)( (int16_t)( data[10] << 8 ) | data[11]);
		Gyro_z = (int16_t)( (int16_t)( data[12] << 8 ) | data[13]);

		Accel_x_bias += (int32_t)Accel_x;
		Accel_y_bias += (int32_t)Accel_y;
		Accel_z_bias += (int32_t)Accel_z;

		Gyro_x_bias += (int32_t)Gyro_x;
		Gyro_y_bias += (int32_t)Gyro_y;
		Gyro_z_bias += (int32_t)Gyro_z;
	}
	Accel_x_bias /= 100;
	Accel_y_bias /= 100;
	Accel_z_bias /= 100;

	Gyro_x_bias /= 100;
	Gyro_y_bias /= 100;
	Gyro_z_bias /= 100;

	if(Accel_z_bias > 0) //// Remove gravity from the z-axis accelerometer bias calculation
	{
		Accel_z_bias -= (int32_t)accel_sensitivity;
	}
	else
	{
		Accel_z_bias += (int32_t)accel_sensitivity;
	}
}







#ifdef _USE_HW_MAG

void Calib_Magnetometer()
{
	//int16_t mag_max[3] = {-32767, -32767, -32767}, mag_min[3] = {32767, 32767, 32767};

	//int16_t mag_max[3] = {344.0,392.0,51.0},mag_min[3] = {-115.0,24.0,-323.0};
	int16_t mag_max[3] = { 332.0,377.0, 61.0},mag_min[3] = {-21.0,25.0,-304.0};
	mag_offset[3] = 0;
	/*uint8_t raw_data[7];
	uint8_t reg_ST1 = ST1;
	uint8_t mag_address = MAG_ADDRESS_DEFAULT;
	uint8_t reg = XOUT_L;
	uint16_t i = 0;
	for (i = 0; i < 1500;i++)
	{
		while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,&reg_ST1,1,1000) != HAL_OK);
		while(HAL_I2C_Master_Receive(&hi2c1,(uint16_t)mag_address,raw_data,1,1000) != HAL_OK);
		if (raw_data[0] & 0x01)
		{
			while(HAL_I2C_Master_Transmit(&hi2c1,(uint16_t)mag_address,&reg,1,1000) != HAL_OK);
			while(HAL_I2C_Master_Receive(&hi2c1,(uint16_t)mag_address,raw_data,7,1000) != HAL_OK);
			// Read the six raw data and ST2 registers sequentially into data arra
			if(!(raw_data[6] & 0x08))// Check if magnetic sensor overflow set, if not then report data
			{
				Mag_x = (int16_t)((int16_t)(raw_data[1]<<8) | raw_data[0] );
				Mag_y = (int16_t)((int16_t)(raw_data[3]<<8) | raw_data[2] );
				Mag_z = (int16_t)((int16_t)(raw_data[5]<<8) | raw_data[4] );
			}
		}
	int16_t mag_temp[3] = {Mag_x,Mag_y,Mag_z};
	for (int j = 0;j < 3;j++)
	{
		if (mag_temp[j] > mag_max[j])  mag_max[j] = mag_temp[j];
		if (mag_temp[j] < mag_min[j])  mag_min[j] = mag_temp[j];
	}
		HAL_Delay(12);
	}*/
	// Get hard iron correction
	mag_bias[0] = (mag_max[0] + mag_min[0])/2;
	mag_bias[1] = (mag_max[1] + mag_min[1])/2;
	mag_bias[2] = (mag_max[2] + mag_min[2])/2;

	mag_offset[0] = (float)(mag_bias[0]) * mag_sensitivity * asax;
	mag_offset[1] = (float)(mag_bias[1]) * mag_sensitivity * asay;
	mag_offset[2] = (float)(mag_bias[2]) * mag_sensitivity * asaz;
	// Get soft iron correction estimate
	mag_scale[0] = (mag_max[0] - mag_min[0])/2;
	mag_scale[1] = (mag_max[1] - mag_min[1])/2;
	mag_scale[2] = (mag_max[2] - mag_min[2])/2;

	scale_x = 0,scale_y = 0,scale_z = 0;
	float avg_rad = mag_scale[0] + mag_scale[1] + mag_scale[2];
	avg_rad /= 3.0;

	scale_x = avg_rad/(float)mag_scale[0];    //1.14
	scale_y = avg_rad/(float)mag_scale[1];  // 1.00
	scale_z = avg_rad/(float)mag_scale[2]; // 0.89
}

#endif /* _USE_HW_MAG */


