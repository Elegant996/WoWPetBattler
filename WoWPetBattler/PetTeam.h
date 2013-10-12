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

	void AddPet();
	void AddPet(int, int, int, int);

	void SetActivePet(int);
	Pet* GetActivePet();
	int GetActivePetIndex();

	int GetNumPets();
	Pet* GetPet(int);

private:
	int activePet;
	QVector<Pet*> pet;
};

#endif

