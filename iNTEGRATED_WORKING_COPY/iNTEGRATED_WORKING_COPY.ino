#include <Servo.h>

//KINECT INTEGRATION VARS
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

//SERVO CONTROL VARS
float distanceArray[10][10]; //for 2x2 matrix of blocks
int angleArray[10][10];
int rowCounter = 0;
int lockPos = 50;
int unlockPos = 0;

boolean systemDone;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo lockServo1;
Servo lockServo2;
Servo lockServo3;
Servo lockServo4;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
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
  if (stringComplete) {
    // clear the string:

    for (int c = 0; c < 10; c++) {
      distanceArray[rowCounter][c] = inputString.substring(inputString.indexOf(',') + 1, inputString.indexOf(",", +1)).toFloat(); // find string between 2 commas
      inputString.remove(0, 5); //remove first comma and number
    }

    inputString = "";
    stringComplete = false;
    rowCounter++;
    if (rowCounter == 10) rowCounter = 1;
    Serial.print(char(rowCounter));
  }
}

void writeToServos() {
  if (rowCounter >= 10) {
    for (int r = 0; r < 4; r++) {
      for (int c = 0; c < 1; c++) {
        servo1.write(angleArray[r][c]);
        servo2.write(angleArray[r][c]);
        servo3.write(angleArray[r][c]);
        servo4.write(angleArray[r][c]);
      }
      if (r == 0) lockServo1.write(lockPos);
      if (r == 1) lockServo2.write(lockPos);
      if (r == 2) lockServo3.write(lockPos);
      if (r == 3) lockServo4.write(lockPos);
      resetBlocks();
    }
    delay(2000);
  }
}

void distanceToAngle() {
  for (int c = 1; c < 11; c++) {
    for (int r = 1; r < 11; r++) {
      angleArray[r][c] = map(distanceArray[r][c], 0, 4, 180, 0);
    }
  }
}

void resetBlocks() {
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
}

void loop() {
  // print the string when a newline arrives:

  getInput();

  distanceToAngle();

  writeToServos();
}
