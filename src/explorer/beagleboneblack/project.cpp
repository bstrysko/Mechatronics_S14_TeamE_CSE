#include "project.h"

Window* w1;

void on_trackbar( int, void* )
{
	cout << "Trackbar moved" << endl;
}

//	Camera* camera = new Camera();
//	I2CBus i2cBus(1);
//	I2CDevice d(&i2cBus, 0x29);
//	I2CDevice d(&i2cBus, 0x12);
//	uint8_t buf[10];
//	DriveSystem* driveSystem = Explorer::getDriveSystem();
//	driveSystem->setServoPos(20);

//	Camera* camera = Explorer::getCamera();
/*
	Window window_video("video");
	Window window_hsv("hsv");
	Window window_thresh("thresh");
	
	unsigned long long distance = 0;

	while(true)
	{
		RGBFrame rgb_frame = camera->getRGBFrame();

		//rgb_frame.resize(1024, 960);
		
		Mat f = rgb_frame.getMat();

		if(!f.data)
		{
			continue;
		}

		HSVFrame hsv_frame(rgb_frame);
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

		window_video.renderFrame(rgb_frame);

		window_hsv.renderFrame(hsv_frame);
		window_thresh.renderFrame(thresh_frame);
	
//			uint8_t servoPos = driveSystem->getServoPos();
//			servoPos += 5;
//			if(servoPos >= 180)
//			{
//				servoPos = 0;
//			}
//			driveSystem->setServoPos(servoPos);
*/
Project::Project() : Application()
{
}

int slider;

void Project::setup()
{
//	Explorer::init();

	w1 = createWindow("w1");
//	setTrackbarPos(string("t1"),string("w1"),0);
	createTrackbar("t1", "w1", &slider, 180, on_trackbar);

	cout << "Setup" << endl;

	setDelay(100);
}

void Project::loop()
{
//	cout << "Loop" << endl;
}

void Project::keyPressed(char key)
{
	cout << "Pressed key: " << (int)key << endl;
}
