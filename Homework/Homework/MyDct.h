#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class MyDct
{
public:
	MyDct();
	~MyDct();

	int dct(cv::Mat& image);
	int idct(cv::Mat& image);
	int idct(cv::Mat& image, int sleepTime);
private:
	void initDctMat();

	cv::Mat Array = cv::Mat(cv::Size(8, 8), CV_32FC1);
};

