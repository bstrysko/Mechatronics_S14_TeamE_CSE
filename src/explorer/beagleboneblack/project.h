#ifndef _EXPLORARE_PROJECT_H_
#define _EXPLORARE_PROJECT_H_

#include <application/application.h>
#include <application/window.h>

#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>
#include <frame/thresh_frame.h>
#include <frame/text_frame.h>

#include <explorer.h>

#include <iostream>

using namespace std;

class Project : public Application
{
  protected:
    void setup();
    void loop();
    void keyPressed(char key);
  public:
    Project();
};

#endif
