# quadcopter
3Dprinted bluetooth controlled quadcopter

## Sensors used:
  * mpu 6050:
    * 6 dof Gyroscope + Accelerometer 
    * [website](https://www.sparkfun.com/products/11028)
    *  [datasheet](http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
    *  I2C address: (AD0=0) - 1101000, (AD0=1) - 1101001

## Bluetooth Communication Protocol
	* Each transmission is 6 character array. 
		* First character: Indicates the type of data being transmitted
		* Character 2, 3, 4, 5: The numerical value associated with the type
		* SPECIAL CASE: if any error happens, the array is {'E', 'R', 'R', 'O', 'R'}