#include <wire.h>
#include "IMU.h"
#include "config.h"

double gyroOffsets[3];
double rawGyro[3];

float rawAccel[3];
double gyro_rpy_in[3];

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

  setGyroOffSets(2000, &gyroOffsets[0]); //TODO

  setupPinChangeInterrupts();
}

void loop()
{
  updateRawGyro(&rawGyro);
  //updateRawAccel(&rawAccel);
  int i;
  for(i=0;i<3;i++)
    gyro_rpy_in[i] = (gyro_rpy_in[i]*0.9) + ((rawGyro[i]/57.14286)*0.1);
}

void setupPinChangeInterrupts()
{
  PCIR |= (1<<PCIE0);
  PCMSK0 |= (1<<PCINT0);
  PCMSK0 |= (1<<PCINT1);
  PCMSK0 |= (1<<PCINT2);
  PCMSK0 |= (1<<PCINT3);
}
