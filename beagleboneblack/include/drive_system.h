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
 * The DriveSystem class represents the
 * Drive System subsystem of the Explorer.
 *
 * Created On: 2/1/14
 */

#ifndef _EXPLORARE_DRIVE_SYSTEM_H_
#define _EXPLORARE_DRIVE_SYSTEM_H_

#include <I2CMaster/I2CDevice.h>
#include <I2CMaster/I2CBus.h>

#include <stdint.h>

#define DRIVE_SYSTEM_REGISTER_POSITION_WRITE 0x1
#define DRIVE_SYSTEM_REGISTER_POSITION_READ 0x2

class DriveSystem : I2CDevice
{
  public:
    DriveSystem(I2CBus* bus, uint8_t address);
    ~DriveSystem();

    void getPosition(float* x, float* y, float* angle);
    void setPosition(float x, float y);
};

#endif
