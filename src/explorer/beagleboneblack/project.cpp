#include "project.h"

Window* w1;
Camera* camera;

void slider_servo_callback(int v, void*)
{
}

void slider_dc_motor_callback(int v, void*)
{
}

void slider_stepper_motor_callback(int v, void*)
{

}

//	I2CBus i2cBus(1);
//	I2CDevice d(&i2cBus, 0x29);
//	I2CDevice d(&i2cBus, 0x12);
//	uint8_t buf[10];
//	DriveSystem* driveSystem = Explorer::getDriveSystem();
//	driveSystem->setServoPos(20);

/*
		Mat f = rgb_frame.getMat();

		ThreshFrame thresh_frame(rgb_frame);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(thresh_frame.getMat(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
		drawContours(rgb_frame.getMat(), contours, -1, CV_RGB(255,255,255), -1);

		std::ostringstream t;
        t << "State: " << ((contours.size() >= 100) ? "defect" : "okay");
        std::string text2(t.str());
		rgb_frame.printText(Point(20,40), Color::GREEN, text2);


//		std::ostringstream u;
//      u << "Servo Pos: " << (int)driveSystem->getServoPos();
//      std::string text3(u.str());
//		rgb_frame.printText(Point(20,60), Color::GREEN, text3);
//		driveSystem->setServoPos(servoPos);
*/
Project::Project() : Application()
{
}

void Project::setup()
{
	camera = new Camera();
//	Explorer::init();

	w1 = createWindow("Motor Lab");
	w1->createSlider("Servo Position", 180, slider_servo_callback);
	w1->createSlider("DC Motor Rotation/Speed", 100, slider_dc_motor_callback);
	w1->createSlider("Stepper Motor Degrees", 100, slider_stepper_motor_callback);

	cout << "Setup" << endl;

	setDelay(100);
}

void Project::loop()
{
	RGBFrame rgb_frame = camera->getRGBFrame();
	//rgb_frame.resize(1024, 960);
	HSVFrame hsv_frame(rgb_frame);

	w1->renderFrames4(rgb_frame, hsv_frame, rgb_frame, rgb_frame);
}

void Project::keyPressed(char key)
{
	cout << "Pressed key: " << (int)key << endl;
}
