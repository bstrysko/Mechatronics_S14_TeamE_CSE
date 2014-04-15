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
 * Implementation of Camera class.
 *
 * Created On: 2/1/14
 */

#include <camera.h>

Camera::Camera()
{
	camera.open(0);

	camera.set(CV_CAP_PROP_FRAME_WIDTH, 160 /*320*/);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 120 /*240*/);
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
