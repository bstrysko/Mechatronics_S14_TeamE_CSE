#ifndef _EXPLORARE_RGB_SENSOR_H_
#define _EXPLORARE_RGB_SENSOR_H_

#include "i2c_device.h"
#include "i2c_bus.h"
#include "color.h"

#include <stdint.h>

class RGBSensor : I2CDevice
{
  private:
  public:
    RGBSensor(I2CBus* bus, uint8_t address);
    ~RGBSensor();

    //uint8_t getID();
    //uint8_t getGain();
    //Color getColor();

    //void setGain(uint8_t gain);
};

#endif
