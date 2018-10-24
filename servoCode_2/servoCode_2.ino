#include <Servo.h>
#include <FileIO.h>

Servo pushServo0;

int distanceArray[10][10];
int servoAngleArray[10][10];
int reading = 1;

String input;
int angle = 0;
boolean newData = false;
int oldAngle = 0;

void setup() {
  pushServo0.attach(10);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
   //Serial.print("Waiting for input");
   input = Serial.readString();
   newData = true;
  }
  if (newData == true) {
    angle = map(input.toInt(),0,4,180,0);
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
