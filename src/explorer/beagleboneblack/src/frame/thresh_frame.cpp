#include <frame/thresh_frame.h>

ThreshFrame::ThreshFrame(HSVFrame frame)
{
	Mat thresh;	
	inRange(frame.getMat(), Scalar(0, 255, 255), cv::Scalar(20, 255, 255), thresh);
	create(thresh);
}

ThreshFrame::~ThreshFrame()
{
}
