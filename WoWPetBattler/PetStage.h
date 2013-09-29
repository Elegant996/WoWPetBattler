#ifndef PETSTAGE_H
#define PETSTAGE_H

#include <QVector>
#include <QVectorIterator>
#include <QtAlgorithms>
#include "PetTeam.h"

class PetStage
{
public:
	PetStage(void);
	~PetStage(void);
	PetStage(const PetStage&);
	PetStage& operator=(const PetStage&);

	PetTeam* GetPetTeam(int);

private:
	QVector<PetTeam*> petTeam;
};

#endif