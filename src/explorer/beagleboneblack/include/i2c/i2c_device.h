#ifndef _EXPLORARE_I2C_I2C_DEVICE_H_
#define _EXPLORARE_I2C_I2C_DEVICE_H_

#include "i2c_bus.h"

#include <iostream>
#include <exception>
#include <sstream>
#include <string>

#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <unistd.h>

using namespace std;

class I2CDevice
{
  private:
    I2CBus* bus;
    int fd;
    uint8_t address;

    void setRegister(uint8_t reg);

//  protected:
  public:
    I2CDevice(I2CBus* bus, uint8_t address);

    void i2c_read(uint8_t reg, uint8_t* buffer, size_t buffer_size);
    void i2c_write(uint8_t reg, uint8_t* buffer, size_t buffer_size);
  public:
    ~I2CDevice();
};

#endif
