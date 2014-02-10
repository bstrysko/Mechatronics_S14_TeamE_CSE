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

RGBFrame Camera::getRGBFrame()
{
	Mat frame;

	while(!frame.data)
	{
		camera >> frame;
	}
	
	return RGBFrame(frame);
}
