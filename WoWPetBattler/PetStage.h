#ifndef PETSTAGE_H
#define PETSTAGE_H

#include <QVector>
#include <QtAlgorithms>
#include "PetTeam.h"

class PetStage
{
public:
	PetStage(void);
	~PetStage(void);

protected:
	QVector<PetTeam*> petTeam;
};

#endif