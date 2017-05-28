#include <Servo.h>

// START by sending 100
// WAIT A COUPLE SECONDS
// SEND 0
// WAIT A COUPLE SECONDS
// SEND 5
// YOU'RE GOOD TO GO#include <Servo.h>
 
Servo esc1;
Servo esc2;
Servo esc3;
Servo esc4;

int throttlePin = 0;
int throttle=0;
int n = 0;
int flag1 = 0;
 
void setup()
{
  esc1.attach(2);
  esc2.attach(3);
  esc3.attach(4);
  esc4.attach(5);
  
  Serial.begin(9600);
}
 
void loop()
{
  if (Serial.available() && flag1 == 0)
    {
      if (Serial.readString()=="calibrate1")
      {
        Serial.println("Attach the ESCs and type in done");
        String input;
        while (input!="done")
        {
          if(Serial.available())
            input = Serial.readString();
          esc1.write(2000);
        }
        
        Serial.println("Setting upperlimit to be 2000us");
        int old = millis();
        while((millis() - old) <=1000)
        {
          esc1.write(2000);
        }
        Serial.println("Setting lowerlimit to be 1000us");
        old = millis();
        while((millis() - old) <=5000)
        {
          esc1.write(1000);
        }
        Serial.println("DONE...");
        flag1=1;
      }
    }
  if(Serial.available())
    {throttle = Serial.parseInt();}
    
  Serial.println(throttle);
  esc1.write(throttle);
  /*esc2.write(throttle);
  esc3.write(throttle);
  esc4.write(throttle);*/
}
