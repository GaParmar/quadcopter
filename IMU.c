/*
 * Description: Initializes the I2C communication with the
 *              gyroscope
 * Parameters: none
 * Return: none
 */
void setupGyro()
{
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
 * Description: Initializes the I2C communication with the
 *              accelerometer
 * Parameters: none
 * Return: none
 */
void setupAccel()
{

}

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
void updateRawAccel(float * ac[]);
