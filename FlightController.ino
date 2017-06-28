/*
 * Filename: FlightController.ino
 *
 * Author: Gaurav Parmar
 *
 * Description: This is the main quadcopter flight controller code
 * meant to be used with an arduino uno.
 *
 * Pin Mappings: //TODO
 */
#include <wire.h>
#include "IMU.h"
#include "config.h"
#include "droneBluetooth.h"

double gyro_offsets[3];
double raw_gyro[3];

float raw_accel[3];
double gyro_pid_in[3];

double controllerInput[4];

char current_stage[5] = "OFF  ";

void setup()
{
  Wire.begin();
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  setupGyro();
  delay(1000);

  //setupAccel();

  setGyroOffSets(2000, &gyro_offsets[0]); //TODO

  setupPinChangeInterrupts();
}

void loop()
{
  updateRawGyro(&raw_gyro);
  //updateRawAccel(&rawAccel);
  int i;
  for(i=0;i<3;i++)
    gyro_pid_in[i] = (gyro_pid_in[i]*0.9) + ((raw_gyro[i]/57.14286)*0.1);
}

void setupPinChangeInterrupts()
{
  PCIR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT0);
  PCMSK0 |= (1<<PCINT1);
  PCMSK0 |= (1<<PCINT2);
  PCMSK0 |= (1<<PCINT3);
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
