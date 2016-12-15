/*
 * MeArm Joystick - This example demonstrates the working of MeArm robotic arm
   using ZeroDriver. The MeArm is controlled using two joysticks. 
    
 * Reference: https://codebender.cc/sketch:169809#MeArm_Joy_NoLCD.ino
 
 * Author : Electronut Labs
 * Website  : electronut.in
*/

#include <Servo.h> 

#define XPOS 0
#define YPOS 1

const int SERVOS = 4;
const int ACC = 10; // the accurancy of the potentiometer value before idle starts counting
int PIN[SERVOS], value[SERVOS], idle[SERVOS], currentAngle[SERVOS], MIN[SERVOS], MAX[SERVOS], INITANGLE[SERVOS], previousAngle[SERVOS],ANA[SERVOS];
Servo myservo[SERVOS];

void setup()   {
  SerialUSB.begin(57600);
  //Middle Servo
  PIN[0] = 4;
  MIN[0] = 0;
  MAX[0] = 180;
  INITANGLE[0] = 90;
  ANA[0] = 1;
  //Left Side
  PIN[1] = 5;
  MIN[1] = 20;
  MAX[1] = 170;
  INITANGLE[1] = 45;
  ANA[1] = 0;
  //Right Side
  PIN[2] = 6;
  MIN[2] = 30;
  MAX[2] = 150;
  INITANGLE[2] = 60;
  ANA[2] = 2;
  //Claw Servo
  PIN[3] = 10;
  MIN[3] = 0;
  MAX[3] = 80;
  INITANGLE[3] = 25;
  ANA[3] = 3;
  
  for (int i = 0; i < SERVOS; i++) {
    myservo[i].attach(PIN[i]);
    myservo[i].write(INITANGLE[i]);
    value[i] = 0;
    idle[i] = 0;
    previousAngle[i]=INITANGLE[i];
  }
}

void loop() {
  // Delay function to slow movement of arm down
  delay(15); 
  for (int i = 0; i < SERVOS; i++) {
    // read analog values from joysticks.
    value[i] = analogRead(ANA[i]); 
    // read current position of each servo.
    currentAngle[i] = myservo[i].read();
  
    if (value[i] > 612) {
      idle[i] = 0;
      // if current position less than maximum position, increment position.
      if (currentAngle[i] < MAX[i]) 
        ++currentAngle[i];
      if (!myservo[i].attached()) {
        myservo[i].attach(PIN[i]);
      }
      // set servos to the desired position.
      myservo[i].write(currentAngle[i]);     
    } 
    else if (value[i] < 412) {
      idle[i] = 0;
      // if current position greater than maximum position, decrement position.
      if (currentAngle[i] > MIN[i]) --currentAngle[i];
      if (!myservo[i].attached()) {
        myservo[i].attach(PIN[i]);
      }
      // set servos to the desired position.
      myservo[i].write(currentAngle[i]);    
    } 
    else {
      ++idle[i];
    }
    if (idle[i] > 100) {
      myservo[i].detach();
      idle[i] = 0;
    }  
  }  
}
