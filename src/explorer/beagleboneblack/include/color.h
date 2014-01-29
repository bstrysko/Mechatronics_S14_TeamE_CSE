#ifndef _EXPLORARE_COLOR_H_
#define _EXPLORARE_COLOR_H_

#include "types.h"

class Color
{
  private:
    uint8_t alpha, red, green, blue;
  public:
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
    ~Color();

    uint8_t getAlpha();
    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
};

#endif
