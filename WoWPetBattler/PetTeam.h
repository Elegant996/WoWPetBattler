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
	void SetActivePet(int);
	int GetActivePet();
	Pet* GetPet(int);

private:
	int activePet;
	QVector<Pet*> pet;
};

#endif

