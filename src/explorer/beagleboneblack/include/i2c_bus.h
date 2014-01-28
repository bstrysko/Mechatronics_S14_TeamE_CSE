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
};

#endif
