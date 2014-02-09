#include <i2c/i2c_device.h>

I2CDevice::I2CDevice(I2CBus* b, uint8_t address)
{
	this->bus = b;
	this->address = address;

	ostringstream filename_s;
	filename_s << "/dev/i2c-" << bus->getID();
	string filename(filename_s.str());

	this->fd = open(filename.c_str(), O_RDWR);

	if(this->fd < 0)
	{
		throw ios_base::failure(string("Cannot not open ") + filename.c_str());
	}

	int res;
	
	res = ioctl(this->fd, I2C_SLAVE, address);

	if(res < 0)
	{
		stringstream o;
		o << "Cannot set bus " << filename;
		o << " to slave address " << (int)address;
		throw ios_base::failure(o.str());
	}
}

I2CDevice::~I2CDevice()
{

}

void I2CDevice::setRegister(uint8_t reg)
{
	char buffer[1];
	buffer[0] = reg;

	if(write(fd, buffer, 1) != 1)
	{
		stringstream o;
		o << "Cannot set device to register " << (int)reg;
		throw ios_base::failure(o.str());
	}
}

void I2CDevice::i2c_read(uint8_t reg, uint8_t* buffer, size_t buffer_size)
{
	setRegister(reg);

	if(read(fd, buffer, buffer_size) != buffer_size)
	{
		stringstream o;
		o << "Cannot read from register " << (int)reg;
		throw ios_base::failure(o.str());
	}
}

void I2CDevice::i2c_write(uint8_t reg, uint8_t* buffer, size_t buffer_size)
{
	throw ios_base::failure("I2CDevice write currently unimplemented");
}
