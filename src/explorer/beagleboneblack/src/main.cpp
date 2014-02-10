#include <explorer.h>
#include <camera.h>
#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>
#include <frame/thresh_frame.h>
#include <application/window.h>

#include <opencv2/opencv.hpp>

#include <i2c/i2c_bus.h>
#include <i2c/i2c_device.h>

#include "../project.h"

using namespace cv;

int main(int argc, char* argv[])
{
	Project* project = new Project();
	project->run();

	return 0;
}
