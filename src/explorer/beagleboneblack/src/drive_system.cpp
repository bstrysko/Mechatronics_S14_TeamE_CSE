#include <drive_system.h>

DriveSystem::DriveSystem(I2CBus* bus, uint8_t address) : I2CDevice(bus, address)
{
}

DriveSystem::~DriveSystem()
{

}

uint8_t DriveSystem::getPotPos()
{
	uint8_t potPos;
	i2c_read(REGISTER_POT, &potPos, 1);
	return potPos;
}
   
bool DriveSystem::getIRSensor()
{
	uint8_t v;
	i2c_read(REGISTER_IR_SENSOR, &v, 1);
	return (v) ? true : false;
}

bool DriveSystem::getSwitch()
{
	uint8_t v;
	i2c_read(REGISTER_SWITCH, &v, 1);
	return (v) ? true : false;
}

uint8_t DriveSystem::getServoPos()
{
	uint8_t servoPos;
	i2c_read(REGISTER_SERVO, &servoPos, 1);
	return servoPos;
}
    
void DriveSystem::setServoPos(uint8_t pos)
{
	i2c_write(REGISTER_SERVO, &pos, 1);
}

void DriveSystem::moveStepper(bool forward, uint8_t degrees)
{
	uint8_t d = forward ? 0x80 : 0x0;
	uint8_t v = d | degrees;
	i2c_write(REGISTER_STEPPER_MOTOR, &v, 1);
}

