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

void Frame::printText(int x, int y, Color color, string text)
{
    putText(frame, text, Point(x,y), FONT_HERSHEY_SIMPLEX,
		0.8, Scalar(color.getRed(),color.getGreen(),color.getBlue(),
		color.getAlpha()), 1, CV_AA);
}
