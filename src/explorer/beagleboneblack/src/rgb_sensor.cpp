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
 * Implementation of RGBSensor class.
 *
 * Created On: 2/1/14
 */

#include "rgb_sensor.h"

RGBSensor::RGBSensor(I2CBus* bus) : I2CDevice(bus, RGB_SENSOR_ADDRESS)
{
	uint8_t id = getID();

	if(id != 0x44)
	{
		throw ios_base::failure("Cannot connect to RGBSensor");
	}

	enable();
}

RGBSensor::~RGBSensor()
{
}

void RGBSensor::enable()
{
	uint8_t v = RGB_SENSOR_ENABLE_PON;
	i2cWrite(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_ENABLE, &v, 1);
	usleep(3);
	v |= RGB_SENSOR_ENABLE_AEN;
	i2cWrite(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_ENABLE, &v, 1);
}

uint8_t RGBSensor::getID()
{
	uint8_t id;
	i2cRead(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_ID, &id, 1);
	return id;
}

void RGBSensor::setIntegrationTime(RGBSensorIntegrationTime t)
{
	i2cWrite(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_ATIME, (uint8_t*)(&t), 1);
}

void RGBSensor::setGain(RGBSensorGain g)
{
	i2cWrite(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_CONTROL, (uint8_t*)(&g), 1);
}

Color RGBSensor::getColor()
{
	uint8_t c, r, g, b;
	
	i2cRead(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_CDATAL, ((uint8_t*)&c), 1);
	i2cRead(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_RDATAL, ((uint8_t*)&r), 1);
	i2cRead(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_GDATAL, ((uint8_t*)&g), 1);
	i2cRead(RGB_SENSOR_COMMAND_BIT | RGB_SENSOR_REGISTER_BDATAL, ((uint8_t*)&b), 1);
	
	return Color(r, g, b, c);
}
