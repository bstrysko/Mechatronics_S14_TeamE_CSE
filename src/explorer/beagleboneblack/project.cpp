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
 * This code is responsible for reading input from the user either
 * from the GUI or the keyboard, updating the GUI, performing red
 * detection on the camera input, and sending the correct commands
 * to the Arduino connected to the BeagleBone I2C Bus.
 * 
 * Created On: 2/2/14
 */


#include "project.h"

Window* w1;
Camera* camera;
DriveSystem* driveSystem;
bool motorForward;
bool motorFreeRun;
int16_t motorSpeed;
int16_t stepperNumSteps;

void slider_servo_callback(int v, void*)
{
	driveSystem->setServoPos(v);
}

void slider_dc_motor_callback(int v, void*)
{
	motorSpeed = (int16_t)v;	
}

void slider_stepper_motor_callback(int v, void*)
{
	stepperNumSteps = (int16_t)v;
}


Project::Project() : Application()
{
}

void Project::setup()
{
	camera = new Camera();
	Explorer::init();

	driveSystem = Explorer::getDriveSystem();

	motorForward = true;
	motorFreeRun = false;
	motorSpeed = 0;
	stepperNumSteps = 0;

	w1 = createWindow("Motor Lab");
	w1->createSlider("Servo Position", 180, slider_servo_callback);
	w1->createSlider("DC Motor Rotation(D)/Speed(DPS)", 270, slider_dc_motor_callback);
	w1->createSlider("Stepper Motor Degrees", 720, slider_stepper_motor_callback);

	setDelay(100);
}

void Project::loop()
{
	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(160, 0, 0), Scalar(255, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	ostringstream t;
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(20,40), Color::GREEN, t);
	t.str("");

    t << "Potentiometer: " << (int)driveSystem->getPotPos();
	text_frame.printText(Point(20,60), Color::GREEN, t);
	t.str("");

    t << "IR Sensor: " << (int)driveSystem->getIRSensor();
	text_frame.printText(Point(20,80), Color::GREEN, t);
	t.str("");

    t << "Switch: " << (int)driveSystem->getSwitch();
	text_frame.printText(Point(20,100), Color::GREEN, t);
	t.str("");


    t << "Servo Position: " << (int)driveSystem->getServoPos();
	text_frame.printText(Point(20,160), Color::GREEN, t);
	t.str("");

    t << "Motor Forward: " << (motorForward ? "true" : "false");
	text_frame.printText(Point(20,180), Color::GREEN, t);
	t.str("");

    t << "DC Free Run: " << (motorFreeRun ? "true" : "false");
	text_frame.printText(Point(20,200), Color::GREEN, t);
	t.str("");

    t << "DC Speed: " << (int)(motorSpeed);
	text_frame.printText(Point(20,220), Color::GREEN, t);
	t.str("");

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(char key)
{
	if(key == 't')
	{
		motorForward = !motorForward;
		motorSpeed = motorForward ? abs(motorSpeed) : -abs(motorSpeed);
		stepperNumSteps = motorForward ? abs(stepperNumSteps) : -abs(stepperNumSteps);
	}
	else if(key == 'b')
	{
		motorForward = driveSystem->getIRSensor();
		motorSpeed = motorForward ? abs(motorSpeed) : -abs(motorSpeed);
		stepperNumSteps = motorForward ? abs(stepperNumSteps) : -abs(stepperNumSteps);
	}
	else if(key == 's')
	{
		driveSystem->moveStepper(stepperNumSteps);
	}
	else if(key == 'f')
	{
		motorFreeRun = !motorFreeRun;
	}
	else if(key == 'm')
	{
		driveSystem->setDCMotor(motorFreeRun, motorSpeed);
	}
	else if(key == 'z')
	{
		driveSystem->setDCMotor(false, 0);
	}
}
