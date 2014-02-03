#include <explorer.h>
#include <camera.h>

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
		Frame frame = camera->getFrame();
		
		Mat f = frame.getMat();

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

		Frame hsv = frame.toHSVFrame();

        imshow("video", f);
		imshow("hsv", hsv.getMat());

		if(waitKey(50) >= 0)
		{

		}

        distance++;

	}

	return 0;
}
