#include "I2CDevice.h"

#include <Wire.h>

bool I2CDevice::is_write = false;
byte I2CDevice::reg = 0;
byte I2CDevice::buffer[BUFFER_SIZE];
byte I2CDevice::buffer_size = 0;
i2c_read_func I2CDevice::_read_func = 0;
i2c_write_func I2CDevice::_write_func = 0;

void I2CDevice::request()
{
	byte read_buffer[BUFFER_SIZE];
	byte n = _read_func(I2CDevice::reg, read_buffer);
	Wire.write(read_buffer, n);
}

void I2CDevice::receive(int count)
{
	byte temp = Wire.read();
    is_write = !(!(temp & 0x80));
	reg = (temp & ~0x80);
  
	int i = 0;
  
	while(Wire.available())
	{
		buffer[i] = Wire.read();
		i++;
	}

	buffer_size = i;
  
	if(is_write)
	{
		_write_func(reg, buffer, buffer_size);
	}
}

void I2CDevice::init(byte address,
	i2c_read_func read_func, i2c_write_func write_func)
{
	_read_func = read_func;
	_write_func = write_func;

	Wire.begin(address);
	Wire.onRequest(I2CDevice::request);
	Wire.onReceive(I2CDevice::receive);
}
