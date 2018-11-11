import kinect4WinSDK.Kinect;
import kinect4WinSDK.SkeletonData;
import processing.serial.*;

Serial myPort;  // Create object from Serial class

Kinect kinect;
int[] screensize = {640,480};
float[][] distanceArray = new float[10][10];

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
  
  for (int y=50; y<430; y=y+38){
    for (int x =145; x< 515; x=x+37){
      int oneDepth256 = int(blue(depthArray.pixels[x+y*width]));
      float oneDepth4 = map(oneDepth256,0,256,0,4);
      distanceArray[(x-145)/38][(y-50)/37] = oneDepth4;
    }
  }
  println("full distancearray loaded");
  
  for(int i = 0;i<2;i++){
    String sendString =','+ str(i) + ',';
    println("sendString initalized");
    for(int j = 0;j<2;j++){
      sendString = sendString + nf(distanceArray[j][i],1,2)+',';
      println("added new value to the sendString");
      //print(distanceArray[j][i]," ");
    }
    while(myPort.read()!=1){
      delay(1);
      println("waiting for arduino to send 1");
    }
    println(sendString);
    myPort.write(sendString);
    println("sendString sent");
  }
  
  
  print("\n");
  image(kinect.GetImage(), 0, 0, 640, 480);
  noStroke();
  rect(145,50,10,10);
  rect(145+37,50,10,10);
  rect(145,50+38,10,10);
  rect(145+37,50+38,10,10);

}
