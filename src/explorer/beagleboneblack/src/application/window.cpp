#include <application/window.h>

Window::Window(string name)
{
	this->name = name;

	namedWindow(name, 1);
}

Window::~Window()
{
}

string Window::getName()
{
	return name;
}

void Window::renderFrame(Frame frame)
{
	imshow(name, frame.getMat());
}
