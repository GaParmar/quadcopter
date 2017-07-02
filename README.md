# quadcopter
3Dprinted bluetooth controlled quadcopter

## Sensors used:
  * mpu 6050:
    * 6 dof Gyroscope + Accelerometer 
    * [website](https://www.sparkfun.com/products/11028)
    *  [datasheet](http://43zrtwysvxb2gf29r5o0athu.wpengine.netdna-cdn.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
    *  I2C address: (AD0=0) - 1101000, (AD0=1) - 1101001

## Bluetooth Communication Protocol:
  * each transmission is a (5+1) character array:
    * First character Indicates the type of data being transmitted
      * 'r' - indicates that the next 4 characters represent roll value
      * 'p' - indicates that the next 4 characters represent pitch value
      * 'y' - indicates that the next 4 characters represent yaw value
      * 't' - indicates that the next 4 characters represent thrust value
      * 'P' - indicates that the transmission is regarding Proportional component of the PID
        1. 'P' followed by 'r' - Proportional constant for roll
       	2. 'P' followed by 'p' - Proportional constant for pitch
       	3. 'P' followed by 'y' - Proportional constant for yaw
      * 'I' - indicates that the transmission is regarding Integral component of the PID
        1. 'I' followed by 'r' - Integral constant for roll
       	2. 'I' followed by 'p' - Integral constant for pitch
       	3. 'I' followed by 'y' - Integral constant for yaw
      * 'D' - indicates that the transmission is regarding Derivative constant of the PID
		1. 'D' followed by 'r' - Derivative constant for roll
		2. 'D' followed by 'p' - Derivative constant for pitch
		3. 'D' followed by 'y' - Derivative constant for yaw
		
    * Character 2, 3, 4, 5: The numerical value associated with the type
    
    * SPECIAL CASES:
      * If any error occurs, the array is {'E', 'R', 'R', 'O', 'R', '\0'}
      * To start the quadcopter, the array is {'S', 'T', 'A', 'R', 'T', '\0'}
