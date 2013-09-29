#ifndef PETTEAM_H
#define PETTEAM_H

#include <QVector>
#include <QtAlgorithms>
#include "Pet.h"

class PetTeam
{
public:
	PetTeam(void);
	~PetTeam(void);

	void AddPet(int);

protected:
	QVector<Pet*> pet;
};

#endif

