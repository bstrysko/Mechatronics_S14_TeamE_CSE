#include <Wire.h>
#include <I2CDevice.h>

#include <Servo.h>

#define REGISTER_SERVO 0x1

byte i2c_read(byte reg, byte* buffer);
void i2c_write(byte reg, byte* buffer, byte buffer_size);


Servo servo;

volatile byte s;

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning Program");

  servo.attach(11);

  pinMode(3, OUTPUT);

  I2CDevice::init(0x12, i2c_read, i2c_write);
  
  s = 0;
}

void loop()
{
  digitalWrite(3, HIGH);
  delay(5);
  digitalWrite(3, LOW);
  //delay(100);
}


byte i2c_read(byte reg, byte* buffer)
{ 
  switch(reg)
  {
    case REGISTER_SERVO:
    {
      //buffer[0] = 10;
      return 0;
    }
    case 0x02:
    {
      buffer[0] = 20;
      buffer[1] = 21;
      return 2; 
    }
    case 0x03:
    {
      buffer[0] = s;
      return 1;
    }
  }
  
  return 0;
}

void i2c_write(byte reg, byte* buffer, byte buffer_size)
{
  switch(reg)
  {
     case REGISTER_SERVO:
     {
       servo.write(buffer[0]);
       break; 
     }
     case 0x03:
     {
       s = buffer[0];
       break;
     }
  }
}
