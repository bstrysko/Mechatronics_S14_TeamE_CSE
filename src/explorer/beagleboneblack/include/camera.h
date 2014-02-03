#ifndef _EXPLORARE_CAMERA_H_
#define _EXPLORARE_CAMERA_H_

#include "frame/rgb_frame.h"

#include <opencv2/opencv.hpp>

using namespace cv;

class Camera
{
  private:
    VideoCapture camera;
  public:
    Camera();
    ~Camera(); 

    RGBFrame getRGBFrame();
};

#endif
