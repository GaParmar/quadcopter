/*
 * Filename: FlightController.ino
 *
 * Author: Gaurav Parmar
 *
 * Description: This is the main quadcopter flight controller code
 * meant to be used with an arduino uno.
 *
 * Pin Mappings: 
 * Digital Out 4, 5: bluetooth serial communication with controller//TODO
 */
#include <Wire.h>
#include "IMU.h"
#include "config.h"
#include "droneBluetooth.h"

/*
 ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
 ***** Declaring the global variables needes.                            ***** *****
 ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** ***** *****
 */
const int GYRO_ADDRESS;
double gyro_offsets[3];
double raw_gyro[3];
float raw_accel[3];
double gyro_pid_in[3];
int controllerInput[4];
char current_stage[5] = "OFF  ";
// Different "stages" the program has during its lifetime:
//  1. OFF
//  2. MANUA
//  3. AUTOL
char * transmission;
// the PID constants
float P_roll, I_roll, D_roll;
float P_pitch, I_pitch, D_pitch;
float P_yaw, I_yaw, D_yaw;



/*
 * Function name: setup();
 * Function prototype: void setup();
 * Paramaters: None
 * Return: None
 * Side Effects: None
 * Description: This subroutine is executed once. It is resposible for 
 * assigning pin states and calibrating the gyroscope and accelerometer
 * to remove the zero offset error. 
 */
void setup()
{
  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Setting the pin modes.        *****
   ***** ***** ***** ***** ***** ***** *****
   */
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Setting up the sensors.       ***** 
   ***** ***** ***** ***** ***** ***** *****
   */
  Wire.begin();
  setupGyro();
  delay(1000);
  //setupAccel();
  setGyroOffSets(2000, &gyro_offsets[0]); 

  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Bluetooth communication config ****
   ***** ***** ***** ***** ***** ***** *****
   */
  setupCommunication();

  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Wait till "START" signal      *****
   ***** ***** ***** ***** ***** ***** *****
   */
  getRawBluetoothString(transmission);
  while(isStart(transmission)) 
     getRawBluetoothString(transmission);
}


/*
 * Function name: loop();
 * Function prototype: void loop();
 * Paramaters: None
 * Return: None
 * Side Effects: None
 * Description: This subroutine is executed indefinitely. It is resposible for 
 * handling the main operation of the quadcopter.
 */
void loop()
{
  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Updating sensor values.       *****
   ***** ***** ***** ***** ***** ***** *****
   */
  updateRawGyro(&raw_gyro);
  //updateRawAccel(&rawAccel);
  int i;
  for(i=0;i<3;i++)
    gyro_pid_in[i] = (gyro_pid_in[i]*0.9) + ((raw_gyro[i]/57.14286)*0.1);

  /*
   ***** ***** ***** ***** ***** ***** *****  
   ***** Updating transmission.        *****
   ***** ***** ***** ***** ***** ***** *****
   */
  getRawBluetoothString(transmission);
  switch(getType(transmission))
  {
    case "roll":
      controllerInput[0] = getValue(transmission);
      break;
    case "pitch":
      controllerInput[1] = getValue(transmission);
      break;
    case "yaw":
      controllerInput[2] = getValue(transmission);
      break;
    case "thrust":
      controllerInput[3] = getValue(transmission);
      break;
    default:
      // TODO: maybe go to the next iteration of the loop? 
  }
}


/*
 * Function Name: updateControllerReadings()
 * Function Prototype: void updateControllerReadings()
 * Parameters: 
 *    double * gr[] -- array of doubles where new readings are stored
 * Return Type: void
 * Description: Updates the controller readings
 * Side Effects: none
 */
void updateControllerReadings(double * gr[])
{
  //TODO
  /*
   * The bluetooth code goes here to get readings from the phone
   */
}
