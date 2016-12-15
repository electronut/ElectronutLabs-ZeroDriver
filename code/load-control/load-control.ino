/*
 * Load Control - This example demonstrates the use of ZeroDriver in high current applications(upto 3A).
   Two LED strips are connected to the H-bridges. These strips are switched on and off alternatively.
   Each H-bridge can support 1.5A current and can be connected in parallel to provide 3A current.
    
 * Author : Electronut Labs
 * Website  : electronut.in
*/

// DRV8835 initializations.
int AIN1 = A5;
int AIN2 = 9;
int BIN1 = A4;
int BIN2 = 8;
int MODE = 7;

// RGB LED initializations.
int ledR = 12;
int ledG = 11;
int ledB = 13;

void setup() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  // set DRV8835 to phase/enable PH/EN mode
  digitalWrite(MODE, HIGH);
  // confgure both H-bridges in same direction.
  digitalWrite(AIN1, HIGH);
  digitalWrite(BIN1, HIGH);
  // disable H-bridges.
  analogWrite(BIN2, 0);
  analogWrite(AIN2, 0);
  
  // set up RGB led pins
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  // turn RGB LED off.
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, HIGH);
}

// Output Channel 1 - ON, Output Channel 2 - OFF
// wait for 1 second.
// Output Channel 1 - OFF, Output Channel 2 - ON
// wait for 1 second.

void loop()
{
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN2, LOW);
  // cyan
  digitalWrite(ledR, HIGH);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  
  delay(1000);
  
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN2, HIGH);
  // magenta.
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, HIGH);
  digitalWrite(ledB, LOW);

  delay(1000);
}

