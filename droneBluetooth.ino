
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(4, 5);
char in = malloc(1);
int ctr=0;

void setup()
{
  Serial.begin(57600);
  BTSerial.begin(9600);
  pinMode(1, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(0, INPUT);
  digitalWrite(13, LOW);
  Serial.println("COMMUNICATION STARTING");
}

void loop()
{
  
  if (BTSerial.available())
  {
    char c = BTSerial.read();
    String value = "";
    while (BTSerial.peek() != 't' || BTSerial.peek() != 'p' || BTSerial.peek() != 'r' || BTSerial.peek() != 'y')
    {
      value+=BTSerial.read();
    }
    int progress = atoi(value);
    Serial.print(c);
    Serial.print('\n');
  }
}
