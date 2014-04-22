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

uint8_t indexToXMap[] = 
	{
		0xFF,
		0, 1, 2, 3, 4, 5, 6, 7, 8,
		8, 7, 6, 5, 4, 3, 2, 1, 0,
		0, 1, 2, 3, 4, 5, 6, 7, 8
	};

uint8_t indexToYMap[] = 
	{
		0,
		0, 0, 0, 0, 0, 0, 0, 0, 0,
		3, 3, 3, 3, 3, 3, 3, 3, 3,
		6, 6, 6, 6, 6, 6, 6, 6, 6
	};

void usage(string name);

#define IS_DEFECT(c) (c.getAlpha() > 2000)

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

	setDelay(500);
}

void Project::loop()
{
	vector<Color> data = rgbColorSensorArray->getData();

	if(coms->isStarted())
	{
		bool arrived = driveSubsystem->hasArrived();

		if(arrived)
		{
			uint8_t positionIndex = driveSubsystem->getPositionIndex();

			if(positionIndex == 0)
			{
				driveSubsystem->moveNextPositionIndex();
			}
			else if(positionIndex != 28)
			{
				uint8_t x = indexToXMap[positionIndex];
				uint8_t y = indexToYMap[positionIndex];

				bool r = (y == 0) || (y == 6);

				coms->detectCell(CSECellCoordinate(y, x), IS_DEFECT(data[r ? 2 : 0]) ? DEFECT : NON_DEFECT);
				coms->detectCell(CSECellCoordinate((y+1), x), IS_DEFECT(data[1]) ? DEFECT : NON_DEFECT);
				coms->detectCell(CSECellCoordinate((y+2), x), IS_DEFECT(data[r ? 0 : 2]) ? DEFECT : NON_DEFECT);
				cout << (*coms) << endl;
				coms->flush();

				driveSubsystem->moveNextPositionIndex();
			}
		}
	}

	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(20, 100, 100), Scalar(30, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	ostringstream t;
    t << "Started: " << (coms->isStarted() ? "true" : "false");
	text_frame.printText(Point(40,20), Scalar(255, 0, 255, 0), t);
	t.str("");

/*
 	t << "Here: " << (here ? "true" : "false");
	text_frame.printText(Point(40,60), Scalar(255, 0, 255, 0), t);
	t.str("");
	
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(40,80), Scalar(255, 0, 255, 0), t);
	t.str("");
*/
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
