#ifndef _EXPLORARE_FRAME_FRAME_H_
#define _EXPLORARE_FRAME_FRAME_H_

#include <color.h>

#include <string>

#include <opencv2/opencv.hpp>

using namespace std;
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

    void printText(int x, int y, Color color, string text);
};

#endif
