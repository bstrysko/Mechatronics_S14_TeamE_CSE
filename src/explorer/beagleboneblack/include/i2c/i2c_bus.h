#ifndef _EXPLORARE_I2C_I2C_BUS_H_
#define _EXPLORARE_I2C_I2C_BUS_H_

#include <stdint.h>

class I2CBus
{
  private:
    uint32_t id;
  public:
    I2CBus(uint32_t id);
    ~I2CBus();

    uint32_t getID();
};

#endif
