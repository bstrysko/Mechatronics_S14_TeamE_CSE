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
 * The ThreshFrame class represents a
 * frame whose data has been thresholded.
 *
 * Created On: 2/1/14
 */

#ifndef _EXPLORARE_FRAME_THRESH_FRAME_H_
#define _EXPLORARE_FRAME_THRESH_FRAME_H_

#include "frame.h"
#include "rgb_frame.h"
#include "hsv_frame.h"

class ThreshFrame : public Frame
{
  private:
    Mat singleChannelMat;
    ThreshFrame(Mat m, Scalar lowBound, Scalar highBound);

  public:
    ThreshFrame(RGBFrame frame, Scalar lowBound, Scalar highBound);
    ThreshFrame(HSVFrame frame, Scalar lowBound, Scalar highBound);
    ~ThreshFrame();

    Mat getSingleChannelMat();
};

#endif
