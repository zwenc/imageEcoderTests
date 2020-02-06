#pragma once
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

class MyQuantification
{
public:
	MyQuantification(int q, int delay);
	~MyQuantification();

	int Quantification(cv::Mat& image);
	int iQuantification(cv::Mat& image);
	int iQuantification(cv::Mat& image, int ACNums);
	int iQuantification_bit(cv::Mat& image, int BitNums);

private:
	int m_Quantification;
	int m_delay;
	cv::Mat m_table = cv::Mat(8, 8, CV_32FC1);
	cv::Mat TableAvailableMark = cv::Mat(8, 8, CV_32FC1);

	int QuantificationTableInit();
	int generateMarkMat(cv::Mat& A,int ACNums);
	int generateBlockByBit(cv::Mat& A, int bits);
	int generateTableAvailableMark();
};

