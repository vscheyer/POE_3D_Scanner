#include <Servo.h>
#include <FileIO.h>

Servo pushServo0;

int distanceArray[10][10];
int servoAngleArray[10][10];

String input;
  void setup() {
  pushServo0.attach(10);
  Serial.begin(9600);
  
  for (int i=0; i<9; i++) {
    for (int k=0; k<9; k++) {
      distanceArray[i][k] = random(1,5);
      Serial.println(distanceArray[i][k]);
      convertDistanceToServoAngle();
    }
  }
}

void loop() {
  updateModel();

}

void convertDistanceToServoAngle(){
//  Serial.println("Here are the angles");
  for(int i=0; i<10; i++){
    for(int j=0; j<10; j++){
      int distance = distanceArray[i][j];
      distance = map(distance,1,4,0,180);
      servoAngleArray[i][j]= distance;
//      Serial.println(servoAngleArray[i][j]);
    }
  }
}

void updateModel(){
  for (int i=0; i<10; i++) {
    for (int j=0; j<10; j++) {
      pushServo0.write(servoAngleArray[i][j]);
      delay(1000);
    }
  }
}
