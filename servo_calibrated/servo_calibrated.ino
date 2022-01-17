#include "Servo.h"

Servo servo;

volatile int bottom = 0;
volatile int top = 1023;

void setup()
{
  servo.attach(9);
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, calBottom, FALLING);
  attachInterrupt(1, calTop, FALLING);
}

void calBottom()
{
  bottom = analogRead(0);
}

void calTop()
{
  top = analogRead(0);
}

void loop()
{
  int sensorValue = analogRead(0);
  int deg = map(sensorValue, bottom, top, 10, 170);
  deg = constrain(deg, 10, 168);
  servo.write(deg);
  
  Serial.print(sensorValue);
  Serial.print(" ");
  Serial.println(deg);
}
