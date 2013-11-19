#ifndef PETABILITY_H
#define PETABILITY_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include "PetType.h"

class PetAbility : public QObject
{
	Q_OBJECT
	Q_PROPERTY(quint16 AbilityId READ GetAbilityId)

public:
	PetAbility(quint16, quint8, qint8, bool);
	~PetAbility(void);
	PetAbility(const PetAbility&);

	void RoundUpdate();

	void UseAbility();

	void SetCooldown(qint8);
	void IsVerified(bool);

	quint16 GetAbilityId();
	quint8 GetTier();
	qint8 GetCooldown();
	qint8 GetRounds();
	bool IsVerified();

private:
	QString name;
	quint16 abilityId;
	quint8 tier;
	qint8 cooldown, currentCooldown, rounds;
	PetType::Type petTypeId;
	bool isPassive, isVerified, usedThisTurn;
};

#endif

