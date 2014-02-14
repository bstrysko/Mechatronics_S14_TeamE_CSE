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
	i2cRead(REGISTER_POT, &potPos, 1);
	return potPos;
}
   
bool DriveSystem::getIRSensor()
{
	uint8_t v;
	i2cRead(REGISTER_IR_SENSOR, &v, 1);
	return (v) ? true : false;
}

bool DriveSystem::getSwitch()
{
	uint8_t v;
	i2cRead(REGISTER_SWITCH, &v, 1);
	return (v) ? true : false;
}

uint8_t DriveSystem::getServoPos()
{
	uint8_t servoPos;
	i2cRead(REGISTER_SERVO, &servoPos, 1);
	return servoPos;
}
    
void DriveSystem::setServoPos(uint8_t pos)
{
	i2cWrite(REGISTER_SERVO, &pos, 1);
}

void DriveSystem::moveStepper(int16_t degrees)
{
	i2cWrite(REGISTER_STEPPER_MOTOR, (uint8_t*)(&degrees), 2);
}

void DriveSystem::setDCMotor(bool continuous, int16_t degrees)
{
	uint8_t buf[3];
	buf[0] = (continuous) ? 0x1 : 0x0;
	buf[1] = (int8_t)((degrees) >> 8);
	buf[2] = ((int8_t)(degrees));
	i2cWrite(REGISTER_DC_MOTOR, buf, 3);
}

