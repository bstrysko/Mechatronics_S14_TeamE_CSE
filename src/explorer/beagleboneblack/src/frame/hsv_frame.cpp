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
 * Implementation of HSVFrame class.
 *
 * Created On: 2/1/14
 */

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
