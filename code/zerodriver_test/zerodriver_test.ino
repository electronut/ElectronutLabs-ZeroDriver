/*
 * zerodriver_test - Code to test basic functionality of ZeroDriver.
   The RGB LED blinks white color twice. This is followed by spinning 
   of motors with RGB LED lit as cyan. Post 2 seconds delay, RGB LED 
   switches to magenta and the motors spin in a reverse direction.

 * Author : Electronut Labs
 * Website  : electronut.in
*/

int AIN1 = A5;
int AIN2 = 9;
int BIN1 = A4;
int BIN2 = 8;
int MODE = 7;

int ledR = 12;
int ledG = 11;
int ledB = 13;

void setup() {
  // set all pins to output
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(MODE, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN2, OUTPUT);
  // set DRV8835 to phase/enable PH/EN mode
  digitalWrite(MODE, HIGH);
  // stop motors
  analogWrite(BIN2, 0);
  analogWrite(AIN2, 0);

  // set up RGB led pins
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  
  // turn led off
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}


void loop()
{
  // blink white twice
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

  delay(500);

  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);

  delay(500);

  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

  delay(500);

  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);

  delay(1000);
    
  // set to cyan
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);

  // set M1 and M2 in forward direction at 50 %
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  analogWrite(AIN2, 127);
  analogWrite(BIN2, 127);

  delay(2000);

  // stop motors
  analogWrite(AIN2, 0);
  analogWrite(BIN2, 0);

  delay(1000);

  // set to magenta
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);

  // set M1 and M2 in reverse direction at 50 %
  digitalWrite(AIN1, LOW);
  digitalWrite(BIN1, LOW);
  analogWrite(AIN2, 127);
  analogWrite(BIN2, 127);

  delay(2000);

  // stop motors
  analogWrite(AIN2, 0);
  analogWrite(BIN2, 0);

  delay(1000);
}
