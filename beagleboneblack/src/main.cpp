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

#include <sstream>
#include <vector>

using namespace std;
using namespace cv;

int stringToInt(char* s);

int main(int argc, char* argv[])
{
	vector<string> args;

	for(int i = 0; i < argc; i++)
	{
		args.push_back(string(argv[i]));
	}

	Project* project = new Project();
	project->run(args);

	return 0;
}
