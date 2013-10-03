#ifndef PET_H
#define PET_H

#include <QVector>
#include <QtAlgorithms>
#include "PetAbility.h"

class Pet
{
public:
	Pet(int, int, int, int);
	~Pet(void);
	Pet(const Pet&);

	void AddAbility(bool, int, int);
	PetAbility* GetAbility(int);

	void SetHealth(int);
	void SetMaxHealth(int);
	void SetPower(int);
	void SetSpeed(int);

	int GetSpeciesID();
	int GetHealth();
	int GetMaxHealth();
	int GetPower();
	int GetSpeed();

private:
	int speciesID, breed, quality, level;
	int type, baseHealth, basePower, baseSpeed;
	int currentHealth, currentMaxHealth, currentPower, currentSpeed;
	QVector<PetAbility*> petAbility;
};

#endif
