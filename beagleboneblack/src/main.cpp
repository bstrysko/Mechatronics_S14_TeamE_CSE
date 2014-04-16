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

using namespace std;
using namespace cv;

void usage(string name);
int stringToInt(char* s);

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		usage(argv[0]);
		return 1;
	}

	string hostname = argv[1];
	int port = stringToInt(argv[2]);

	Project* project = new Project();
	project->run(hostname, port);

	return 0;
}

void usage(string name)
{
    cout << "usage: ./" << name << " [hostname] [port]" << endl;
}

int stringToInt(char* s)
{
    int result;

    result = atoi(s);

    if(result == 0 && s[0] != '0')
    {
        stringstream o;
        o << s << " is not a number";
        throw ios_base::failure(o.str());
    }

    return result;
}
