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
 * Implementation of ThreshFrame class.
 *
 * Created On: 2/1/14
 */

#include <frame/thresh_frame.h>

ThreshFrame::ThreshFrame(Mat m, Scalar lowBound, Scalar highBound)
{
	Mat thresh;
	inRange(m, lowBound, highBound, thresh);

	this->singleChannelMat = thresh;

    vector<Mat> channels;
	channels.push_back(thresh);
	channels.push_back(thresh);
	channels.push_back(thresh);

	Mat result;
	merge(channels, result);

	create(result);
}

ThreshFrame::ThreshFrame(RGBFrame frame, Scalar lowBound, Scalar highBound) : ThreshFrame(frame.getMat(), lowBound, highBound)
{
}

ThreshFrame::ThreshFrame(HSVFrame frame, Scalar lowBound, Scalar highBound) : ThreshFrame(frame.getMat(), lowBound, highBound)
{
}

ThreshFrame::~ThreshFrame()
{
}

Mat ThreshFrame::getSingleChannelMat()
{
	return singleChannelMat;
}
