#include "project.h"

Window* w1;
Camera* camera;
DriveSystem* driveSystem;
bool stepperForward;

void slider_servo_callback(int v, void*)
{
	driveSystem->setServoPos(v);
}

void slider_dc_motor_callback(int v, void*)
{
}

void slider_stepper_motor_callback(int v, void*)
{
	driveSystem->moveStepper(stepperForward, (uint8_t)v);
}

//	I2CBus i2cBus(1);
//	I2CDevice d(&i2cBus, 0x29);
//	I2CDevice d(&i2cBus, 0x12);

Project::Project() : Application()
{
}

void Project::setup()
{
	camera = new Camera();
	Explorer::init();

	driveSystem = Explorer::getDriveSystem();

	stepperForward = true;

	w1 = createWindow("Motor Lab");
	w1->createSlider("Servo Position", 180, slider_servo_callback);
	w1->createSlider("DC Motor Rotation/Speed", 100, slider_dc_motor_callback);
	w1->createSlider("Stepper Motor Degrees", 90, slider_stepper_motor_callback);

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

    t << "Stepper Forward: " << (stepperForward ? "true" : "false");
	text_frame.printText(Point(20,180), Color::GREEN, t);
	t.str("");


	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(char key)
{
	if(key == 't')
	{
		stepperForward = !stepperForward;
	}
	else if(key == 'b')
	{
		stepperForward = driveSystem->getIRSensor();
	}
}
