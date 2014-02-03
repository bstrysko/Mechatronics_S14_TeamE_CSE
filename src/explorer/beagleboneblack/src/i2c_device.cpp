#include "i2c_device.h"

I2CDevice::I2CDevice(I2CBus* bus, uint8_t address)
{
	this->bus = bus;
	this->address = address;
}

I2CDevice::~I2CDevice()
{

}

