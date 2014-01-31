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
float x;
float y;

Project::Project() : Application()
{
}

void Project::setup()
{
//	setDelay(10);

	Explorer::init();

	driveSystem = Explorer::getDriveSystem();
	rgbColorSensorArray = Explorer::getRGBColorSensorArray();
	camera = Explorer::getCamera();

	x = 0.0;
	y = 0.0;
	driveSystem->setPosition(x, y);

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
	
	vector<Color> data = rgbColorSensorArray->getData();

	for(size_t i = 0; i < data.size(); i++)
	{
		Color c = data[i];

		ostringstream t;
		t << ((c.getAlpha() > 3000) ? "DEFECT" : "NON-DEFECT");
		text_frame.printText(Point(20, 60 + 20*i), Color(c.getBlue(), c.getGreen(), c.getRed()), 0, t);
		t.str("");
	}

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

#define STEP 4.0

void Project::keyPressed(char key)
{
	switch(key)
	{
		case 'a': //left
		{
			x -= STEP;
			break;
		}
		case 'w': //up
		{
			y += STEP;
			break;
		}
		case 'd': //right
		{
			x += STEP;
			break;
		}
		case 's': //down
		{
			y -= STEP;
			break;
		}
	}

	driveSystem->setPosition(x, y);
}
