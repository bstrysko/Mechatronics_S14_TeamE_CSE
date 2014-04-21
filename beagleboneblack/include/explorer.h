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
#include <DriveSubsystem/DriveSubsystem.h>
#include <VisualCSEDefectDetector/Camera.h>

#include <RGBColorSensorArray/RGBColorSensorArray.h>

#define I2C_BUS_NUMBER 1
#define DRIVE_SUBSYSTEM_ADDRESS 18
#define RGB_COLOR_SENSOR_ARRAY_ADDRESS 60

class Explorer
{
  private:
    static I2CBus* i2cBus;
    static DriveSubsystem* driveSubsystem;
    static RGBColorSensorArray* rgbColorSensorArray;
    static Camera* camera;
    static void initEarly();
  public:
    static void init();
    static void init(Size size);
    ~Explorer();
    static DriveSubsystem* getDriveSubsystem();
    static RGBColorSensorArray* getRGBColorSensorArray();
    static Camera* getCamera();
};

#endif
