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
 * The TextFrame class represents a
 * frame with textual data.
 *
 * Created On: 2/1/14
 */

#ifndef _EXPLORARE_TEXT_FRAME_H_
#define _EXPLORARE_TEXT_FRAME_H_

#include "frame.h"

class TextFrame : public Frame
{
  public:
    TextFrame(Frame frame);
    ~TextFrame();
};

#endif
