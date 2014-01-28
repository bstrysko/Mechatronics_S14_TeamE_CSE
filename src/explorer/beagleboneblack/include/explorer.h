#ifndef _EXPLORARE_EXPLORER_H_
#define _EXPLORARE_EXPLORER_H_

#include "color.h"
#include "rgb_sensor.h"
#include "drive_controller.h"
#include "kinect.h"

class Explorer
{
  public:
    static bool init(Color defectColor);

    static RGBSensor getRGBSensor();
    static DriveController getDriveController();
    static Kinect getKinect();
};

#endif
