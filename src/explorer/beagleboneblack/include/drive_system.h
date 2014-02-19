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

    void moveStepper(int16_t degrees);

    void setDCMotor(bool continuous, int16_t degrees);

    //uint64_t getDistanceTraveled();
    //TODO: get orientation

    //TODO: figure out units of measurement
    //void driveForward(uint8_t cm);
    //void turn(short degrees);
};

#endif
