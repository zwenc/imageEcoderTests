#include "MyQuantification.h"
#include <iostream>

float msk[8][8] = { 
{16,11,10,16,24,40,51,61},
{12,12,14,19,26,58,60,55},
{14,13,16,24,40,57,69,56},
{14,17,22,29,51,87,80,62},
{18,22,37,56,68,109,103,77},
{24,35,55,64,81,104,113,92},
{49,64,78,87,103,121,120,101},
{72,92,95,98,112,100,103,99} };


MyQuantification::MyQuantification(int q, int delay) : m_Quantification(q), m_delay(delay)
{
	this->QuantificationTableInit();
	this->generateTableAvailableMark();

	//m_table = m_table.mul(TableAvailableMark);

	//for (int i = 0; i < 8; i++)
	//{
	//	for (int j = 0; j < 8; j++)
	//	{
	//		if (TableAvailableMark.ptr<float>(i)[j] < 0.0001)
	//			m_table.ptr<float>(i)[j] = 100000;
	//	}
	//}

	//std::cout << m_table << std::endl;
}

MyQuantification::~MyQuantification()
{
	// none
}

int MyQuantification::Quantification(cv::Mat& image)
{
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();

	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) /= this->m_table;
				for (int x = 0; x < 8; x++)
				{
					for (int y = 0; y < 8; y++)
					{
						if (TableAvailableMark.ptr<float>(x)[y] < 0.0001)
							channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)).ptr<float>(x)[y] = 0;
					}
				}

				//std::cout << channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) << std::endl;

			}
		}

	cv::merge(channels, image);
	return 0;
}

int MyQuantification::iQuantification(cv::Mat& image)
{
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)).mul(this->m_table);
			}
		}

	cv::merge(channels, image);
	return 0;
}

int MyQuantification::iQuantification(cv::Mat& image, int ACNums)
{
	cv::Mat markBlock = cv::Mat(8, 8, CV_32FC1);
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::split(image, channels);

	generateMarkMat(markBlock, ACNums);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)).mul(markBlock).mul(this->m_table);
			}
		}

	cv::merge(channels, image);
	return 0;
}

int MyQuantification::iQuantification_bit(cv::Mat& image, int BitNums)
{
	cv::Mat markBlock;
	cv::Mat temp;
	cv::Mat beiTemp;
	std::vector<cv::Mat> channels;
	cv::Size size = image.size();
	cv::split(image, channels);

	for (int i = 0; i < size.height; i += 8)
		for (int j = 0; j < size.width; j += 8)
		{
			for (int k = 0; k < 3; k++)
			{
				beiTemp = channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) * 10000;
				beiTemp.convertTo(markBlock, CV_32SC1);
				this->generateBlockByBit(markBlock, BitNums);


				markBlock /= 10000;
				markBlock.convertTo(temp, CV_32FC1);

				channels.at(k)(cv::Range(i, i + 8), cv::Range(j, j + 8)) = temp.mul(this->m_table);
			}
		}

	cv::merge(channels, image);
	return 0;
}

int MyQuantification::QuantificationTableInit()
{
	m_table = cv::Mat(8,8, CV_32FC1, msk);
	return 0;
}

int MyQuantification::generateMarkMat(cv::Mat& A, int ACNums)
{
	bool startleft = true;
	int x = 0;
	int y = 0;

	for (int i = 0; i < 64; i++)
	{
		if (i <= ACNums)
			A.ptr<float>(x)[y] = 1.0;
		else
			A.ptr<float>(x)[y] = 0.0;

		if (((x == 0) || (y == 7)) && (startleft))
		{
			startleft = false;
			if (y == 7)
				x += 1;
			else
				y += 1;
		}
		else if (((x == 7) || (y == 0)) && ( startleft == false))
		{
			startleft = true;
			if (x == 7)
				y += 1;
			else
				x += 1;
		}
		else if (startleft == false)
		{
			x += 1;
			y -= 1;
		}
		else
		{
			x -= 1;
			y += 1;
		}
	}
	return 0;
}

int MyQuantification::generateBlockByBit(cv::Mat& A, int bits)
{
	int32_t temp = 0;
	for (int i = 0; i < bits; i++)
	{
		temp <<= 1;
		temp |= 0x01;
	}

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (A.ptr<int>(i)[j] >= 0)
			{
				A.ptr<int>(i)[j] = A.ptr<int>(i)[j] & (temp);
			}
			else
			{
				A.ptr<int>(i)[j] = -((-A.ptr<int>(i)[j]) & (temp));
			}
		} 
	}
	return 0;
}

int MyQuantification::generateTableAvailableMark()
{
	int temp[8] = { 0,5,14,27,42,53,60,63 };

	generateMarkMat(TableAvailableMark, temp[m_Quantification]);

	return 0;
}
