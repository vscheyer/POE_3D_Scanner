/*
  Pandora Final Poe-Project of team Poetatos
  Authors: Richard Ballaux, Leo Liu, Alison Palmer, Vienna Scheyer
*/
//IMPORTS--------------------------------------------------------------------
#include <Servo.h>
#include "SpeedyStepper.h"

//Initialize stepper motor -------------------------------------------------

#define MS1 4
#define MS2 5
#define EN  6
#define stp 2
#define dir 3
SpeedyStepper stepper1;

//Initializations of the servos --------------------------------------------
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo lockServo1;
Servo lockServo2;
Servo lockServo3;
Servo lockServo4;
Servo lockServo5;
Servo lockServo6;
Servo lockServo7;
Servo lockServo8;
Servo lockServo9;
Servo lockServo10;


//Initializing global variables ---------------------------------------------

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int rowCounter = 0;

int lockPos = 50;
int unlockPos = 0;
int stepperSize = 35;

float distanceArray[10][10];
int angleArray[10][10];

void setup() {
  // initialize serial:
  Serial.begin(9600);
  servo1.attach(24);
  servo2.attach(25);
  servo3.attach(26);
  servo4.attach(27);
  servo1.attach(28);
  servo2.attach(29);
  servo3.attach(30);
  servo4.attach(31);
  servo3.attach(32);
  servo4.attach(33);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);
  servo7.write(0);
  servo8.write(0);
  servo9.write(0);
  servo10.write(0);

  lockServo1.attach(34);
  lockServo2.attach(35);
  lockServo3.attach(36);
  lockServo4.attach(37);
  lockServo5.attach(38);
  lockServo6.attach(39);
  lockServo7.attach(40);
  lockServo8.attach(41);
  lockServo9.attach(42);
  lockServo10.attach(43);
  lockServo1.write(unlockPos);
  lockServo2.write(unlockPos);
  lockServo3.write(unlockPos);
  lockServo4.write(unlockPos);
  lockServo5.write(unlockPos);
  lockServo6.write(unlockPos);
  lockServo7.write(unlockPos);
  lockServo8.write(unlockPos);
  lockServo9.write(unlockPos);
  lockServo10.write(unlockPos);

  stepper1.connectToPins(stp, dir);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);
  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  stepper1.setCurrentPositionInMillimeters(0);

  //Set the number of steps per mm for belt gantry
  stepper1.setStepsPerMillimeter(40);

  //Set speed and acceleration in mm per second
  stepper1.setSpeedInMillimetersPerSecond(10);
  stepper1.setAccelerationInMillimetersPerSecondPerSecond(10);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}
void loop() {
  // print the string when a newline arrives:

  if (stringComplete) {
    getInput();

    // clear the string:
    inputString = "";
    stringComplete = false;
    rowCounter++;
    if (rowCounter == 10) {
      Serial.print("Q");
      distanceToAngle();
      rowCounter = 1;
    }
    Serial.print(char(rowCounter));

  }
}
void serialEvent() {
  while (Serial.available() > 0) {
    //    inputString = Serial.read();
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == 'A') {
      stringComplete = true;
    }
  }
}


void getInput() {
  for (int c = 0; c < 10; c++) {
    distanceArray[rowCounter][c] = inputString.substring(inputString.indexOf(',') + 1, inputString.indexOf(",", +1)).toFloat(); // find string between 2 commas
    inputString.remove(0, 5); //remove first comma and number
  }
}
void writeToServos() {
  for (int r = 0; r < 4; r++) {
    servo1.write(angleArray[r][0]);
    servo2.write(angleArray[r][1]);
    servo3.write(angleArray[r][2]);
    servo4.write(angleArray[r][3]);
    servo5.write(angleArray[r][4]);
    servo6.write(angleArray[r][5]);
    servo7.write(angleArray[r][6]);
    servo8.write(angleArray[r][7]);
    servo9.write(angleArray[r][8]);
    servo10.write(angleArray[r][9]);
    delay(1000);

    if (r == 0) {
      lockServo1.write(lockPos);
      stepper1.moveToPositionInMillimeters(0);
    }
    if (r == 1) {
      lockServo2.write(lockPos);
      stepper1.moveToPositionInMillimeters(1*stepperSize);
    }
    if (r == 2) {
      lockServo3.write(lockPos);
      stepper1.moveToPositionInMillimeters(2*stepperSize);
    }
    if (r == 3) {
      lockServo4.write(lockPos);
      stepper1.moveToPositionInMillimeters(3*stepperSize);
    }
    if (r == 4) {
      lockServo5.write(lockPos);
      stepper1.moveToPositionInMillimeters(4*stepperSize);
    }
    if (r == 5) {
      lockServo6.write(lockPos);
      stepper1.moveToPositionInMillimeters(5*stepperSize);
    }
    if (r == 6) {
      lockServo7.write(lockPos);
      stepper1.moveToPositionInMillimeters(6*stepperSize);
    }
    if (r == 7) {
      lockServo8.write(lockPos);
      stepper1.moveToPositionInMillimeters(7*stepperSize);
    }
    if (r == 8) {
      lockServo9.write(lockPos);
      stepper1.moveToPositionInMillimeters(8*stepperSize);
    }
    if (r == 9) {
      lockServo10.write(lockPos);
      stepper1.moveToPositionInMillimeters(9*stepperSize);
    }
    delay(200);
    resetPushBlocks();
    delay(3000);
  }
}
void distanceToAngle() {
  for (int c = 0; c < 10; c++) {
    for (int r = 0; r < 10; r++) {
      angleArray[r][c] = ourMap(distanceArray[r][c], 0, 4, 180, 0);
    }
  }
  writeToServos();
}
void resetPushBlocks() {
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  servo5.write(0);
  servo6.write(0);
  servo7.write(0);
  servo8.write(0);
  servo9.write(0);
  servo10.write(0);
}
int ourMap(float value, long in_min, long in_max, long out_min, long out_max) {
  return (int)(value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
