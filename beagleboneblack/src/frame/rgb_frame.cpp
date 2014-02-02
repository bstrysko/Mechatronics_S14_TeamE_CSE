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
 * Implementation of RGBFrame class.
 *
 * Created On: 2/1/14
 */

#include <frame/rgb_frame.h>

RGBFrame::RGBFrame(Mat frame)
{
	create(frame);
}

RGBFrame::~RGBFrame()
{
}

