/*
 * Filename: IMU.h
 * 
 * Author: Gaurav Parmar
 *
 * Description: Declares the methods defined in the IMU.c file
 */

/*
 * Function Name: setupGyro();
 * Function Prototype: void setupGyro();
 * Description: Initializes the I2C communication with the
 *              gyroscope
 * Parameters: none
 * Return: none
 */
void setupGyro();

/*
 * Function name: setupAccel();
 * Function prototype: void setupAccel();
 * Description: Initializes the I2C communication with the
 *              accelerometer
 * Parameters: none
 * Return: none
 */
void setupAccel();

/*
 * Function name: getGyroOffsets();
 * Function prototype: void getGyroOffsets(int samples, double * gyro[]);
 * Description: Calculates the gyroscope offests
 * Parameters: int samples - the number of samples to be taken
 *             double * gyo[] - An array of double with calculated
 *                              gyroscope offsets
 * Return: none
 */
void getGyroOffsets(int samples, double * gyro[]);

/*
 * Function name: updateRawGyro();
 * Function prototype: void updateRawGyro(float * gr[]);
 * Description: Updates the array with the latest gyroscope
 *              readings.
 * Parameters: float * gr[] - pointer to float array
 * Return: none
 */
void updateRawGyro(float * gr[]);

/* 
 * Function name: updateRawAccel();
 * Function prototype: void updateRawAccel(float * ac[]);
 * Description: Updates the array with the latest accelerometer
 *              readings.
 * Parameters: float * ac[] - pointer to float array
 * Return: none
 */
void updateRawAccel(float * ac[]);
