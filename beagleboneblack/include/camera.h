/*
 * Mechatronics (Spring 2014)
 * Team Name: Explorare
 *
 * Team Member Names:
 * Brent Strysko
 * Wen Li
 * Caroline Colombo
 * Funan Ma
 * 
 * @author Brent Strysko
 *
 * The Camera class is a wrapper around
 * OpenCV's VideoStream functionality.
 *
 * Created On: 2/1/14
 */

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
