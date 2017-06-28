# quadcopter
3Dprinted bluetooth controlled quadcopter

## Sensors used:
  * mpu 6050:
    * 6 dof Gyroscope + Accelerometer 
    * [website](https://www.sparkfun.com/products/11028)
    *  [datasheet](http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
    *  I2C address: (AD0=0) - 1101000, (AD0=1) - 1101001

## Bluetooth Communication Protocol:
	* Each transmission is a 6 character array
		* First character Indicates the type of data being transmitted
			* 'r' - indicates that the next 4 characters represent roll value
			* 'p' - indicates that the next 4 characters represent pitch value
			* 'y' - indicates that the next 4 characters represent yaw value
			* 't' - indicates that the next 4 characters represent thrust value
		* Character 2, 3, 4, 5: The numerical value associated with the type
		* SPECIAL CASES:
			* If any error occurs, the array is {'E', 'R', 'R', 'O', 'R'}