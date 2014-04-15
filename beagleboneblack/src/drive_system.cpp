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
 * Implementation of DriveSystem class.
 *
 * Created On: 2/1/14
 */

#include <drive_system.h>

DriveSystem::DriveSystem(I2CBus* bus, uint8_t address) : I2CDevice(bus, address)
{
}

DriveSystem::~DriveSystem()
{
}

void DriveSystem::getPosition(float* x, float* y)
{
	uint8_t buffer[2];
	i2cRead(DRIVE_SYSTEM_REGISTER_POSITION, buffer, 2);

	(*x) = (float)buffer[0];
	(*y) = (float)buffer[1];
}

float DriveSystem::getAngle()
{
	uint8_t v;

	i2cRead(DRIVE_SYSTEM_REGISTER_ANGLE, &v, 1);

	return (float)v;
}

void DriveSystem::setPosition(float x, float y)
{
	uint8_t buffer[2];

	buffer[0] = (uint8_t)x;
	buffer[1] = (uint8_t)y;

	i2cWrite(DRIVE_SYSTEM_REGISTER_POSITION, buffer, 2);
}
