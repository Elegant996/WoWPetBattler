#ifndef PET_H
#define PET_H

#include <QVector>
#include <QtAlgorithms>
#include "PetAbility.h"

class Pet
{
public:
	Pet(int);
	~Pet(void);
	Pet(const Pet&);
	Pet& operator=(const Pet&);

	void AddAbility(int, int, bool);
	PetAbility* GetPetAbility(int);

	int GetSpeciesID();
	int GetHealth();
	int GetPower();
	int GetSpeed();

private:
	int speciesID, type, health, power, speed;
	QVector<PetAbility*> petAbility;
};

#endif
