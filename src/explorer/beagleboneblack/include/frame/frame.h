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
 * The virtual Frame class represents
 * a generic image frame with no specific contents.
 *
 * Created On: 2/1/14
 */

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
  public:
    ~Frame();
    Mat getMat();

    int getWidth();
    int getHeight();

    void resize(int width, int height);

    void printText(Point point, Color color, ostringstream& stream);
    void printText(Point point, Color color, string text);
};

#endif
