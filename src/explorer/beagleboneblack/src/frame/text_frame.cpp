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
