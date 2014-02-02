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
 * The HSVFrame class represents a
 * frame with HSV Color data.
 *
 * Created On: 2/1/14
 */

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
