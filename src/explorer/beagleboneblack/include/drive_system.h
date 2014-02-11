#ifndef _EXPLORARE_DRIVE_SYSTEM_H_
#define _EXPLORARE_DRIVE_SYSTEM_H_

#include "i2c/i2c_device.h"
#include "i2c/i2c_bus.h"

#include <stdint.h>

#define REGISTER_SERVO 1
#define REGISTER_DC_MOTOR 2
#define REGISTER_STEPPER_MOTOR 3
#define REGISTER_POT 10
#define REGISTER_IR_SENSOR 11
#define REGISTER_SWITCH 12

class DriveSystem : I2CDevice
{
  public:
    DriveSystem(I2CBus* bus, uint8_t address);
    ~DriveSystem();

    uint8_t getPotPos();
    bool getIRSensor();
    bool getSwitch();

    uint8_t getServoPos();
    void setServoPos(uint8_t pos);

    void moveStepper(bool forward, uint8_t degrees);

    //uint64_t getDistanceTraveled();
    //TODO: get orientation

    //TODO: figure out units of measurement
    //void driveForward(uint8_t cm);
    //void turn(short degrees);
};

#endif
