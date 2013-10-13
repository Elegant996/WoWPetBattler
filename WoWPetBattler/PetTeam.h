#ifndef PETTEAM_H
#define PETTEAM_H

#include <QVector>
#include <QtAlgorithms>

#include "Pet.h"

class PetTeam
{
public:
	PetTeam(int);
	~PetTeam(void);
	PetTeam(const PetTeam&);

	void Remove();

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

