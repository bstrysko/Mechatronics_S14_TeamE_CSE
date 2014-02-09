#include <i2c/i2c_bus.h>

I2CBus::I2CBus(uint32_t id)
{
	this->id = id;
}

I2CBus::~I2CBus()
{

}

uint32_t I2CBus::getID()
{
	return id;
}
