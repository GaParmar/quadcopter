/*
 * Filename: IMU.h
 * 
 * Author: Gaurav Parmar
 *
 * Description: Handles all the operations involving the gyroscope and
 * the accelerometer.
 */

#include <wire.h>
#include "config.h"

/*
 * Function Name: setupGyro();
 * Function Prototype: void setupGyro();
 * Description: Initializes the I2C communication with the
 *              gyroscope
 * Parameters: none
 * Return: none
 */
void setupGyro()
{
  Wire.begin();//not sure if we need this

  Wire.beginTransmission(105);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  Wire.beginTransmission(105);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();

  Wire.beginTransmission(105);
  Wire.write(0x1A);
  Wire.write(0x03);
  Wire.endTransmission();
}

/*
 * Function name: setupAccel();
 * Function prototype: void setupAccel();
 * Description: Initializes the I2C communication with the
 *              accelerometer
 * Parameters: none
 * Return: none
 */
void setupAccel()
{
  //TODO
}

/*
 * Function name: getGyroOffsets();
 * Function prototype: void getGyroOffsets(int samples, double * gyro[]);
 * Description: Calculates the gyroscope offests
 * Parameters: int samples - the number of samples to be taken
 *             double * gyo[] - An array of double with calculated
 *                              gyroscope offsets
 * Return: none
 */
void getGyroOffsets(int samples, double * gyro[])
{
  float gr = {0,0,0};
  updateRawGyro(&gr);
  int i;
  for(i=0; i<samples; i++)
  {
    updateRawGyro(&gr);
    *(gyo) += gr[0];
    *(gyo+1) += gr[1];
    *(gyo+2) += gr[2];
  }

  *(gyo) /= samples;
  *(gyo+1) /= samples;
  *(gyo+2) /= samples;
}

/*
 * Function name: updateRawGyro();
 * Function prototype: void updateRawGyro(float * gr[]);
 * Description: Updates the array with the latest gyroscope
 *              readings.
 * Parameters: float * gr[] - pointer to float array
 * Return: none
 */
void updateRawGyro(float * gr[])
{
  Wire.beginTransmission(105);
  Wire.write(0x43);
  Wire.endTransmission();

  Wire.requestFrom(105, 6);
  while (Wire.available() < 6)
  {
    *(gr) = Wire.read()<<8|Wire.read();
    *(gr+1) = Wire.read()<<8|Wire.read();
    *(gr+2) = Wire.read()<<8|Wire.read();
  }

}

/* 
 * Function name: updateRawAccel();
 * Function prototype: void updateRawAccel(float * ac[]);
 * Description: Updates the array with the latest accelerometer
 *              readings.
 * Parameters: float * ac[] - pointer to float array
 * Return: none
 */
void updateRawAccel(float * ac[])
{
  //TODO
}
