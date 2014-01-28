#ifndef _EXPLORARE_COLOR_H_
#define _EXPLORARE_COLOR_H_

#include "types.h"

class Color
{
  private:
    uint8_t red, green, blue;
  public:
    Color(uint8_t red, uint8_t green, uint8_t blue);
    
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
};

#endif
