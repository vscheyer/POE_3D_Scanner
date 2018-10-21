#include <Servo.h>

Servo pushServo0;
Servo pushServo1;
Servo pushServo2;
Servo pushServo3;
Servo pushServo4;
Servo pushServo5;
Servo pushServo6;
Servo pushServo7;
Servo pushServo8;
Servo pushServo9;

Servo lockServo0;
Servo lockServo1;
Servo lockServo2;
Servo lockServo3;
Servo lockServo4;
Servo lockServo5;
Servo lockServo6;
Servo lockServo7;
Servo lockServo8;
Servo lockServo9;

int distanceArray[10][10];
int servoAngleArray[10][10];

String input;
void setup() {
  pushServo0.attach(10);
  Serial.begin(9600);

}

void loop() {
  checkForInput();
  

}
void checkForInput(){
  while(Serial.available()>0){
    input = Serial.readString();
    Serial.println(input);
  }
    servoAngleArray[0][0] = input.toInt();
    updateModel();
  
}

void updateModel(){
  convertDistanceToServoAngle();
  for(int row = 0; row<10; row++){
      moveToRow(row);
      delay(20);
      setHeightToRow(row);
  }
}
void setHeightToRow(int row){
  Serial.print("Set height to row");
  Serial.println(row);
pushServo0.write(servoAngleArray[row][0]);
pushServo1.write(servoAngleArray[row][1]);
pushServo2.write(servoAngleArray[row][2]);
pushServo3.write(servoAngleArray[row][3]);
pushServo4.write(servoAngleArray[row][4]);
pushServo5.write(servoAngleArray[row][5]);
pushServo6.write(servoAngleArray[row][6]);
pushServo7.write(servoAngleArray[row][7]);
pushServo8.write(servoAngleArray[row][8]);
pushServo9.write(servoAngleArray[row][9]);
}
void convertDistanceToServoAngle(){
  for(int i = 0; i<10; i++){
    for(int j = 0; j<10; j++){
      int distance = distanceArray[i][j];
      servoAngleArray[i][j]=map(distance,40,100,0,180);
      
    }
  }
}
void moveToRow(int row){
  //move the stepper motor to go to a certain row
}
