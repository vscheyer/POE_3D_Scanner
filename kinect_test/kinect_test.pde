import KinectPV2.*;
import kinect4WinSDK.*;
import org.openkinect.freenect.*;
import org.openkinect.processing.*;
import kinect4WinSDK.Kinect;

Kinect kinect;

void setup()
{
  size(640, 480);
  background(0);
  kinect = new Kinect(this);
  smooth();
}

void draw()
{
  background(0);
  image(kinect.GetImage(), 320, 0, 320, 240);
  image(kinect.GetDepth(), 320, 240, 320, 240);
  image(kinect.GetMask(), 0, 240, 320, 240);
}
