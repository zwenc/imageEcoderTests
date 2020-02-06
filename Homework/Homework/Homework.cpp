#include <iostream>
#include <string.h>
#include "InputParameter.h"
#include "Image.h"   // will delete
#include "MyDct.h"
#include "MyQuantification.h"

// include opencv libraries but not use the DCT and quantization functions
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

// set default image width and height
#define defaultWidth 1920
#define defaultHeight 1080

int getACnum(cv::Mat& image,cv::Mat& dst,int num)
{
	std::vector<cv::Mat> channels;
	cv::Mat temp;
	cv::Size size = image.size();

	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)).ptr<float>(i)[k];
			}
		}

	cv::merge(channels, image);
	return 0;
}

int modeOne(cv::Mat& image, MyQuantification& mq, MyDct& myDct,int sleepTime)
{	
	mq.iQuantification(image);
	myDct.idct(image, sleepTime);

	return 0;
}

int modeTwo(cv::Mat& image, MyQuantification& mq, MyDct& myDct, int sleepTime)
{
	cv::Mat temp;
	cv::Mat timage;
	for (int i = 0; i < 64; i++)
	{
		std::cout << "AC coefficients : " << i << std::endl;
		image.convertTo(temp, CV_32FC1);
		mq.iQuantification(temp, i);
		myDct.idct(temp);

		temp.convertTo(timage, CV_8UC1);
		cv::imshow("windows", timage);

		if (cv::waitKey(sleepTime) == 27)
		{
			break;
		}
	}
	return 0;
}

int modeThree(cv::Mat& image, MyQuantification& mq, MyDct& myDct, int sleepTime)
{
	cv::Mat temp;
	cv::Mat timage;
	for (int i = 1; i < 32; i++)
	{
		std::cout << "bit num : " << i << std::endl;
		image.convertTo(temp, CV_32FC1);
		mq.iQuantification_bit(temp, i);
		myDct.idct(temp);

		temp.convertTo(timage, CV_8UC1);
		cv::imshow("windows", timage);

		if (cv::waitKey(sleepTime) == 27)
		{
			break;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	InputParameter param = InputParameter(argc, argv);
	std::cout << param << std::endl;
	if (!param.isAvailable())
	{
		std::cout << "Parameter error, please enter again!" << std::endl;
		return -1;
	}

	cv::Mat image = cv::imread(param.getImagePath());
	cv::Mat fimage;
	cv::Mat timage; // temp image
	//cv::imshow("image1",image);
	//cv::waitKey(0);

	std::cout << image.size() << std::endl;  // print the image size


	MyDct myDct = MyDct();
	MyQuantification mq = MyQuantification(param.getQuantizationLevel(), param.getLatency());

	image.convertTo(fimage, CV_32FC1);

	// dct and Quantification
	myDct.dct(fimage);
	mq.Quantification(fimage);

	switch (param.getDeliveryMode())
	{
	case 1:modeOne(fimage,mq,myDct, param.getLatency()); break;
	case 2:modeTwo(fimage, mq, myDct, param.getLatency());  break;
	case 3:modeThree(fimage, mq, myDct, param.getLatency());  break;
	default:
		std::cout << "This code will not execute unless a miracle occurs" << std::endl;
		break;
	}

	//getACnum(fimage, timage, 1);
	////mq.iQuantification(fimage);
	////myDct.idct(fimage);
	//timage.convertTo(image, CV_8UC1);

	//cv::imshow("image", image);
	//cv::waitKey(0);


	//MyImage image = MyImage();

	//// read image to Data array
	//image.setWidth(defaultWidth);
	//image.setHeight(defaultHeight);
	//image.setImagePath(param.getImagePath());
	//image.ReadImage();



	// print some infomation
	//std::cout << "this program is only for 1920*1080 image" << std::endl;
}

