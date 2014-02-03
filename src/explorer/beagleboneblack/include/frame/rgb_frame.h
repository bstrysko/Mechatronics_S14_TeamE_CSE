#ifndef _EXPLORARE_FRAME_RGB_FRAME_H_
#define _EXPLORARE_FRAME_RGB_FRAME_H_

#include "frame.h"

#include <opencv2/opencv.hpp>

using namespace cv;

class RGBFrame : public Frame
{
  public:
    RGBFrame(Mat frame);
    ~RGBFrame();
};

#endif
