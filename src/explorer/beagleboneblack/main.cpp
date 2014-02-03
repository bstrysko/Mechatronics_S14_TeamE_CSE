#include <explorer.h>
#include <camera.h>
#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>
#include <frame/thresh_frame.h>

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Explorer::init();

	Camera* camera = Explorer::getCamera();

	namedWindow("video", 1);
	namedWindow("hsv", 1);	
	namedWindow("thresh", 1);

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

		std::ostringstream s;
        s << "Distance: " << distance;
        std::string text(s.str());
		rgb_frame.printText(20,20, Color::GREEN, text);

		HSVFrame hsv_frame(rgb_frame);
		ThreshFrame thresh_frame(rgb_frame);

        imshow("video", f);
		imshow("hsv", hsv_frame.getMat());
		imshow("thresh", thresh_frame.getMat());

		if(waitKey(50) >= 0)
		{

		}

        distance++;
	}

	return 0;
}
