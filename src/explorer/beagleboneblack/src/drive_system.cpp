#include <drive_system.h>

DriveSystem::DriveSystem(I2CBus* bus, uint8_t address) : I2CDevice(bus, address)
{
	this->servo_pos = 0;
}

DriveSystem::~DriveSystem()
{

}

uint8_t DriveSystem::getServoPos()
{
	return servo_pos;
}
    
void DriveSystem::setServoPos(uint8_t pos)
{
	this->servo_pos = pos;

	i2c_write(SERVO_REGISTER, &pos, 1);
}
