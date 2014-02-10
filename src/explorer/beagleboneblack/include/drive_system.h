#ifndef _EXPLORARE_DRIVE_SYSTEM_H_
#define _EXPLORARE_DRIVE_SYSTEM_H_

#include "i2c/i2c_device.h"
#include "i2c/i2c_bus.h"

#include <stdint.h>

#define SERVO_REGISTER 0x01

class DriveSystem : I2CDevice
{
  private:
    uint8_t servo_pos;
  public:
    DriveSystem(I2CBus* bus, uint8_t address);
    ~DriveSystem();

    uint8_t getServoPos();
    void setServoPos(uint8_t pos);

    //uint64_t getDistanceTraveled();
    //TODO: get orientation

    //TODO: figure out units of measurement
    //void driveForward(uint8_t cm);
    //void turn(short degrees);
};

#endif
