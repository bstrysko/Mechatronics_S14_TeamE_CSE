#ifndef _EXPLORARE_APPLICATION_WINDOW_H_
#define _EXPLORARE_APPLICATION_WINDOW_H_

#include <string>
#include <opencv2/opencv.hpp>

#include <frame/frame.h>

using namespace std;
using namespace cv;

class Window
{
  private:
    string name;
  public:
    Window(string name);
    ~Window(); 

    string getName();
    void renderFrame(Frame frame);
};

#endif
