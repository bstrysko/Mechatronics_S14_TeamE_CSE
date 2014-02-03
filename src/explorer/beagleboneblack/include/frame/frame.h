#ifndef _EXPLORARE_FRAME_FRAME_H_
#define _EXPLORARE_FRAME_FRAME_H_

#include <opencv2/opencv.hpp>

using namespace cv;

class Frame
{
  private:
    Mat frame;
  protected:
    void create(Mat frame);
    ~Frame();
  public:
    Mat getMat();

    int getWidth();
    int getHeight();

    void resize(int width, int height);
};

#endif
