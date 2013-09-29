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

	void AddAbility(int, int, bool);
	void UpdateCooldown(int, int);
	void VerifyAbility(int, bool);

	int GetSpeciesID();
	int GetHealth();
	int GetPower();
	int GetSpeed();

private:
	int speciesID, health, power, speed;
	QVector<PetAbility*> petAbility;
};

#endif
