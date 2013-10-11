#ifndef PETABILITY_H
#define PETABILITY_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <QtAlgorithms>

class PetAbility
{
public:
	PetAbility(int, int, bool);
	~PetAbility(void);
	PetAbility(const PetAbility&);

	void SetCooldown(int);
	void IsVerified(bool);

	int GetAbilityId();
	int GetCooldown();
	bool IsVerified();

private:
	QString name;
	int abilityId, cooldown, currentCooldown, rounds, petTypeId;
	bool isPassive, isVerified;
};

#endif

