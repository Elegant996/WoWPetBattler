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
#include "PetAura.h"
#include "PetBreed.h"
#include "PetHelper.h"

class Pet
{
public:
	Pet();
	Pet(int, int, int, int);
	~Pet(void);
	Pet(const Pet&);

	void AddAbility(bool, int, int);
	void ReplaceAbility(int, bool, int, int);
	PetAbility* GetAbility(int);

	void AddAura(int, int);
	void RemoveAuras();
	PetAura* GetAura(int);

	void SetHealth(int);
	void SetMaxHealth(int);
	void SetPower(int);
	void SetSpeed(int);

	int GetSpeciesId();
	int GetLevel();
	int GetHealth();
	int GetMaxHealth();
	int GetPower();
	int GetSpeed();

private:
	QString name;
	int speciesId, breed, quality, level;
	float type, baseHealth, basePower, baseSpeed;
	int currentHealth, currentMaxHealth, currentPower, currentSpeed;
	QJsonArray abilityList;
	QVector<PetAbility*> petAbility;
	QVector<PetAura*> petAura;
};

#endif
