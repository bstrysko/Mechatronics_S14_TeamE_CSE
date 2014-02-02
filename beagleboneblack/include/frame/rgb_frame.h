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
 * The RGBFrame class represents a
 * frame with RGB Color data.
 *
 * Created On: 2/1/14
 */

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
