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
RGBColorSensorArray* rgbColorSensorArray;

Project::Project() : Application()
{
}

void Project::setup()
{
	setDelay(200);

	Explorer::init();

	driveSystem = Explorer::getDriveSystem();
	rgbColorSensorArray = Explorer::getRGBColorSensorArray();
	camera = Explorer::getCamera();

	w1 = createWindow("Explorer");
}

void Project::loop()
{
	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(160, 0, 0), Scalar(255, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	ostringstream t;
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(20,40), Color::GREEN, 0, t);
	t.str("");
	
	vector<RGBColorSensor> data = rgbColorSensorArray->getData();

	for(size_t i = 0; i < data.size(); i++)
	{
		RGBColorSensor s = data[i];
		Color c = s.getColor();

		ostringstream t;
		t << (s.isDefect() ? "DEFECT" : "NON-DEFECT");
		text_frame.printText(Point(20, 60 + 20*i), Color(c.getBlue(), c.getGreen(), c.getRed()), 0, t);
		t.str("");

		cout << s << "\t";
	}

	cout << endl;

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(char key)
{
}
