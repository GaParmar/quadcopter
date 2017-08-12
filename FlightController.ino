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

float PID_IN[3];
float PID_OUT[3];
float PID_SETPOINT[3];

int FLAGS[3];



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
  updateControllerReadings(&controllerInput, &FLAGS); //yet to be implemented

  if 
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
void updateControllerReadings(int * gr[], int * flags[])
{
  //TODO
  /*
   * The bluetooth code goes here to get readings from the phone
   */
}



void PID (double * in, double * out, double * setpoint)
{
  //Roll calculations
  double difference = *in - *setpoint;
  pid_i_mem_roll += I_roll * difference;

  pid_output_roll = (P_roll * difference) + pid_i_mem_roll + D_roll*(difference - pid_last_roll_d_error);
  if(pid_output_roll > pid_max_roll)pid_output_roll = pid_max_roll;
  else if(pid_output_roll < pid_max_roll * -1)pid_output_roll = pid_max_roll * -1;

  pid_last_roll_d_error = pid_error_temp;

  //Pitch calculations
  pid_error_temp = gyro_pitch_input - pid_pitch_setpoint;
  pid_i_mem_pitch += pid_i_gain_pitch * pid_error_temp;
  if(pid_i_mem_pitch > pid_max_pitch)pid_i_mem_pitch = pid_max_pitch;
  else if(pid_i_mem_pitch < pid_max_pitch * -1)pid_i_mem_pitch = pid_max_pitch * -1;

  pid_output_pitch = pid_p_gain_pitch * pid_error_temp + pid_i_mem_pitch + pid_d_gain_pitch * (pid_error_temp - pid_last_pitch_d_error);
  if(pid_output_pitch > pid_max_pitch)pid_output_pitch = pid_max_pitch;
  else if(pid_output_pitch < pid_max_pitch * -1)pid_output_pitch = pid_max_pitch * -1;

  pid_last_pitch_d_error = pid_error_temp;

  //Yaw calculations
  pid_error_temp = gyro_yaw_input - pid_yaw_setpoint;
  pid_i_mem_yaw += pid_i_gain_yaw * pid_error_temp;
  if(pid_i_mem_yaw > pid_max_yaw)pid_i_mem_yaw = pid_max_yaw;
  else if(pid_i_mem_yaw < pid_max_yaw * -1)pid_i_mem_yaw = pid_max_yaw * -1;

  pid_output_yaw = pid_p_gain_yaw * pid_error_temp + pid_i_mem_yaw + pid_d_gain_yaw * (pid_error_temp - pid_last_yaw_d_error);
  if(pid_output_yaw > pid_max_yaw)pid_output_yaw = pid_max_yaw;
  else if(pid_output_yaw < pid_max_yaw * -1)pid_output_yaw = pid_max_yaw * -1;

  pid_last_yaw_d_error = pid_error_temp;
}
