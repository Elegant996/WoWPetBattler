#ifndef PETABILITY_H
#define PETABILITY_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class PetAbility
{
friend class ScriptHelper;

public:
	PetAbility();
	~PetAbility(void);
	PetAbility(const PetAbility&);

	void Initialize(int, int, bool);
	void Remove();

	void UseAbility();

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

