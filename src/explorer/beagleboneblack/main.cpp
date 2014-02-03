#include <explorer.h>
#include <camera.h>
#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>

#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Explorer::init();

	Camera* camera = Explorer::getCamera();

	namedWindow("video", 1);
	namedWindow("hsv", 1);	

	unsigned long long distance = 0;

	while(true)
	{
		RGBFrame rgb_frame = camera->getRGBFrame();
		
		Mat f = rgb_frame.getMat();

		if(!f.data)
		{
			continue;
		}

		std::ostringstream s;
        s << "Distance: " << distance;
        std::string text(s.str());
        int fontFace = FONT_HERSHEY_SIMPLEX;
        double fontScale = 2;
        int thickness = 3;
        Point textOrg(20, 20);
        putText(f, text, textOrg, fontFace, 0.8, Scalar(0,250,0), 1, CV_AA);

		HSVFrame hsv_frame(rgb_frame);

        imshow("video", f);
		imshow("hsv", hsv_frame.getMat());

		if(waitKey(50) >= 0)
		{

		}

        distance++;

	}

	return 0;
}
