#ifndef PETSTATS_H
#define PETSTATS_H

#include <QDataStream>
#include <QtCore/qmath.h>

class PetStats
{
public:
	static quint16 CalculateHealth(float, float, float, float);
	static quint16 CalculatePower(float, float, float, float);
	static quint16 CalculateSpeed(float, float, float, float);

private:
	static quint16 Round(float);
};

#endif

