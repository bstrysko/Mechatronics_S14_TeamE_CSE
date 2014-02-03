#include <frame/frame.h>

void Frame::create(Mat frame)
{
  this->frame = frame;
}

Frame::~Frame()
{

}

Mat Frame::getMat()
{
  return frame;
}

int Frame::getWidth()
{
	return frame.size().width;
}

int Frame::getHeight()
{
	return frame.size().height;
}

void Frame::resize(int width, int height)
{
	Mat dest;
	cv::resize(frame, dest, Size(width, height));
	this->frame = dest;
}