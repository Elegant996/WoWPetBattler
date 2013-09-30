#ifndef PETSTAGE_H
#define PETSTAGE_H

#include <QVector>
#include <QtAlgorithms>
#include <QDebug>
#include "PetTeam.h"

class PetStage
{
public:
	PetStage(void);
	~PetStage(void);
	PetStage(const PetStage&);

	PetTeam* GetPetTeam(int);

private:
	QVector<PetTeam*> petTeam;
};

#endif