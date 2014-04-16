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

#include <CSEComsProtocol/CSEComsClient.h>

Window* w1;
Camera* camera;
DriveSubsystem* driveSubsystem;
RGBColorSensorArray* rgbColorSensorArray;
CSEComsClient* client;

#define STEP 4.0

int x;
int y;
bool here;

#define IS_DEFECT(c) (c.getAlpha() > 3000)
#define FLOAT_TO_INT(f) ((int)((f > 0) ? (f + 0.2) : (f - 0.2)))

Project::Project() : Application()
{
}

void Project::setup(string hostname, int port)
{
	Explorer::init();

	driveSubsystem = Explorer::getDriveSubsystem();
	rgbColorSensorArray = Explorer::getRGBColorSensorArray();
	camera = Explorer::getCamera();

	w1 = createWindow("Explorer");

	client = new CSEComsClient(hostname, port);

	float x2, y2;
	driveSubsystem->getPosition(&x2, &y2);
	x = x2 / STEP;
	y = y2 / STEP;
	here = false;
	
	setDelay(500);
}

void Project::loop()
{
	float x2, y2;
	driveSubsystem->getPosition(&x2, &y2);

	x2 /= STEP;
	y2 /= STEP;

	cout << "(" << x << "," << y << ") (" << FLOAT_TO_INT(x2) << ", " << FLOAT_TO_INT(y2) << ")" << endl;

	vector<Color> data = rgbColorSensorArray->getData();

	if((FLOAT_TO_INT(x2) == x) && (FLOAT_TO_INT(y2) == y) && (!here))
	{
		here = true;
		client->detectCell(CSECellCoordinate(-y, x), IS_DEFECT(data[0]) ? DEFECT : NON_DEFECT);
		client->detectCell(CSECellCoordinate((-y+1), x), IS_DEFECT(data[1]) ? DEFECT : NON_DEFECT);
		client->detectCell(CSECellCoordinate((-y+2), x), IS_DEFECT(data[2]) ? DEFECT : NON_DEFECT);
	
		cout << (*client) << endl;
		client->flush();
	}

	RGBFrame rgb_frame = camera->getRGBFrame();
	
	HSVFrame hsv_frame(rgb_frame);
	ThreshFrame thresh_frame(hsv_frame, Scalar(160, 0, 0), Scalar(255, 255, 255));
	TextFrame text_frame(rgb_frame);
	
	ostringstream t;
    t << "Target Position: (" << x << ", " << y << ")";
	text_frame.printText(Point(40,40), Color::GREEN, 0, t);
	t.str("");
	
	t << "Current Position: (" << x2 << ", " << y2 << ")";
	text_frame.printText(Point(40,60), Color::GREEN, 0, t);
	t.str("");
	
    t << "State: " << ((countNonZero(thresh_frame.getSingleChannelMat()) > 10000) ? "defect" : "okay");
	text_frame.printText(Point(40,80), Color::GREEN, 0, t);
	t.str("");
	
	for(size_t i = 0; i < data.size(); i++)
	{
		Color c = data[i];

		ostringstream t;
		t << (IS_DEFECT(c) ? "DEFECT" : "NON-DEFECT");
		text_frame.printText(Point(40, 100 + 20*i), Color(c.getBlue(), c.getGreen(), c.getRed()), 0, t);
		t.str("");
	}

	w1->renderFrames4(rgb_frame, hsv_frame, thresh_frame, text_frame);
}

void Project::keyPressed(int key)
{
	switch(key)
	{
		case 'a': //left
		{
			x--;
			break;
		}
		case 'w': //up
		{
			y+= 1;
			break;
		}
		case 'd': //right
		{
			x++;
			break;
		}
		case 's': //down
		{
			y-= 1;
			break;
		}
	}

	driveSubsystem->setPosition(x * STEP, y * STEP);
	here = false;
}
