#ifndef I2CDevice_h
#define I2CDevice_h

#include "Arduino.h"

#define BUFFER_SIZE 10

typedef byte (*i2c_read_func)(byte, byte*);
typedef void (*i2c_write_func)(byte, byte*, byte);

class I2CDevice
{
  public:
    static void init(byte address,
      i2c_read_func read_func, i2c_write_func write_func);
  private:
    static bool is_write;
    static byte reg;
    static byte buffer[BUFFER_SIZE];
    static byte buffer_size;
    static i2c_read_func _read_func;
    static i2c_write_func _write_func;

    static void request();
    static void receive(int count);
};

#endif
