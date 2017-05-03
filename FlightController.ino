#include <wire.h>
#include "IMU.h"

double gyroOffsets[];

void setup()
{
  Wire.begin();
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  
  setupGyro();
  setupAccel();
  
  gyroOffsets = getGyroOffSets();
  setupPinChangeInterrupts();
}

void loop()
{
}

void setupPinChangeInterrupts()
{
  //TODO
}
