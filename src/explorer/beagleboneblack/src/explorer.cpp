#include <explorer.h>

void Explorer::init()
{
	i2cBus = new I2CBus(I2C_BUS_NUMBER);	
}

DriveSystem* Explorer::getDriveSystem()
{
	if(!driveSystem)
	{
		driveSystem = new DriveSystem(i2cBus, DRIVE_SYSTEM_ADDRESS);
	}
	
	return driveSystem;
}

RGBSensor* Explorer::getRGBSensor()
{
	if(!rgbSensor)
	{
		rgbSensor = new RGBSensor(i2cBus, RGB_SENSOR_ADDRESS);
	}

	return rgbSensor;
}

Camera* Explorer::getCamera()
{
	if(!camera)
	{
		camera = new Camera();
	}

	return camera;
}
