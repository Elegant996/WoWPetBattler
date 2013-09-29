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
	PetTeam(const PetTeam&);
	PetTeam& operator=(const PetTeam&);

	void AddPet(int);
	Pet* GetPet(int);

private:
	QVector<Pet*> pet;
};

#endif

