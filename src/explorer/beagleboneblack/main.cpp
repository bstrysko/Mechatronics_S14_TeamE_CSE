#include <explorer.h>
#include <camera.h>
#include <frame/rgb_frame.h>
#include <frame/hsv_frame.h>
#include <frame/thresh_frame.h>
#include <application/window.h>

#include <opencv2/opencv.hpp>

using namespace cv;

//

int main()
{
	Explorer::init();

	Camera* camera = Explorer::getCamera();

	Window window_video("video");
	Window window_hsv("hsv");
	Window window_thresh("thresh");
	//Window window_red("red");
	Window window_contours("contours");
	
	unsigned long long distance = 0;

	while(true)
	{
		RGBFrame rgb_frame = camera->getRGBFrame();

		//rgb_frame.resize(1024, 960);
		
		Mat f = rgb_frame.getMat();

		if(!f.data)
		{
			continue;
		}

		std::ostringstream s;
        s << "Distance: " << distance;
        std::string text(s.str());
		rgb_frame.printText(Point(20,20), Color::GREEN, text);

		HSVFrame hsv_frame(rgb_frame);
		ThreshFrame thresh_frame(rgb_frame);

		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;
		findContours(thresh_frame.getMat(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		window_video.renderFrame(rgb_frame);
		window_hsv.renderFrame(hsv_frame);
		window_thresh.renderFrame(thresh_frame);

		vector<Mat> bgr_planes;
		split(rgb_frame.getMat(), bgr_planes );

		int histSize = 256;

		float range[] = { 0, 256 } ;
		const float* histRange = { range };

		bool uniform = true; bool accumulate = false;

		Mat b_hist, g_hist, r_hist;

		calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate );
		calcHist( &bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate );

		int hist_w = 512; int hist_h = 400;
		int bin_w = cvRound( (double) hist_w/histSize );

		Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );

		normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
		normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

		for( int i = 1; i < histSize; i++ )
		{
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) ,
				Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ),
                Scalar( 255, 0, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(g_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(g_hist.at<float>(i)) ),
                Scalar( 0, 255, 0), 2, 8, 0  );
			line( histImage, Point( bin_w*(i-1), hist_h - cvRound(r_hist.at<float>(i-1)) ) ,
                Point( bin_w*(i), hist_h - cvRound(r_hist.at<float>(i)) ),
                Scalar( 0, 0, 255), 2, 8, 0  );
		}

		//namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE );
		//imshow("calcHist Demo", histImage );
		//window_red.renderFrame(RGBFrame(bgr_planes[2]));

		if(waitKey(50) >= 0){}

        distance++;
	}

	return 0;
}
