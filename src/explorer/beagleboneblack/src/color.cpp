#include <color.h>

Color Color::RED = Color(255, 0, 0);
Color Color::GREEN = Color(0, 255, 0);
Color Color::BLUE = Color(0, 0, 255);

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : Color(red, green, blue, 0)
{
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

Color::~Color()
{
}

uint8_t Color::getRed()
{
	return red;
}

uint8_t Color::getGreen()
{
	return green;
}

uint8_t Color::getBlue()
{
	return blue;
}

uint8_t Color::getAlpha()
{
	return alpha;
}

ostream& operator<<(ostream& os, const Color& color)
{
	return os << "(" << (int)color.red << ", " <<
		(int)color.green << ", " << (int)color.blue << ", " <<
		(int)color.alpha << ")";
}
