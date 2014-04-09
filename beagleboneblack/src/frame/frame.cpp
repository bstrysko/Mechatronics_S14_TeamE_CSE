/*
 * Mechatronics (Spring 2014)
 * Team Name: Explorare
 *
 * Team Member Names:
 * Brent Strysko
 * Wen Li
 * Caroline Colombo
 * Funan Ma
 * 
 * @author Brent Strysko
 *
 * Implementation of Frame class.
 *
 * Created On: 2/1/14
 */

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

void Frame::printText(Point point, Color color, uint8_t alpha, ostringstream& stream)
{
	printText(point, color, alpha, stream.str());
}

void Frame::printText(Point point, Color color, uint8_t alpha, string text)
{
    putText(frame, text, point, FONT_HERSHEY_SIMPLEX,
		0.5, Scalar(color.getRed(),color.getGreen(),color.getBlue(),
		alpha), 1, CV_AA);
}
