#ifndef _EXPLORARE_I2C_BUS_H_
#define _EXPLORARE_I2C_BUS_H_

#include "types.h"

class I2CBus
{
  private:
    int fd;
  public:
    I2CBus(uint8_t busNumber);
    ~I2CBus();

    size_t read(uint8_t address, uint8_t register, uint8_t* buf, size_t buf_size);
    size_t write(uint8_t address, uint8_t register, uint8_t* buf, size_t buf_size);
};

#endif
