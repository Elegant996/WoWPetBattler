#ifndef PETHELPER_H
#define PETHELPER_H

#include <math.h>

class PetHelper
{
public:
	static int CalculateHealth(float, float, float, float);
	static int CalculatePower(float, float, float, float);
	static int CalculateSpeed(float, float, float, float);

private:
	static int Round(float);
};

#endif

