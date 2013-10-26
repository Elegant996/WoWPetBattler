#ifndef PETSTATS_H
#define PETSTATS_H

#include <QtCore/qmath.h>

class PetStats
{
public:
	static int CalculateHealth(float, float, float, float);
	static int CalculatePower(float, float, float, float);
	static int CalculateSpeed(float, float, float, float);

private:
	static int Round(float);
};

#endif

