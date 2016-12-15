/*
 * Stepper-Iris - This example demonstrates the movement of a mechanical iris using a Stepper motor 
   and an Ultrasonic sensor. On detecting an object in front of the sensor, the gear mounted stepper
   motor rotates, causing the iris to open. On removing the object, the iris is closed.  
    
 * Author : Electronut Labs
 * Website  : electronut.in
*/
 
#include <Stepper.h>

// number of steps required for the internal gear to complete one rotation
#define stepsPerRevolution 32
// number of steps required for external shaft to complete one rotation.
#define stepsPerOutputRevolution 32*64

// HCSR-04 initialization.
int trigger = 2;
int echo = 4;

// gear ratio = T2/T1; where T1 is the number of teeth on drive gear (gear connected to motor) and T2 is the number of teeth on driven gear (gear connected to load).
// gear ratio determines the number of turns drive gear needs to make for the driven gear to achieve one complete rotation.
// T2 = 13 (to open or close the iris), T1 = 40.
// gear ratio = 13/40
// gear ratio = 0.325
// steps = 0.325 * stepsPerOutputRevolution
// steps = 665.6

int steps =  0.325 * stepsPerOutputRevolution;

// initialize the stepper library.
Stepper myStepper(stepsPerRevolution, A5, 9, A4, 8);

float getDistance()
{
  // send a 10uS pulse
  digitalWrite(trigger, LOW);
  delayMicroseconds(20);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(20);

  //echo duration
  int duration = pulseIn(echo, HIGH);

  if(duration > 0) {
    // dist = duration * speed of sound * 0.5
    // dist in cm = duration in uS * 10^(-6) * 340.26 * 100 * 0.5
    // = duration * 0.017
    float dist = duration * 0.017;
    //SerialUSB.println(dist);
    return dist;
  }
}

void stopStepper()
{
  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
}

int R = 12;
int G = 11;
int B = 13;

void flashRed()
{
  // red ON  
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);

  delay(1000);

  // LED OFF
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);

  delay(1000);

  // red ON
  digitalWrite(R, LOW);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);

  delay(1000);

  // LED OFF
  digitalWrite(R, HIGH);
  digitalWrite(G, HIGH);
  digitalWrite(B, HIGH);
}

void setup() {
  // set the speed at 700 rpm:
  myStepper.setSpeed(700);
  // initialize the serial port:
  SerialUSB.begin(9600);

  // set HCSR-04 pins
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  stopStepper();

  // set RGB LED pins
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);

  // blink Red twice.
  flashRed();
}

float currentDistance;
float previousDistance = 0.0;

bool flag = false;

void loop() {
  currentDistance = getDistance();

  // object detected
  if(currentDistance <= 15) {
    myStepper.step(steps);
    delay(500);
    flag = true;
  }
  // object removed
  if((currentDistance > 15) && (flag == true)) {
    myStepper.step(-steps);
    flag = false;
  }
  stopStepper();
}
