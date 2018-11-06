#include "SpeedyStepper.h"

#define MS1 4
#define MS2 5
#define EN  6

SpeedyStepper stepper1;

void setup() {
  stepper1.connectToPins(10, 11);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
}

void loop() {
  //Move one motor in units of revolutions:
  //
  // set the number of steps per revolutions, 200 with no microstepping,
  // 800 with 4x microstepping
  //
  stepper1.setStepsPerRevolution(200);

  //
  // set the speed in rotations/second and acceleration in
  // rotations/second/second
  //
  stepper1.setSpeedInRevolutionsPerSecond(10);
  stepper1.setAccelerationInRevolutionsPerSecondPerSecond(10);

  //
  // move backward 1.5 revolutions
  //
  stepper1.moveRelativeInRevolutions(35.52); //number of revolutions to make lead screw go 2.22 inches
  delay(5000); //eventually replace with signal from steppers

  //
  // move to an absolute position of 3.75 revolutions
  //
  //    stepper1.moveToPositionInRevolutions(8);
}
