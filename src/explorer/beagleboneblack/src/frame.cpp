#include "frame.h"

Frame::Frame(Mat frame)
{
  this->frame = frame;
}

Frame::~Frame()
{

}

Frame Frame::toHSVFrame()
{
	Mat frame_hsv;
	cvtColor(frame, frame_hsv, CV_BGR2HSV);
	return Frame(frame_hsv);
}

Mat Frame::getMat()
{
  return frame;
}
