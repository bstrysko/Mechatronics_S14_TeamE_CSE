#include "explorer.h"

I2CBus* Explorer::i2cBus = 0;
DriveSystem* Explorer::driveSystem = 0;
RGBSensor* Explorer::rgbSensor = 0;
Camera* Explorer::camera = 0;

void Explorer::init()
{
	i2cBus = new I2CBus(I2C_BUS_NUMBER);
	driveSystem = new DriveSystem(i2cBus, DRIVE_SYSTEM_ADDRESS);
	rgbSensor = new RGBSensor(i2cBus, RGB_SENSOR_ADDRESS);
	camera = new Camera();
}

DriveSystem* Explorer::getDriveSystem()
{
	return driveSystem;
}

RGBSensor* Explorer::getRGBSensor()
{
	return rgbSensor;
}

Camera* Explorer::getCamera()
{
	return camera;
}
