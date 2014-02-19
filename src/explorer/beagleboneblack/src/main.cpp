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
 * Contains main.
 * Creates a Project and runs it.
 *
 * Created On: 2/1/14
 */

#include "../project.h"

using namespace cv;

int main(int argc, char* argv[])
{
	Project* project = new Project();
	project->run();

	return 0;
}
