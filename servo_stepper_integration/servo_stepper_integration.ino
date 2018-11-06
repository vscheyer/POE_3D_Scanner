//INTEGRATING 2 HARDCODED SERVOS AND GANTRY STEPPER MOTOR

#include <Servo.h>
#include <FileIO.h>
#include <SPI.h>
#include <SD.h>
#include "SpeedyStepper.h"

#define MS1 4
#define MS2 5
#define EN  6

SpeedyStepper stepper1;

Servo pushServo1;
Servo pushServo2;

int distanceArray[2][2]; //for 2x2 matrix of blocks
int angleArray[2][2];
int servoAngleArray[2][2];
int r = 2;
int c = 2;
boolean servosDone;

String input;
int angle = 0;
boolean newData = false;
int oldAngle = 0;

void setup() {
  //Stepper motor pins
  stepper1.connectToPins(10, 11);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);

  //set both MS1 and MS2 to low for single stepping
  digitalWrite(EN, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  pushServo1.attach(22); //digital pins on Arduino mega
  pushServo2.attach(23);
  Serial.begin(9600);

  //fill arrays for servo data, eventually from Kinect
  distanceArray[1][1] = 1;
  distanceArray[1][2] = 2;
  distanceArray[2][1] = 3;
  distanceArray[2][2] = 4;

  //map distances to angle array
  for (c = 1; c < 11; c++) {
    for (r = 1; r < 11; r++) {
      angleArray[r][c] = map(distanceArray[r][c], 0, 4, 180, 0);
    }
  }
}

void moveGantry() {
  //Move one motor in units of revolutions:
  stepper1.setStepsPerRevolution(200);

  // set the speed in rotations/second and acceleration in
  // rotations/second/second
  stepper1.setSpeedInRevolutionsPerSecond(10);
  stepper1.setAccelerationInRevolutionsPerSecondPerSecond(10);

  //move 35.52 revolutions to next gantry position
  stepper1.moveRelativeInRevolutions(35.52); //number of revolutions to make lead screw go 2.22 inches
}

void loop() {
  for (r = 1; r < 3; r++) {
    for (c = 1; c < 3; c++) {
      pushServo1.write(angleArray[r][c]);
      pushServo2.write(angleArray[r][c]);
      delay(300);
      pushServo1.write(0); //reset servos for gantry to move
      pushServo2.write(0);
      moveGantry();
    }
  }
}
