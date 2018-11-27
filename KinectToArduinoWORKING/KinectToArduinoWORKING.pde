import kinect4WinSDK.Kinect;
import kinect4WinSDK.SkeletonData;
import processing.serial.*;

Serial myPort;  // Create object from Serial class

Kinect kinect;
int[] screensize = {640, 480};
float[][] distanceArray = new float[10][10];
String sendString;
int inByte;

void setup()
{
  size(640, 480);
  background(0);
  kinect = new Kinect(this);
  smooth();
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  background(0);
  PImage depthArray = kinect.GetDepth();
  depthArray.loadPixels();

  println("new deptharray loaded");
  //make a 10X10 matrix that contains floats from 0-4
  for (int y=50; y<430; y=y+38) {
    for (int x =145; x< 515; x=x+37) {
      int oneDepth256 = int(blue(depthArray.pixels[x+y*width]));
      float oneDepth4 = map(oneDepth256, 0, 256, 0, 4);
      distanceArray[(x-145)/38][(y-50)/37] = oneDepth4;
    }
  }
  println("full distancearray loaded");
  image(kinect.GetImage(), 0, 0, 640, 480);
  noStroke();
  rect(145, 50, 10, 10);
  rect(145+37, 50, 10, 10);
  rect(145, 50+38, 10, 10);
  rect(145+37, 50+38, 10, 10);
  
  delay(1000);
}

void keyPressed() {
  println("keyPressed opened");
  if (key == 10) { //key 10 = ENTER
    sendRow(0);
  }
}

void sendRow(int rowToSend) {
  for (int i = 0; i < 10; i++) {
    //print(nfc(distanceArray[rowToSend][i],2)+" ");
    sendString = sendString + ',' + nfc(distanceArray[rowToSend][i],2);
  }
  sendString= sendString + "A";
  println();
 
  print(sendString);
  myPort.write(sendString);
  println(" :sendString sent");
  sendString = "";
}

void serialEvent(Serial myPort){
  inByte = myPort.read();
  delay(1000);
  println("This is what the arduino sent back: "+inByte);
  if (inByte <9){
    sendRow(inByte);
    inByte = 100;
  }
}
