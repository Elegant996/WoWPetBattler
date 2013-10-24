#ifndef PET_H
#define PET_H

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QQueue>
#include <QtAlgorithms>

#include "PetAbility.h"
#include "PetAction.h"
#include "PetAura.h"
#include "PetBreed.h"
#include "PetHelper.h"
#include "PetType.h"

class Pet : public QObject
{
	Q_OBJECT
	Q_ENUMS(PetStatus)
	//Q_PROPERTY(QList<int> Statuses READ GetStatuses)
	//Q_PROPERTY(QQmlListProperty<PetAbility> Abilities READ GetAbilities)
	//Q_PROPERTY(QQmlListProperty<PetAura> Auras READ GetAuras)
	Q_PROPERTY(quint8 Level READ GetLevel)
	Q_PROPERTY(quint8 Type READ GetType)
	Q_PROPERTY(quint16 Health READ GetHealth WRITE SetHealth)
	Q_PROPERTY(quint16 MaxHealth READ GetMaxHealth WRITE SetMaxHealth)
	Q_PROPERTY(quint16 Power READ GetPower WRITE SetPower)
	Q_PROPERTY(quint16 Speed READ GetSpeed WRITE SetSpeed)

public:
	Pet();
	Pet(quint16, quint8, quint8, quint8);
	~Pet(void);
	Pet(const Pet&);

	//enum PetType { Humanoid, Dragonkin, Flying, Undead, Critter, Magic, Elemental, Beast, Aquatic, Mechanical };
	enum PetStatus { First, Second, Stunned, Rooted, Burning, Chilled, Bleeding, Webbed, Blinded, Poisoned, Evading, Asleep };

	void RoundUpdate();

	Q_INVOKABLE void AddStatus(PetStatus);
	Q_INVOKABLE bool HasStatus(PetStatus);
	int GetNumStatuses();
	Q_INVOKABLE PetStatus GetStatus(quint8);
	//QList<int> GetStatuses();

	void AddAbility(bool, quint8, qint8);
	void ReplaceAbility(quint8, bool, quint8, qint8);
	int GetNumAbilities();
	Q_INVOKABLE PetAbility* GetAbility(quint8);
	//QQmlListProperty<PetAbility> GetAbilities();

	void AddAura(quint16, qint8, bool);
	void RemoveAuras();
	int GetNumAuras();
	PetAura* GetAura(quint8);
	//QQmlListProperty<PetAura> GetAuras();

	void SetHealth(quint16);
	void SetMaxHealth(quint16);
	void SetPower(quint16);
	void SetSpeed(quint16);
	void RacialUsed(bool);

	quint16 GetSpeciesId();
	quint8 GetLevel();
	PetType::Type GetType();
	quint16 GetHealth();
	quint16 GetMaxHealth();
	quint16 GetPower();
	quint16 GetSpeed();
	bool RacialUsed();

private:
	QString name;
	quint16 speciesId;
	PetType::Type type;
	quint8 breed, quality, level;
	float baseHealth, basePower, baseSpeed;
	quint16 maxHealth, currentHealth, currentMaxHealth, currentPower, currentSpeed;

	bool racialUsed;
	PetAction *currentAction; //Determine how to use this.

	QJsonArray abilityList;
	QList<int> petStatuses;
	QList<PetAbility*> petAbilities;
	QList<PetAura*> petAuras;
	QQueue<int> petDamage;	//Placeholder, if needed.
};

#endif
