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

#include <CSEComsProtocol/CSEComs.h>

Window* w1;
Camera* camera;
DriveSubsystem* driveSubsystem;
RGBColorSensorArray* rgbColorSensorArray;
CSEComs* coms;

void usage(string name);

CSECellCoordinate coordinates;
bool here;
bool scanned;
bool started;

#define IS_DEFECT(c) (c.getAlpha() > 3000)

CSECellCoordinate getNextCoordinates(CSECellCoordinate currentCoordinates);

Project::Project() : Application()
{
}

void Project::setup(vector<string> argv)
{
	if(argv.size() < 2)
	{
		usage(argv[0]);
		exit(1);
	}

	Explorer::init(Size(400, 400));

	driveSubsystem = Explorer::getDriveSubsystem();
	rgbColorSensorArray = Explorer::getRGBColorSensorArray();
	camera = Explorer::getCamera();

	w1 = createWindow("Explorer");

	string hostname = argv[1];
	coms = new CSEComs(hostname);

	here = false;
	scanned = false;
	started = false;
	
	setDelay(500);
}

void Project::loop()
{
	here = driveSubsystem->hasArrived();

	vector<Color> data = rgbColorSensorArray->getData();

	if(coms->isStarted() && !started)
	{
		coms->flush();
		started = true;
	}

	if(here && !scanned)
	{
		here = false;
//		coms->detectCell(CSECellCoordinate(-y, x), IS_DEFECT(data[0]) ? DEFECT : NON_DEFECT);
//		coms->detectCell(CSECellCoordinate((-y+1), x), IS_DEFECT(data[1]) ? DEFECT : NON_DEFECT);
//		coms->detectCell(CSECellCoordinate((-y+2), x), IS_DEFECT(data[2]) ? DEFECT : NON_DEFECT);
		scanned = true;	

		cout << (*coms) << endl;
		coms->flush();
	}

	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(160, 0, 0), Scalar(255, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	ostringstream t;
    t << "Started: " << (coms->isStarted() ? "true" : "false");
	text_frame.printText(Point(40,20), Scalar(255, 0, 255, 0), t);
	t.str("");

 	t << "Here: " << (here ? "true" : "false");
	text_frame.printText(Point(40,60), Scalar(255, 0, 255, 0), t);
	t.str("");
	
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(40,80), Scalar(255, 0, 255, 0), t);
	t.str("");

	for(size_t i = 0; i < data.size(); i++)
	{
		Color c = data[i];

		ostringstream t;
		t << (IS_DEFECT(c) ? "DEFECT" : "NON-DEFECT");
		text_frame.printText(Point(40, 100 + 20*i), Scalar(255, c.getBlue(), c.getGreen(), c.getRed()), t);
		t.str("");
	}

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(int key)
{
}

void usage(string name)
{
    cout << "usage: ./" << name << " [hostname]" << endl;
}

CSECellCoordinate getNextCoordinates(CSECellCoordinate currentCoordinates)
{
	uint8_t x = currentCoordinates.first;
	uint8_t y = currentCoordinates.second;

	switch(y)
	{
		case 0:
		{
			if(x == 8)
			{
				return CSECellCoordinate(8, 1);
			}
			else
			{
				return CSECellCoordinate(x+1, 0);
			}
		}
		case 1:
		{
			if(x == 0)
			{
				return CSECellCoordinate(0, 2);
			}
			else
			{
				return CSECellCoordinate(x-1, 1);
			}
		}
		case 2:
		{
			if(x == 8)
			{
				return CSECellCoordinate(9, 9);
			}
			else
			{
				return CSECellCoordinate(x+1, 2);
			}
		}
		default:
		{
			return CSECellCoordinate(-1, -1);
		}
	}
}

