#ifndef _EXPLORARE_EXPLORER_H_
#define _EXPLORARE_EXPLORER_H_

#include <I2CMaster/I2CBus.h>

#include "drive_system.h"
#include "rgb_sensor.h"
#include "camera.h"

#define I2C_BUS_NUMBER 1
#define DRIVE_SYSTEM_ADDRESS 0x12

class Explorer
{
  private:
    static I2CBus* i2cBus;
    static DriveSystem* driveSystem;
    static RGBSensor* rgbSensor;
    static Camera* camera;
  public:
    static void init();
    static DriveSystem* getDriveSystem();
    static RGBSensor* getRGBSensor();
    static Camera* getCamera();
};

#endif
