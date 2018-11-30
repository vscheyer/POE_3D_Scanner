#include <Servo.h>
#include <Stepper.h>

#define stp 2
#define dir 3
#define MS1 4
#define MS2 5
#define EN  6

//KINECT INTEGRATION VARS
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

//SERVO CONTROL VARS
float distanceArray[10][10]; //for 2x2 matrix of blocks
int angleArray[10][10];
int rowCounter = 0;
int lockPos = 50;
int unlockPos = 0;

//STEPPER CONTROL VARS
int currentStep = 0;
char user_input;

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
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(EN, OUTPUT);
  resetEDPins(); //Set step, direction, microstep and enable pins to default states
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

//void serialEvent() {
//  while (Serial.available() > 0) {
//    //    inputString = Serial.read();
//    // get the new byte:
//    char inChar = (char)Serial.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag so the main loop can
//    // do something about it:
//    if (inChar == 'A') {
//      stringComplete = true;
//    }
//  }
//}

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
    }
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
  lockServo1.write(unlockPos);
  lockServo2.write(unlockPos);
  lockServo3.write(unlockPos);
  lockServo4.write(unlockPos);
}


void stepForward(int steps) {
  Serial.print("Moving forward ");
  Serial.println(steps);
  digitalWrite(dir, LOW); //Pull direction pin low to move "forward"
  for ( int j = 1; j < steps; j++) { //Loop the forward stepping enough times for motion to be visible
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(2);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(2);
    currentStep = currentStep + 1;
  }
}

void stepBackward(int steps)
{
  Serial.print("Moving backward ");
  Serial.println(steps);
  digitalWrite(dir, HIGH); //Pull direction pin low to move "forward"
  for ( int j = 1; j < steps; j++) { //Loop the forward stepping enough times for motion to be visible
    digitalWrite(stp, HIGH); //Trigger one step forward
    delay(5);
    digitalWrite(stp, LOW); //Pull step pin low so it can be triggered again
    delay(5);
    currentStep = currentStep - 1;
  }
}

void moveToRow(int row) {
  Serial.print("move to row: ");
  Serial.println(row);
  if (row * 190 > currentStep) {
    int stepsToMove = row * 190 - currentStep;
    stepForward(stepsToMove);
  }
  if (row * 190 < currentStep) {
    int stepsToMove = currentStep - row * 190;
    stepBackward(stepsToMove);
  }
}

void resetEDPins()
{
  digitalWrite(stp, LOW);
  digitalWrite(dir, LOW);
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(EN, HIGH);
}

void loop() {
  // print the string when a newline arrives:
  while (Serial.available()) {
    user_input = Serial.read(); //Read user input and trigger appropriate function
    Serial.println(user_input);
    digitalWrite(EN, LOW); //Pull enable pin low to allow motor control
    moveToRow(user_input - '0');
    resetEDPins();

  }
  getInput();

  distanceToAngle();

  writeToServos();
}
