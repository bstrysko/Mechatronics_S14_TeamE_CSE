#ifndef _EXPLORARE_APPLICATION_APPLICATION_H_
#define _EXPLORARE_APPLICATION_APPLICATION_H_

#include <string>
#include <application/window.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Application
{
  private:
    int delay;
  protected:
    Application();

    int getDelay();
    void setDelay(int delay);

    Window* createWindow(string name);

    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual void keyPressed(char key) = 0;
  public:
    ~Application();

    void run();
};

#endif
