#include <Arduino.h>

// put function declarations here:
#include "Servo.h"

Servo myServo;

void setup() {
  // put your setup code here, to run once:
  // pinMode(3, OUTPUT);
  myServo.attach(3);
}

void loop() {
  // put your main code here, to run repeatedly:
  // analogWrite(3, 0); // turn the LED on (HIGH is the voltage level)
  // delay(1000); // wait for a second
  myServo.write(90); // turn the servo to 90 degrees
  delay(1000); // wait for a second
  myServo.write(0); // turn the servo to 0 degrees
  delay(1000); // wait for a second
}
