#include <camera.h>

Camera::Camera()
{
	camera.open(0);

	camera.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
}

Camera::~Camera()
{

}

Frame Camera::getFrame()
{
	Mat frame;

	camera >> frame;

	if(!frame.data)
	{
		//TODO: change
		return frame;
	}
	else
	{
		return frame;
	}
}
