#include <Servo.h>
#include <FileIO.h>

Servo pushServo0;

angleArray = [2][2];
int distanceArray[2][2]; //for 2x2 matrix of blocks
int servoAngleArray[2][2];
int reading = 1;

String input;
int angle = 0;
boolean newData = false;
int oldAngle = 0;

void setup() {
  pushServo1.attach(10);
  pushServo2.attach(11);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
   //Serial.print("Waiting for input");
   input1 = Serial.readString();
   angleArray[1] = map(input1.toInt(),0,4,180,0);
   input2 = Serial.readString();
   angleArray[2] = map(input2.toInt(),0,4,180,0);
   newData = true;
  }
  if (newData == true) {
    if (oldAngle < angle) {
      for (int pos = oldAngle; pos <= angle; pos += 1) {
        pushServo0.write(pos);
        delay(15);
      }
    }
    else {
      for (int pos = oldAngle; pos >= angle; pos -= 1) {
        pushServo0.write(pos);
        delay(15);
      }
    }
    pushServo0.write(angle);
    newData = false;
    oldAngle = angle;
  }
}
