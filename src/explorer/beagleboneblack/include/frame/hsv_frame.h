#ifndef _EXPLORARE_FRAME_HSV_FRAME_H_
#define _EXPLORARE_FRAME_HSV_FRAME_H_

#include "frame.h"
#include "rgb_frame.h"

class HSVFrame : public Frame
{
  public:
    HSVFrame(RGBFrame frame);
    ~HSVFrame();
};

#endif
