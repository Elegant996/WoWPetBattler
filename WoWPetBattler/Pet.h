#ifndef PET_H
#define PET_H

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <QtAlgorithms>

#include "PetAbility.h"
#include "PetBreed.h"
#include "PetHelper.h"

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
	QString name;
	int speciesID, breed, quality, level;
	float type, baseHealth, basePower, baseSpeed;
	int currentHealth, currentMaxHealth, currentPower, currentSpeed;
	QJsonArray abilityList;
	QVector<PetAbility*> petAbility;
};

#endif
