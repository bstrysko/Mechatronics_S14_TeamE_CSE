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

void DriveSystem::getPosition(float* x, float* y, float* angle)
{
	float buffer[3];

	i2cRead(DRIVE_SYSTEM_REGISTER_POSITION_READ, (uint8_t*)buffer, 12);

	(*x) = buffer[0];
	(*y) = buffer[1];
	(*angle) = buffer[2];
}

void DriveSystem::setPosition(float x, float y)
{
	float buffer[2];
	buffer[0] = x;
	buffer[1] = y;

	i2cWrite(DRIVE_SYSTEM_REGISTER_POSITION_WRITE, (uint8_t*)buffer, 8);
}
