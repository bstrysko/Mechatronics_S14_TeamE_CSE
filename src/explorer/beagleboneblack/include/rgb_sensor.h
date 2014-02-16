#ifndef _EXPLORARE_RGB_SENSOR_H_
#define _EXPLORARE_RGB_SENSOR_H_

#include <I2CMaster/I2CDevice.h>
#include <I2CMaster/I2CBus.h>
#include "color.h"

#include <stdint.h>

#define RGB_SENSOR_ADDRESS (0x29)

#define RGB_SENSOR_COMMAND_BIT (0x80)

#define RGB_SENSOR_REGISTER_ENABLE 0x00
#define RGB_SENSOR_REGISTER_ATIME 0x01
#define RGB_SENSOR_REGISTER_WTIME 0x03
#define RGB_SENSOR_REGISTER_AILTL 0x04
#define RGB_SENSOR_REGISTER_AILTH 0x05
#define RGB_SENSOR_REGISTER_AIHTL 0x06
#define RGB_SENSOR_REGISTER_AIHTH 0x07
#define RGB_SENSOR_REGISTER_PERS 0x0C
#define RGB_SENSOR_REGISTER_CONFIG 0x0D
#define RGB_SENSOR_REGISTER_CONTROL 0x0F
#define RGB_SENSOR_REGISTER_ID 0x12
#define RGB_SENSOR_REGISTER_STATUS 0x13
#define RGB_SENSOR_REGISTER_CDATAL 0x14
#define RGB_SENSOR_REGISTER_CDATAH 0x15
#define RGB_SENSOR_REGISTER_RDATAL 0x16
#define RGB_SENSOR_REGISTER_RDATAH 0x17
#define RGB_SENSOR_REGISTER_GDATAL 0x18
#define RGB_SENSOR_REGISTER_GDATAH 0x19
#define RGB_SENSOR_REGISTER_BDATAL 0x1A
#define RGB_SENSOR_REGISTER_BDATAH 0x1B

#define RGB_SENSOR_ENABLE_PON 0x01
#define RGB_SENSOR_ENABLE_AEN 0x02
#define RGB_SENSOR_ENABLE_WEN 0x08
#define RGB_SENSOR_ENABLE_AIEN 0x10

#define TCS34725_WTIME_2_4MS      (0xFF)    /* WLONG0 = 2.4ms   WLONG1 = 0.029s */
#define TCS34725_WTIME_204MS      (0xAB)    /* WLONG0 = 204ms   WLONG1 = 2.45s  */
#define TCS34725_WTIME_614MS      (0x00)    /* WLONG0 = 614ms   WLONG1 = 7.4s   */
#define TCS34725_CONFIG_WLONG     (0x02)    /* Choose between short and long (12x) wait times via TCS34725_WTIME */
#define TCS34725_STATUS_AINT      (0x10)    /* RGBC Clean channel interrupt */
#define TCS34725_STATUS_AVALID    (0x01)    /* Indicates that the RGBC channels have completed an integration cycle */

typedef enum
{
  //2.4ms, 1 cycle, 1024
  INTEGRATION_TIME_2_4MS  = 0xFF,
  //24ms, 10 cycles, 10240
  INTEGRATION_TIME_24MS   = 0xF6,
  //50ms, 20 cycles, 20480
  INTEGRATION_TIME_50MS   = 0xEB,
  //101ms, 42 cycles, 43008
  INTEGRATION_TIME_101MS  = 0xD5,
  //154ms, 64 cycles, 65535
  INTEGRATION_TIME_154MS  = 0xC0,
  //700ms, 256 cycles, 65535
  INTEGRATION_TIME_700MS  = 0x00
} RGBSensorIntegrationTime;

typedef enum
{
  GAIN_1X = 0x00,
  GAIN_4X = 0x01,
  GAIN_16X = 0x02,
  GAIN_60X = 0x03
} RGBSensorGain;

class RGBSensor : I2CDevice
{
  private:
    bool enabled;
  public:
    RGBSensor(I2CBus* bus);
    ~RGBSensor();

    void enable();

    uint8_t getID();

    void setIntegrationTime(RGBSensorIntegrationTime t);
    void setGain(RGBSensorGain g);

    Color getColor();
};

#endif
