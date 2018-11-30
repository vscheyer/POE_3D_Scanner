/*
  Serial Event example
   When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.
   A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.
   NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.
   created 9 May 2011
  by Tom Igoe
   This example code is in the public domain.
   http://www.arduino.cc/en/Tutorial/SerialEvent
*/
#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo lockServo1;
Servo lockServo2;
Servo lockServo3;
Servo lockServo4;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int rowCounter = 0;

int lockPos = 50;
int unlockPos = 0;

float distanceArray[10][10];
int angleArray[10][10];

void setup() {
  // initialize serial:
  Serial.begin(9600);
  servo1.attach(30);
  servo2.attach(31);
  servo3.attach(32);
  servo4.attach(33);
  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);
  
  lockServo1.attach(22);
  lockServo2.attach(23);
  lockServo3.attach(24);
  lockServo4.attach(25);
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
      delay(1000);

      if (r == 0) lockServo1.write(lockPos);
      if (r == 1) lockServo2.write(lockPos);
      if (r == 2) lockServo3.write(lockPos);
      if (r == 3) lockServo4.write(lockPos);
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
  }
  int ourMap(float value,long in_min, long in_max, long out_min, long out_max){
    return (int)(value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
