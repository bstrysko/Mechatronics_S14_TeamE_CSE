#include <Wire.h>
#include <I2CDevice.h>

#include <Servo.h>

#define PIN_SERVO 11
#define PIN_STEPPER_STEP 8
#define PIN_STEPPER_DIR 9
#define PIN_POT 0
#define PIN_IR_SENSOR 10
#define PIN_SWITCH 12

#define REGISTER_SERVO 1
#define REGISTER_DC_MOTOR 2
#define REGISTER_STEPPER_MOTOR 3
#define REGISTER_POT 10
#define REGISTER_IR_SENSOR 11
#define REGISTER_SWITCH 12

byte i2cRead(byte reg, byte* buffer);
void i2cWrite(byte reg, byte* buffer, byte buffer_size);


Servo servo;
byte stepperNumSteps;

byte valuePot;
byte valueIRSensor;
byte valueSwitch;

void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning Program");

  servo.attach(PIN_SERVO);
  servo.write(0);

  pinMode(PIN_STEPPER_STEP, OUTPUT);
  pinMode(PIN_STEPPER_DIR, OUTPUT);
  digitalWrite(PIN_STEPPER_DIR, 0);
  
  pinMode(PIN_IR_SENSOR, INPUT);
  pinMode(PIN_SWITCH, INPUT);
  
  valuePot = 0;
  valueIRSensor = 0;
  valueSwitch = 0;
  
  I2CDevice::init(0x12, i2cRead, i2cWrite);
}

byte calculateServoPos(byte servoPos)
{
  byte oldServoPos = servo.read();
  
  if(servoPos == 0)
  {
    return 0;
  }
  else if(abs(servoPos - oldServoPos) > 5)
  {
    return servoPos; 
  }
  else
  {
    return oldServoPos;
  }
}

void stepperMotorTakeSingleStep()
{
    int stepPulseWidthInMicroSec = 2;

    digitalWrite(PIN_STEPPER_STEP, LOW);
    delayMicroseconds(stepPulseWidthInMicroSec); 
    digitalWrite(PIN_STEPPER_STEP, HIGH); 
    delayMicroseconds(stepPulseWidthInMicroSec); 
    digitalWrite(PIN_STEPPER_STEP, LOW);
}

void loop()
{
   int sum = 0;
   for(int i = 0; i < 10; i++)
   {
     sum += map(analogRead(PIN_POT), 0, 708, 0, 180);
   }
   valuePot = sum/10;
   
   valueIRSensor = digitalRead(PIN_IR_SENSOR);
   
   //TODO: debouncing
   valueSwitch = digitalRead(PIN_SWITCH);
   
   if(valueSwitch)
   {
     servo.write(calculateServoPos(valuePot));
     //Serial.println(servo.read());
   }
   
   if(stepperNumSteps > 0)
   {
     stepperNumSteps--;
     stepperMotorTakeSingleStep();
     delay(1);
   }
}


byte i2cRead(byte reg, byte* buffer)
{ 
  switch(reg)
  {
    case REGISTER_SERVO:
    {
      buffer[0] = servo.read();
      return 1; 
    }
    case REGISTER_POT:
    {
      buffer[0] = valuePot;
      return 1;
    }
    case REGISTER_IR_SENSOR:
    {
      buffer[0] = valueIRSensor;
      return 1;
    }
    case REGISTER_SWITCH:
    {
      buffer[0] = valueSwitch;
      return 1;
    }
  }
  
  return 0;
}

void i2cWrite(byte reg, byte* buffer, byte buffer_size)
{
  switch(reg)
  {
     case REGISTER_SERVO:
     {
       servo.write(buffer[0]);
       break; 
     }
     case REGISTER_DC_MOTOR:
     {
       //TODO
       break;
     }
     case REGISTER_STEPPER_MOTOR:
     {
       byte temp = buffer[0];
       stepperNumSteps = (byte)(((float)(temp & (~0x80))) / 0.14);
       byte dir = !(!(temp & 0x80));
       Serial.println(dir);
       digitalWrite(PIN_STEPPER_DIR, dir);
       break; 
     }
  }
}
