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
 * @author Brent Strysko
 * 
 * Implementation of the Project class.
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
RGBSensor* rgbSensor;

Project::Project() : Application()
{
}

void Project::setup()
{
	Explorer::init();

	driveSystem = Explorer::getDriveSystem();
	rgbSensor = Explorer::getRGBSensor();
	camera = Explorer::getCamera();

	w1 = createWindow("Explorer");
}

void Project::loop()
{
	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(160, 0, 0), Scalar(255, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	Color c = rgbSensor->getColor();

	ostringstream t;
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(20,40), Color::GREEN, t);
	t.str("");

    t << "Color: " << c;
	text_frame.printText(Point(20,60), Color::GREEN, t);
	t.str("");

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(char key)
{
}
