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
 * The Explorer class is a factory
 * that provides methods to obtain
 * instances of major Explorer subsystems.
 *
 * Created On: 2/1/14
 */

#ifndef _EXPLORARE_EXPLORER_H_
#define _EXPLORARE_EXPLORER_H_

#include <I2CMaster/I2CBus.h>

#include "drive_system.h"
#include "camera.h"

#include <RGBColorSensorArray/RGBColorSensorArray.h>

#define I2C_BUS_NUMBER 1
#define DRIVE_SYSTEM_ADDRESS 0x12
#define RGB_COLOR_SENSOR_ARRAY_ADDRESS 60

class Explorer
{
  private:
    static I2CBus* i2cBus;
    static DriveSystem* driveSystem;
    static RGBColorSensorArray* rgbColorSensorArray;
    static Camera* camera;
  public:
    static void init();
    static DriveSystem* getDriveSystem();
    static RGBColorSensorArray* getRGBColorSensorArray();
    static Camera* getCamera();
};

#endif
