#ifndef PETABILITY_H
#define PETABILITY_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

class PetAbility : public QObject
{
	Q_OBJECT

public:
	PetAbility(int, int, bool);
	~PetAbility(void);
	PetAbility(const PetAbility&);

	void RoundUpdate();

	void SetCooldown(int);
	void IsVerified(bool);

	int GetAbilityId();
	int GetCooldown();
	bool IsVerified();

private:
	QString name;
	int abilityId, cooldown, currentCooldown, rounds, petTypeId;
	bool isPassive, isVerified, usedThisTurn;
};

#endif

