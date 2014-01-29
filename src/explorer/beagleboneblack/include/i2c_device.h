#ifndef _EXPLORARE_I2C_DEVICE_H_
#define _EXPLORARE_I2C_DEVICE_H_

#include "i2c_bus.h"
#include "types.h"

class I2CDevice
{
  private:
    I2CBus* bus;
    uint8_t address;
  protected:
    I2CDevice(I2CBus* bus, uint8_t address);
    ~I2CDevice();
};

#endif
