#pragma once
#include <string>
class InputParameter
{
private:
	char inputImagePath[100];
	int i_quantizationLevel;
	int i_deliveryMode;
	int i_latency;
	bool Available;

public:
	InputParameter(int argc, char* argv[]);
	~InputParameter();

	char* getImagePath();
	int getQuantizationLevel();
	int getDeliveryMode();
	int getLatency();
	bool isAvailable();

	friend std::ostream& operator << (std::ostream& out, const InputParameter& p);
};

