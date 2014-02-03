#ifndef _EXPLORARE_DRIVE_SYSTEM_H_
#define _EXPLORARE_DRIVE_SYSTEM_H_

#include "i2c_device.h"
#include "i2c_bus.h"

#include <stdint.h>

class DriveSystem : I2CDevice
{
  private:
  public:
    DriveSystem(I2CBus* bus, uint8_t address);
    ~DriveSystem();

    //uint64_t getDistanceTraveled();
    //TODO: get orientation

    //TODO: figure out units of measurement
    //void driveForward(uint8_t cm);
    //void turn(short degrees);
};

#endif
