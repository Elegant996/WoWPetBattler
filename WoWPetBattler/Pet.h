#ifndef PET_H
#define PET_H

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <QtAlgorithms>

#include <QDebug>

#include "PetAbility.h"
#include "PetAura.h"
#include "PetBreed.h"
#include "PetHelper.h"

class Pet
{
friend class ScriptHelper;

public:
	Pet();
	Pet(int, int, int, int);
	~Pet(void);
	Pet(const Pet&);

	void Initialize(int speciesId, int breed, int quality, int level);
	void Remove();

	void AddAbility(bool, int, int);
	void ReplaceAbility(int, bool, int, int);
	int GetNumAbilities();
	PetAbility* GetAbility(int);

	void AddAura(int, int);
	void RemoveAuras();
	int GetNumAuras();
	PetAura* GetAura(int);

	int GetNumStatus();
	QString* GetStatus(int);
	bool HasStatus(QString);

	void SetHealth(int);
	void SetMaxHealth(int);
	void SetPower(int);
	void SetSpeed(int);

	int GetSpeciesId();
	int GetLevel();
	int GetType();
	int GetHealth();
	int GetMaxHealth();
	int GetPower();
	int GetSpeed();

private:
	QString name;
	int speciesId, breed, type, quality, level;
	float baseHealth, basePower, baseSpeed;
	int currentHealth, currentMaxHealth, currentPower, currentSpeed;
	QJsonArray abilityList;
	QVector<QString*> petStatus;
	QVector<PetAbility*> petAbility;
	QVector<PetAura*> petAura;
};

#endif
