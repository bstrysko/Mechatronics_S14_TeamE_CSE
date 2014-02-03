#include <frame/hsv_frame.h>

HSVFrame::HSVFrame(RGBFrame frame)
{
	Mat hsv;
    cvtColor(frame.getMat(), hsv, CV_BGR2HSV);
    create(hsv);
}

HSVFrame::~HSVFrame()
{
}
