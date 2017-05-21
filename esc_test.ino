// START by sending 100
// WAIT A COUPLE SECONDS
// SEND 0
// WAIT A COUPLE SECONDS
// SEND 5
// YOU'RE GOOD TO GO#include <Servo.h>

// PIN MAPPING:
// esc white to digital i/o 9
// esc black to gnd
// LEAVE red esc pin unconnected
// 
// ESC power banana male plugs to the lipo
 
Servo esc1;
int throttlePin = 0;
int throttle=0;
int n = 0;
 
void setup()
{
  esc1.attach(9);
  Serial.begin(9600);
}
 
void loop()
{
  if(Serial.available())
    {throttle = Serial.parseInt();}
    
  Serial.println(throttle);
  esc1.write(throttle);
}
