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
 * Implementation of TextFrame class.
 *
 * Created On: 2/1/14
 */

#include <frame/text_frame.h>

TextFrame::TextFrame(Frame frame)
{
//	Mat temp(&(frame.getMat()), true);
    create(frame.getMat().clone());
	getMat().setTo(Scalar(0,0,0));
}

TextFrame::~TextFrame()
{
}
