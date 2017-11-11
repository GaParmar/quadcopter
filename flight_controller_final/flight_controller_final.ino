/**
 * WIRING GUIDE:
 * 
 * ESC 1:
 * White: digital pin 6
 * Red: -
 * Black: Ground
 * 
 * ESC 2:
 * White: digital pin 3
 * Red: -
 * Black: Ground
 * 
 * ESC 3:
 * White: digital pin 4
 * Red: -
 * Black: Ground
 * 
 * ESC 4:
 * White: digital pin 5
 * Red: -
 * Black: Ground
 * 
 * IR receiver:
 * +: 5v
 * -: ground
 * Channel 2 (throttle): analog pin A0
 * 
 * MPU 6050:
 * Vin: 5V
 * Gnd: ground
 * SDA: SDA
 * SCL: SCL
 * INT: digital 2
 * 
 * TODO: Bluetooth rx/tx connection
 */

#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif






// GLOBAL VARIABLES
Servo motor[4];
unsigned long curr_time, timer_1;
byte last_channel;
int throttle;
int motor_output[4];
int flag1 = 0;
float mpu_angle[3];
bool motor_calibration_status = false;

// PID VARIABLES
float roll_pid[3], pitch_pid[3], yaw_pid[3]; 
float roll_setpoint, pitch_setpoint, yaw_setpoint;
float roll_integral_sum, pitch_integral_sum, yaw_integral_sum;
float prev_roll, prev_pitch, prev_yaw;

// IMU variables
MPU6050 mpu;
bool blinkState = false;
bool dmpReady=false;
uint8_t mpuIntStatus, devStatus;
uint16_t packetSize, fifoCount;
uint8_t fifoBuffer[64];
Quaternion q;
VectorInt16 aa, aaReal, aaWorld;
VectorFloat gravity;
float euler[3], ypr[3], ypr_offsets[3];
int offset_ctr;
volatile bool mpuInterrupt = false;

void dmpDataReady(){
  mpuInterrupt = true;
}

void updateOffsets(int total){
  if (!dmpReady) return;
  offset_ctr = 0;
  while(offset_ctr <= total){
    while(!mpuInterrupt && fifoCount<packetSize);
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();
    fifoCount = mpu.getFIFOCount();
    if ((mpuIntStatus&0x10)||fifoCount==1024){
      mpu.resetFIFO();
      Serial.println("FIFO overflow");
    } else if (mpuIntStatus & 0x02){
      while(fifoCount<packetSize) fifoCount = mpu.getFIFOCount();
      mpu.getFIFOBytes(fifoBuffer, packetSize);
      fifoCount -= packetSize;
      offset_ctr++;
      mpu.dmpGetQuaternion(&q,fifoBuffer);
      mpu.dmpGetGravity(&gravity,&q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      ypr_offsets[0] += ypr[0]*180/M_PI;
      ypr_offsets[1] += ypr[1]*180/M_PI;
      ypr_offsets[2] += ypr[2]*180/M_PI;
    }
  }
  ypr_offsets[0] /= total*1.0;
  ypr_offsets[1] /= total*1.0;
  ypr_offsets[2] /= total*1.0;
}

void setup() {

  // Hardware setup
  motor[0].attach(6);
  motor[1].attach(3);
  motor[2].attach(4);
  motor[3].attach(5);
  pinMode(A0,INPUT);

  // Interrupt setup
  cli();
  PCICR = 0x02;
  PCMSK1 |= bit (PCINT8);
  sei();

  // Initialize the serial communication
  Serial.begin(9600);

  // Add a 5 second delay to stabilize the connections
  for (int i = 0; i < 5; i++){
    Serial.print(".");
    delay(1000);
  }

  // MPU6050 setup
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
      Wire.setClock(400000);
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  pinMode(2,INPUT);
  Serial.println("Initializing I2C devices");
  mpu.initialize();
  Serial.println("Testing IMU connection");
  Serial.println(mpu.testConnection()? "success":"failure");
  delay(3000);
  Serial.println("Initializing DMP");
  devStatus = mpu.dmpInitialize();
  if (devStatus == 0){
    Serial.println("Enabling DMP");
    mpu.setDMPEnabled(true);
    Serial.println("Enabling Interrupt detection");
    attachInterrupt(digitalPinToInterrupt(2),dmpDataReady,RISING);
    mpuIntStatus = mpu.getIntStatus();
    Serial.println("DMP ready");
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
  }else{
    Serial.println("DMP initialization failed");
  }

  pinMode(13,OUTPUT);
  Serial.println("Waiting for the sensor to stabilize (20 seconds)");
  for (int i = 10; i>0; i--){
    delay(1000);
    Serial.print(i);
  }
  Serial.print("\nCalculating the offsets");
  mpu.resetFIFO();
  updateOffsets(1000);
  Serial.println("\nSETUP COMPLETE");
}


void calibrateMotors(){
  Serial.println("Attach the ESCs and type in done");
  String input;
  while(input!="done"){
    if (Serial.available())
      input = Serial.readString();
    for(int i =0; i<4;i++)
      motor[i].write(2000);
  }
  // Setting uppperlimit to be 2000us
  int old = millis();
  while((millis()-old) <= 1000){
    for(int i =0; i<4;i++)
      motor[i].write(2000);
  }
  // Setting lower limit to be 1000us
  old = millis();
  while((millis()-old) <= 5000){
    for(int i =0; i<4;i++)
      motor[i].write(1000);
  }
  Serial.println("DONE....");
  flag1=1;
}


void loop(){
  if (!dmpReady) return;
  while(!mpuInterrupt && fifoCount<packetSize){
    // Waiting for the buffer to fill up
  }
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();
  if ( (mpuIntStatus & 0x10) || fifoCount == 1024 ){
    mpu.resetFIFO();
    Serial.println("FIFO overflow");
  }else if (mpuIntStatus & 0x02){
    while(fifoCount<packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
    float yaw = (ypr[0]*180/M_PI) - ypr_offsets[0];
    float pitch = (ypr[1]*180/M_PI) - ypr_offsets[1];
    float roll = (ypr[2]*180/M_PI) - ypr_offsets[2];

    blinkState = !blinkState;
    digitalWrite(13, blinkState);

    // MOTOR CONTROL CODE
    if (Serial.available() && flag1==0){
      String input = Serial.readString();
      if (input == "calibrate"){
        calibrateMotors();
        motor_calibration_status = true;
      }
    }

    roll_setpoint = 0;
    pitch_setpoint = 0;
    yaw_setpoint = 0;
    float pid_out[3];
    calculate_pid( pid_out,
                roll_setpoint,
                pitch_setpoint,
                yaw_setpoint,
                roll,
                pitch,
                yaw);
    int temp_throttle = throttle;
    // Cap the motor output to 50%
    if (temp_throttle > 1500){
      temp_throttle = 1500;
    }
  }
  
  
  int temp = throttle;
  if (temp>1500)
    temp = 1500;
  for(int i =0; i<4;i++)
    motor[i].write(temp);
      //motors[i].write(motor_output[i]);
}

ISR(PCINT1_vect) { 
  curr_time = micros();
  if (digitalRead(A0)){
    if (last_channel == 0){
      last_channel = 1;
      timer_1 = curr_time;
    }
  }
  else if (last_channel == 1){
    last_channel = 0;
    throttle = curr_time - timer_1;
  }
}



void calculate_pid( float * pid_out,
               float roll_setpoint,  
               float pitch_setpoint,
               float yaw_setpoint,
               float roll_input,
               float pitch_input,
               float yaw_input){

  // Roll processing
  float error_roll = roll_input - roll_setpoint;
  roll_integral_sum += roll_pid[1]*error_roll;
  pid_out[0] = roll_pid[0]*error_roll + roll_integral_sum + roll_pid[2]*(error_roll - prev_roll);
  prev_roll = error_roll;

  // Pitch processing
  float error_pitch = pitch_input - pitch_setpoint;
  pitch_integral_sum += pitch_pid[1]*error_pitch;
  pid_out[1] = pitch_pid[0]*error_pitch + pitch_integral_sum + roll_pid[2]*(error_pitch-prev_pitch);
  prev_pitch = error_pitch;

  // Pitch processing
  float error_yaw = yaw_input - yaw_setpoint;
  yaw_integral_sum += yaw_pid[1]*error_yaw;
  pid_out[2] = yaw_pid[0]*error_yaw + yaw_integral_sum + yaw_pid[2]*(error_yaw-prev_yaw);
  prev_yaw = error_yaw;

}

