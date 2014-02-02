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
 * The Project class is where all the code specific
 * to the CSI challenge will go(path planning, etc).
 *
 * Created On: 2/1/14
 */

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
