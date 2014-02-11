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
