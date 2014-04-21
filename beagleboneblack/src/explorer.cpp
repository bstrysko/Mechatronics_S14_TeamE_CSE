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
 * Implementation of Explorer class.
 *
 * Created On: 2/1/14
 */

#include "explorer.h"

I2CBus* Explorer::i2cBus = 0;
DriveSubsystem* Explorer::driveSubsystem = 0;
RGBColorSensorArray* Explorer::rgbColorSensorArray = 0;
Camera* Explorer::camera = 0;

void Explorer::initEarly()
{
	i2cBus = new I2CBus(I2C_BUS_NUMBER);

	driveSubsystem = new DriveSubsystem(i2cBus, DRIVE_SUBSYSTEM_ADDRESS);

	rgbColorSensorArray = new RGBColorSensorArray(i2cBus, RGB_COLOR_SENSOR_ARRAY_ADDRESS);
	LEDState s = ENABLED;
	rgbColorSensorArray->setLED0State(s);
	rgbColorSensorArray->setLED1State(s);
	rgbColorSensorArray->setLED2State(s);
	rgbColorSensorArray->enable();
}

void Explorer::init()
{
	initEarly();
	camera = new Camera();
}

void Explorer::init(Size cameraSize)
{
	initEarly();
	camera = new Camera(cameraSize);
}

Explorer::~Explorer()
{
	delete camera;
	delete rgbColorSensorArray;
	delete driveSubsystem;
	delete i2cBus;
}

DriveSubsystem* Explorer::getDriveSubsystem()
{
	return driveSubsystem;
}

RGBColorSensorArray* Explorer::getRGBColorSensorArray()
{
	return rgbColorSensorArray;
}

Camera* Explorer::getCamera()
{
	return camera;
}
