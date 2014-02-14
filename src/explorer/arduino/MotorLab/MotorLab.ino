/*
 * Mechatronics (Spring 2014)
 * Team Name: Explorare
 *
 * Team Member Names:
 * Brent Strysko
 * Wen Li
 * Caroline Colombo
 * Funan Ma
 * 
 * This code is responsible for responding to I2C read/write commands
 * from the BeagleBoneBlack, reading from all sensors, and updating the state
 * of all motors.
 *
 * Created On: 2/8/14
 */

#include <Stepper.h>

#include <Wire.h>
#include <WireDevice.h>

#include <Servo.h>
#include<Metro.h>
#include <PID_v1.h>

#include <Bounce2.h>

Bounce debouncer = Bounce(); 

#define WIRE_DEVICE_ID 0x12

#define PIN_SERVO 11
#define PIN_STEPPER0 6
#define PIN_STEPPER1 7
#define PIN_STEPPER2 9
#define PIN_STEPPER3 8
#define PIN_DC_MOTOR0 3
#define PIN_DC_MOTOR1 5
#define PIN_ENCODER_A 2

#define PIN_POT 0
#define PIN_IR_SENSOR 10
#define PIN_SWITCH 12

#define REGISTER_SERVO 1
#define REGISTER_DC_MOTOR 2
#define REGISTER_STEPPER_MOTOR 3
#define REGISTER_POT 10
#define REGISTER_IR_SENSOR 11
#define REGISTER_SWITCH 12

byte wireDeviceRead(byte reg, byte* buffer);
void wireDeviceWrite(byte reg, byte* buffer, byte bufferSize);


Servo servo;
Stepper stepper(400, PIN_STEPPER0, PIN_STEPPER1, PIN_STEPPER2, PIN_STEPPER3); 
int stepperSteps;
volatile unsigned int encoder0Count;
unsigned int oldEncoder0Count;
double dcMotorSpeed, dcMotorTargetSpeed, dcMotorOutput;
Metro dcMotorEncoderMetro(10);
PID dcMotorPID(&dcMotorSpeed, &dcMotorOutput, &dcMotorTargetSpeed, 1, 1, 0, DIRECT);
boolean dcMotorDirection;
volatile boolean dcMotorContinuous;
volatile unsigned int encoderTarget;


byte valuePot;
byte valueIRSensor;
byte valueSwitch;

/*
 * Called every encoder tick
 */
void interruptEncoder()
{
  encoder0Count++;
 
  if(!dcMotorContinuous)
  {
    if(encoderTarget > 0)
    {
      encoderTarget--;
    }
    else if(encoderTarget == 0)
    {
      digitalWrite(PIN_DC_MOTOR0, LOW);
      digitalWrite(PIN_DC_MOTOR1, LOW);

    }
  }
}

/*
 * Initialize all sensors, motors, PID control,
 * and I2CBus.
 */
void setup()
{
  Serial.begin(9600);
  Serial.println("Beginning Program");

  servo.attach(PIN_SERVO);
  servo.write(0);

  stepper.setSpeed(20);
  stepper.step(400);
  stepperSteps = 0;
  
  pinMode(PIN_DC_MOTOR0, OUTPUT);
  pinMode(PIN_DC_MOTOR1, OUTPUT);
  digitalWrite(PIN_DC_MOTOR0, LOW);
  digitalWrite(PIN_DC_MOTOR1, LOW);
  pinMode(PIN_ENCODER_A, INPUT);
  digitalWrite(PIN_ENCODER_A, HIGH);
  
  pinMode(PIN_IR_SENSOR, INPUT);
  pinMode(PIN_SWITCH, INPUT);
  
  valuePot = 0;
  valueIRSensor = 0;
  valueSwitch = 0;
  
  encoderTarget = 0;
  dcMotorContinuous = false;
  dcMotorTargetSpeed = 0;
  
  attachInterrupt(0, interruptEncoder, CHANGE);
  dcMotorPID.SetMode(AUTOMATIC);
  dcMotorDirection = true;
  
  debouncer.attach(PIN_SWITCH);
  debouncer.interval(5);
  
  WireDevice.begin(WIRE_DEVICE_ID, wireDeviceRead, wireDeviceWrite);
}

/*
 * Only move the servo when there is a reasonable
 * distance to move.
 */
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

/*
 * Read the sensors, calculate PID values, and debounce the switch.
 */
void loop()
{  
   int sum = 0;
   for(int i = 0; i < 10; i++)
   {
     sum += map(analogRead(PIN_POT), 0, 708, 0, 180);
   }
   valuePot = sum/10;
   
   valueIRSensor = digitalRead(PIN_IR_SENSOR);
   
   debouncer.update();
   valueSwitch = debouncer.read();
   
   if(valueSwitch)
   {
     servo.write(calculateServoPos(valuePot));
   }
   
   stepper.step(stepperSteps);
   stepperSteps = 0;
   
   if(dcMotorContinuous)
   {
     if(dcMotorEncoderMetro.check() == 1)
     {
       dcMotorSpeed=((double)encoder0Count-(double)oldEncoder0Count)*3;
       oldEncoder0Count = encoder0Count;
     }
    
     dcMotorPID.Compute();

     if(dcMotorDirection)
     {
       digitalWrite(PIN_DC_MOTOR0, LOW);
       analogWrite(PIN_DC_MOTOR1, dcMotorOutput);
     }
     else
     {
       digitalWrite(PIN_DC_MOTOR1, LOW);
       analogWrite(PIN_DC_MOTOR0, dcMotorOutput);
     }
   }
}

/*
 * Called when the BeagleBone wants to read data from the Arduino 
 * @param reg the register the beaglebone wants to read data from
 * @param buffer a byte array that the Arduino will send back 
 * to the BeagleBone
 * @return the number of bytes to send back to the Beaglebone
 */
byte wireDeviceRead(byte reg, byte* buffer)
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

/*
 * Called when the BeagleBone wants to write to the Arduino
 * @param reg the register the beaglebone wants to write data to
 * @param buffer a byte array of size bufferSize containing data
 * from the Beaglebone.
 * @param bufferSize the size of buffer
 */
void wireDeviceWrite(byte reg, byte* buffer, byte bufferSize)
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
       dcMotorContinuous = (buffer[0] == 1) ? true : false;
       dcMotorDirection = (!(!(buffer[1] & 0x80)));
              
       short deg = (buffer[1] << 8) | buffer[2];
       
       deg = abs(deg);
       
       if(dcMotorContinuous)
       {
         dcMotorTargetSpeed = map(deg, 0, 270, 0, 132);
         encoder0Count = 0;
       }
       else
       {
         encoderTarget = (unsigned int)((float)deg*(11.0));
         
         if(dcMotorDirection)
         {
           digitalWrite(PIN_DC_MOTOR0, LOW);
           analogWrite(PIN_DC_MOTOR1, 50);
         }
         else
         {
           digitalWrite(PIN_DC_MOTOR1, LOW);
           analogWrite(PIN_DC_MOTOR0, 50);
         }
       }
       
       break;
     }
     case REGISTER_STEPPER_MOTOR:
     {
       short deg = (buffer[1] << 8) | buffer[0];
       stepperSteps = (int)(((float)(deg)/360.0) * 401.0);
       break;
     }
  }
}
