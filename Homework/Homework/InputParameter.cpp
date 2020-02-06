#include "InputParameter.h"
#include <iostream>

InputParameter::InputParameter(int argc, char* argv[])
{
	if (argc != 5)
	{
		Available = false;
		return;
	}

	strcpy(inputImagePath,argv[1]);
	i_quantizationLevel = std::stoi(argv[2],0,10);
	i_deliveryMode = std::stoi(argv[3], 0, 10);
	i_latency = std::stoi(argv[4], 0, 10);

	if ((i_quantizationLevel < 0) || (i_quantizationLevel > 7))
	{
		Available = false;
		return;
	}

	if ((i_deliveryMode < 1) || (i_deliveryMode > 3))
	{
		Available = false;
		return;
	}

	Available = true;
}

InputParameter::~InputParameter()
{
}

char* InputParameter::getImagePath()
{
	return this->inputImagePath;
}

int InputParameter::getQuantizationLevel()
{
	return this->i_quantizationLevel;
}

int InputParameter::getDeliveryMode()
{
	return this->i_deliveryMode;
}

int InputParameter::getLatency()
{
	return this->i_latency;
}

bool InputParameter::isAvailable()
{
	return this->Available;
}

std::ostream& operator << (std::ostream& out, const InputParameter& p)
{
	if (p.Available == false)
	{
		out << "Available:" << p.Available << std::endl;
		return out;
	}
	out <<"ImagePath: "<< p.inputImagePath << std::endl;
	out <<"quantizationLevel: "<< p.i_quantizationLevel << std::endl;
	out <<"deliveryMode: "<< p.i_deliveryMode << std::endl;
	out <<"latency: "<< p.i_latency << std::endl;
	out <<"Available: "<< p.Available << std::endl;

	return out;
}
