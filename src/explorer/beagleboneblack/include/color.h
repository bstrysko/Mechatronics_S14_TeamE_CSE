#ifndef _EXPLORARE_COLOR_H_
#define _EXPLORARE_COLOR_H_

#include <stdint.h>

class Color
{
  private:
    uint8_t red, green, blue, alpha;
  public:
    Color(uint8_t red, uint8_t green, uint8_t blue);
    Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
    ~Color();

    uint8_t getRed();
    uint8_t getGreen();
    uint8_t getBlue();
    uint8_t getAlpha();

    static Color RED;
    static Color GREEN;
    static Color BLUE;
};

#endif
