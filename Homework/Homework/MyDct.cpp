#include "MyDct.h"
#include <iostream>
#include <windows.h>

# define pi 3.141592

MyDct::MyDct()
{
	this->initDctMat();
}

MyDct::~MyDct()
{
}

int MyDct::dct(cv::Mat& image)
{
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::Mat timage;

	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				//X = AXAT 
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = Array * channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) * Array.t();
				//用mask量化
				//image(cv::Range(i, i + 8), Range(j, j + 8)) /= mask;
			}
			//cv::merge(channels, image);
			//image.convertTo(timage, CV_8UC1);
			//cv::imshow("windows", timage);

			//if (cv::waitKey(20) == 27)
			//{
			//	goto end;
			//}
		}

	cv::merge(channels, image);

end:
	return 0;
}

int MyDct::idct(cv::Mat& image)
{
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
			////还原量化
			//image(cv::Range(i, i + 8), cv::Range(j, j + 8)) = image(cv::Range(i, i + 8), cv::Range(j, j + 8)).mul(mask);
			//X = ATXA
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = this->Array.t() * channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) * this->Array;
			}
		}

	cv::merge(channels, image);
	return 0;
}

int MyDct::idct(cv::Mat& image, int sleepTime)
{
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::split(image, channels);
	cv::Mat timage;


	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				////还原量化
				//image(cv::Range(i, i + 8), cv::Range(j, j + 8)) = image(cv::Range(i, i + 8), cv::Range(j, j + 8)).mul(mask);
				//X = ATXA
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = this->Array.t() * channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) * this->Array;
			}

			cv::merge(channels, image);
			image.convertTo(timage, CV_8UC1);
			cv::imshow("windows", timage);

			if (cv::waitKey(sleepTime) == 27)
			{
				goto end;
			}
		}

end:
	return 0;
}

void MyDct::initDctMat()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			float a;
			if (i == 0)
				a = sqrt(1.0 / 8.0);
			else
				a = sqrt(2.0 / 8.0);

			this->Array.ptr<float>(i)[j] = a * cos((j + 0.5) * pi * i / 8);
		}

	//std::cout << this->Array;
}

