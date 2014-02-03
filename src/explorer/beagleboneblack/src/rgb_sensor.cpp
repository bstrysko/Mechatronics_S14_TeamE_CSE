#include "rgb_sensor.h"

RGBSensor::RGBSensor(I2CBus* bus, uint8_t address) : I2CDevice(bus, address)
{
	
}

RGBSensor::~RGBSensor()
{

}
