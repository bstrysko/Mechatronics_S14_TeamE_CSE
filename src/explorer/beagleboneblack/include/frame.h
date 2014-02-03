#ifndef _EXPLORARE_FRAME_H_
#define _EXPLORARE_FRAME_H_

#include <opencv2/opencv.hpp>

using namespace cv;

class Frame
{
  private:
    Mat frame;
  public:
    Frame(Mat frame);
    ~Frame();

    Frame toHSVFrame();

    Mat getMat();
};

#endif
