/*
 * Ultrasonic Bot - HCSR04 (Ultrasonic Sensor), DRV8835 (Motor Driver), RGB Led
   Initially, bot moves forward. On obstacle detection within a range of 10 cms,
   2wdbot stops, reverses and takes a left turn.
   
 * Author : Electronut Labs
 * Website  : electronut.in
*/

// DRV8835 pin definitions
int AIN1 = A5;
int AIN2 = 9;
int BIN1 = A4;
int BIN2 = 8;
int MODE = 7;

// HCSR-04 pin definitions
int trigger = 2;
int echo = 5;

// LED pin definitions
int ledR = 12;
int ledB = 11;
int ledG = 13;

// function to setup motors.
// motor determines which output terminal is active, MA = true or MB = false.
// motorDirection determines the direction in which motor rotates. Forward = true and Backward = false.
void setDCMotor(boolean motor, boolean motorDirection, uint8_t motorSpeed)
{
  // MA terminal active
  if(motor == true) {
    // motor in forward direction
    if(motorDirection == true) {
      digitalWrite(AIN1, HIGH);
      analogWrite(AIN2, motorSpeed);
    }
    // motor in reverse direction
    else {
      digitalWrite(AIN1, LOW);
      analogWrite(AIN2, motorSpeed);
    }
  }
  // MB terminal active
  else {
    // motor in forward direction
    if(motorDirection == true) {
      digitalWrite(BIN1, HIGH);
      analogWrite(BIN2, motorSpeed);
    }
    // motor in reverse direction
    else {
      digitalWrite(BIN1, LOW);
      analogWrite(BIN2, motorSpeed);
    }
  }
}

// function to stop motors
void stopMotors()
{
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, LOW);
}

// function to use HCSR-04 Ultrasonic module
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

// function to light led with a specific colour
void ledColor(uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t redPinValue = 255 - red;
  uint8_t greenPinValue = 255 - green;
  uint8_t bluePinValue = 255 - blue;

  analogWrite(ledR, redPinValue);
  analogWrite(ledG, greenPinValue);
  analogWrite(ledB, bluePinValue);
}

// function to turn led off
void ledOff()
{
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}

void setup()
{
  SerialUSB.begin(9600);
  
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(MODE, OUTPUT);
  digitalWrite(MODE, HIGH);
  
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  ledOff();

  // move forward
  setDCMotor(true, true, 100);
  setDCMotor(false, true, 100);
}

void loop()
{
  float currDist = getDistance();
  //SerialUSB.println(currDist);

  if(currDist >= 10) {
    //green
    ledColor(0,255,0);
    delay(100);
  }
  else {
    // turn off led
    ledOff();
    // red
    ledColor(255,0,0);
    // stop motors
    stopMotors();
    delay(1000);
    // turn off led
    ledOff();

    // reverse
    // blue
    ledColor(0,0,255);
    setDCMotor (true, false, 100);
    setDCMotor(false, false, 100);
    delay(800);
    // turn off led
    ledOff();

    // left turn
    // magenta
    ledColor(255,0,255);
    setDCMotor(true, true, 100);
    setDCMotor(false, false, 50);
    delay(800);
    // turn off led
    ledOff();

    // forward
    setDCMotor(true, true, 100);
    setDCMotor(false, true, 100);
  }
}
