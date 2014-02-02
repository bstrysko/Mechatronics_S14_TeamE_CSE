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
 * Implementation of Application class.
 *
 * Created On: 2/1/14
 */

#include <application/application.h>

Application::Application()
{
	this->delay = 10;	
}

Application::~Application()
{
}

void Application::run()
{	
	setup();

	while(true)
	{
		loop();

		char key = cvWaitKey(delay);

		if(key >= 0)
		{
			keyPressed(key);
		}
	}
}

int Application::getDelay()
{
	return delay;
}

void Application::setDelay(int delay)
{
	this->delay = delay;
}

Window* Application::createWindow(string name)
{
	return new Window(name);
}
