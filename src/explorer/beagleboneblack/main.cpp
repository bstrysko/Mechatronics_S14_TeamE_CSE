#include <explorer.h>
#include <camera.h>
#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>
#include <frame/thresh_frame.h>
#include <application/window.h>

#include <opencv2/opencv.hpp>

#include <i2c/i2c_bus.h>
#include <i2c/i2c_device.h>

using namespace cv;

int main(int argc, char* argv[])
{
	Explorer::init();

//	I2CBus i2cBus(1);
//	I2CDevice d(&i2cBus, 0x29);
//	I2CDevice d(&i2cBus, 0x12);

//	uint8_t buf[10];
//	d.i2c_read(0x01, buf, 1);
//	cout << "0x01: " << (int)buf[0] << endl;

//	d.i2c_read(0x02, buf, 2);
//	cout << "0x02: " << (int)buf[0] << " " << (int)buf[1] << endl;

//	d.i2c_read(0x03, buf, 1);
//	cout << "0x03: " << (int)buf[0] << endl;

//	buf[0] = 50;
//	d.i2c_write(0x80 | 0x01, buf, 1);

	DriveSystem* driveSystem = Explorer::getDriveSystem();

	driveSystem->setServoPos(20);

//	d.i2c_read(0x03, buf, 1);
//	cout << "0x03: " << (int)buf[0] << endl;

	//cout << "RGB Color Sensor ID: " << (int)buf[0] << endl;

	cout << "End" << endl;
	//exit(1);

	Camera* camera = Explorer::getCamera();

	Window window_video("video");
	Window window_hsv("hsv");
	Window window_thresh("thresh");
	//Window window_red("red");
	Window window_contours("contours");
	
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

		//cout << contours.size() << endl;

		drawContours(rgb_frame.getMat(), contours, -1, CV_RGB(255,255,255), -1);

		std::ostringstream s;
        s << "Counter: " << distance;
        std::string text(s.str());
		rgb_frame.printText(Point(20,20), Color::GREEN, text);

		std::ostringstream t;
        t << "State: " << ((contours.size() >= 100) ? "defect" : "okay");
        std::string text2(t.str());
		rgb_frame.printText(Point(20,40), Color::GREEN, text2);

		std::ostringstream u;
        u << "Servo Pos: " << (int)driveSystem->getServoPos();
        std::string text3(u.str());
		rgb_frame.printText(Point(20,60), Color::GREEN, text3);


		window_video.renderFrame(rgb_frame);
		window_hsv.renderFrame(hsv_frame);
		window_thresh.renderFrame(thresh_frame);
	
		char key = waitKey(40);

		if(key == 97)
		{
			uint8_t servoPos = driveSystem->getServoPos();
			servoPos += 5;

			if(servoPos >= 180)
			{
				servoPos = 0;
			}

			driveSystem->setServoPos(servoPos);
		}


        distance++;
	}

	return 0;
}
