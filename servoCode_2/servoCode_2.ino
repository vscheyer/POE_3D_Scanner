//THIS CODE CURRENTLY CONTROLS 2 SERVOS WITH HARDCODED VALUES

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo lockServo;

float distanceArray[10][10]; //for 2x2 matrix of blocks
int angleArray[10][10];

int r = 2;

boolean servosDone;

String input;
int angle = 0;
boolean newData = false;
int oldAngle = 0;

void setup() {
  servo1.attach(22); //digital pins on Arduino mega
  servo2.attach(23);
  lockServo.attach(24);
  Serial.begin(9600);
}

void getInput() {
  if (Serial.available()) {
    input = ",1,2,3,4,"; //Serial.readString(); //read one row at a time
    int rowIndex = input.substring(input.indexOf(",") + 1, input.indexOf(",", 1)).toInt();
    input.remove(0, 2);
    for (int c = 0; c < 10; c++) {
      distanceArray[rowIndex][c] = input.substring(input.indexOf(',') + 1, input.indexOf(",", +1)).toFloat(); // find string between 2 commas
      input.remove(0, 5); //remove first comma and number
    }
  }
  else {
    Serial.write(0);
  }
}

void distanceToAngle() {
  for (int c = 1; c < 11; c++) {
    for (int r = 1; r < 11; r++) {
      angleArray[r][c] = map(distanceArray[r][c], 0, 4, 180, 0);
    }
  }
}

void loop() {
  for (int j = 0; j < 10; j++) {
    for (int i = 0; i < 10; i++) {
      Serial.write(1);
      delay(10);
      getInput();
    }
    distanceToAngle();
    for (int r = 0; r < 1; r++) {
      for (int c = 0; c < 1; c++) {
        servo1.write(angleArray[r][c]);
        servo2.write(angleArray[r][c]);
      }
    }
  }
}
