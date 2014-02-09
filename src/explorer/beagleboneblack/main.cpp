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

int main()
{
	Explorer::init();

	I2CBus i2cBus(1);
	I2CDevice d(&i2cBus, 0x29);

	uint8_t buf[1];
	d.i2c_read(0x80 | 0x12, buf, 1);

	cout << "RGB Color Sensor ID: " << (int)buf[0] << endl;

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

		window_video.renderFrame(rgb_frame);
		window_hsv.renderFrame(hsv_frame);
		window_thresh.renderFrame(thresh_frame);
	
		if(waitKey(50) >= 0){}

        distance++;
	}

	return 0;
}
