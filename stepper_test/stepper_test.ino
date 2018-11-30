#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "Adafruit_PWMServoDriver.h"
char user_input;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);

void setup() {
  // put your setup code here, to run once:
  AFMS.getStepper(280, 1);
//  AFMS.setSpeed(10);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available()){
      user_input = Serial.read(); //Read user input and trigger appropriate function
      if (user_input =='1'){
         AFMS.step(190, FORWARD, SINGLE);
      } else {
        Serial.println("Invalid option entered.");
      }
  }
}
