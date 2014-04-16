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
 * The Application class provides a general
 * program structure with helper methods in order
 * to simplify the main code.
 *
 * Created On: 2/1/14
 */

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

    virtual void setup(string hostname, int port) = 0;
    virtual void loop() = 0;
    virtual void keyPressed(int key) = 0;
  public:
    ~Application();

    void run(string hostname, int port);
};

#endif
