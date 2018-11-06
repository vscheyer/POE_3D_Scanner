import kinect4WinSDK.Kinect;
import kinect4WinSDK.SkeletonData;

Kinect kinect;
ArrayList <SkeletonData> bodies;
int[] screensize = {640,480};

void setup()
{
  size(640, 480);
  background(0);
  kinect = new Kinect(this);
  smooth();
  bodies = new ArrayList<SkeletonData>();
}

void draw()
{
  background(0);
  PImage depthArray = kinect.GetDepth();
  depthArray.loadPixels();
  println(brightness(depthArray.pixels[320+screensize[0]*240]));
  //for (int x = 0; x < width; x++) {
  //// Loop through every pixel row
  //for (int y = 0; y < height; y++) {
  //  // Use the formula to find the 1D location
  //  int loc = x + y * width;
  //  print(pixels[loc]);
  //}
  //}
  image(kinect.GetImage(), 0, 0, 640, 480);
  noStroke();
  rect(320,240,10,10);
  delay(1000);

  for (int y=120; y<360; y=y+640){
    for (int x =0; x< 320; x++){
      
      
 
    }
  }
}
