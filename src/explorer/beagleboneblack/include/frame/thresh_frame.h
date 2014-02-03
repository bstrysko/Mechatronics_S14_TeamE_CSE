#ifndef _EXPLORARE_FRAME_THRESH_FRAME_H_
#define _EXPLORARE_FRAME_THRESH_FRAME_H_

#include "frame.h"
#include "hsv_frame.h"

class ThreshFrame : public Frame
{
  public:
    ThreshFrame(HSVFrame frame);
    ~ThreshFrame();
};

#endif
