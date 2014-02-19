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
 * The Color class represents a 4 channel
 * color.
 *
 * Created On: 2/1/14
 */

#ifndef _EXPLORARE_COLOR_H_
#define _EXPLORARE_COLOR_H_

#include <stdint.h>

#include <iostream>

using namespace std;

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

    friend ostream& operator<<(ostream& os, const Color& color);
};

#endif
