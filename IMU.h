/*
 * Description: Initializes the I2C communication with the
 *              gyroscope
 * Parameters: none
 * Return: none
 */
void setupGyro();

/*
 * Description: Initializes the I2C communication with the
 *              accelerometer
 * Parameters: none
 * Return: none
 */
void setupAccel();

/*
 * Description: Calculates the gyroscope offests
 * Parameters: int samples - the number of samples to be taken
 * Return: An array of double with calculated gyroscope offsets
 *        for each axis.
 */
double[] getGyroOffsets(int samples);

/*
 * Description: Updates the array with the latest gyroscope
 *              readings. 
 * Parameters: float * gr[] - pointer to float array
 * Return: none
 */
void updateRawGyro(float * gr[]);

/* Description: Updates the array with the latest accelerometer
 *              readings. 
 * Parameters: float * ac[] - pointer to float array
 * Return: none
 */
void updateRawGyro(float * ac[]);
