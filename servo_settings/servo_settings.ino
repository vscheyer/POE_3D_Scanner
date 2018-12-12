/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

//Servo myservo1;  // create servo object to control a servo
//Servo myservo2;
//Servo myservo3;
//Servo myservo4;
//Servo myservo5;
//Servo myservo6;
//Servo myservo7;
//Servo myservo8;
//Servo myservo9;
//Servo myservo10;
Servo myservo11;  // create servo object to control a servo
Servo myservo12;
Servo myservo13;
Servo myservo14;
Servo myservo15;
Servo myservo16;
Servo myservo17;
Servo myservo18;
Servo myservo19;
Servo myservo20;
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
//  myservo1.attach(24);  // attaches the servo on pin 9 to the servo object
//  myservo2.attach(25);
//  myservo3.attach(26);
//  myservo4.attach(27);
//  myservo5.attach(28);
//  myservo6.attach(29);
//  myservo7.attach(30);
//  myservo8.attach(31);
//  myservo9.attach(32);
//  myservo10.attach(33);
  myservo11.attach(34);  // attaches the servo on pin 9 to the servo object
  myservo12.attach(35);
  myservo13.attach(36);
  myservo14.attach(37);
  myservo15.attach(38);
  myservo16.attach(39);
  myservo17.attach(40);
  myservo18.attach(41);
  myservo19.attach(42);
  myservo20.attach(43);
}

void loop() {
  for (pos = 70; pos <= 100; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo2.write(pos);
//    myservo3.write(pos);
//    myservo4.write(pos);
//    myservo5.write(pos);
//    myservo6.write(pos);
//    myservo7.write(pos);
//    myservo8.write(pos);
//    myservo9.write(pos);
//    myservo10.write(pos);
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    myservo12.write(pos);
    myservo13.write(pos-20);
    myservo14.write(pos-20);
    myservo15.write(pos+20);
    myservo16.write(pos+20);
    myservo17.write(pos-20);
    myservo18.write(pos-30);
    myservo19.write(pos-30);
    myservo20.write(pos-30);
    delay(40);                       // waits 15ms for the servo to reach the position
  }

  for (pos = 100; pos >= 70; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    myservo2.write(pos);
//    myservo3.write(pos);
//    myservo4.write(pos);
//    myservo5.write(pos);
//    myservo6.write(pos);
//    myservo7.write(pos);
//    myservo8.write(pos);
//    myservo9.write(pos);
//    myservo10.write(pos);              // tell servo to go to position in variable 'pos'
    myservo11.write(pos);              // tell servo to go to position in variable 'pos'
    myservo12.write(pos);
    myservo13.write(pos-20);
    myservo14.write(pos-20);
    myservo15.write(pos+20);
    myservo16.write(pos+20);
    myservo17.write(pos-20);
    myservo18.write(pos-30);
    myservo19.write(pos-30);
    myservo20.write(pos-30);
    delay(40);                       // waits 15ms for the servo to reach the position
  }

}
