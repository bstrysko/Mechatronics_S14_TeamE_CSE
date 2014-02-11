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

void Window::createSlider(string sliderName, int max, WindowSliderCallback callback)
{
	//Do not need n but will never remove sidebar during program execution
	int* n = new int;
	*n = 0;
	createTrackbar(sliderName, name, n, max, callback);
}

void Window::renderFrame(Frame frame)
{
	imshow(name, frame.getMat());
}

void Window::renderFrames2(Frame frame1, Frame frame2)
{
	Mat f1 = frame1.getMat();
	Mat f2 = frame2.getMat();

	Mat result(f1.rows, 2*f1.cols, f1.type());
	f1.copyTo(result(Rect(0, 0, f1.cols, f1.rows)));
	f2.copyTo(result(Rect(f1.cols, 0, f1.cols, f1.rows)));
	imshow(name, result);
}

void Window::renderFrames4(Frame frame1, Frame frame2, Frame frame3, Frame frame4)
{
	Mat f1 = frame1.getMat();
	Mat f2 = frame2.getMat();
	Mat f3 = frame3.getMat();
	Mat f4 = frame4.getMat();

	Mat result(2*f1.rows, 2*f1.cols, f1.type());
	f1.copyTo(result(Rect(0, 0, f1.cols, f1.rows)));
	f2.copyTo(result(Rect(f1.cols, 0, f1.cols, f1.rows)));
	f3.copyTo(result(Rect(0, f1.rows, f1.cols, f1.rows)));
	f4.copyTo(result(Rect(f1.cols, f1.rows, f1.cols, f1.rows)));
	
	imshow(name, result);
}
