//THIS CODE CURRENTLY CONTROLS 2 SERVOS WITH HARDCODED VALUES

#include <Servo.h>
#include <FileIO.h>
#include <SPI.h>
#include <SD.h>

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
  pushServo1.attach(22); //digital pins on Arduino mega
  pushServo2.attach(23);
  Serial.begin(9600);

  distanceArray[1][1] = 1;
  distanceArray[1][2] = 2;
  distanceArray[2][1] = 3;
  distanceArray[2][2] = 4;

  for (c = 1; c < 11; c++) {
    for (r = 1; r < 11; r++) {
      angleArray[r][c] = map(distanceArray[r][c], 0, 4, 180, 0);
    }
  }
}

void loop() {
  for (r = 1; r < 3; r++) {
    for (c = 1; c < 3; c++) {
      pushServo1.write(angleArray[r][c]);
      pushServo2.write(angleArray[r][c]);
      delay(300);
      pushServo1.write(0); //reset servos for gantry to move
      pushServo2.write(0);
    }
  }
}
