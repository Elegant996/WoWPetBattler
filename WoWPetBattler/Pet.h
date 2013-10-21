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
#include "PetAura.h"
#include "PetBreed.h"
#include "PetHelper.h"

class Pet : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<QString> statuses READ GetStatuses)
	Q_PROPERTY(QQmlListProperty<PetAbility> abilities READ GetAbilities)
	Q_PROPERTY(QQmlListProperty<PetAura> auras READ GetAuras)
	Q_PROPERTY(int level READ GetLevel)
	Q_PROPERTY(int type READ GetType)
	Q_PROPERTY(int health READ GetHealth WRITE SetHealth)
	Q_PROPERTY(int maxHealth READ GetMaxHealth WRITE SetMaxHealth)
	Q_PROPERTY(int power READ GetPower WRITE SetPower)
	Q_PROPERTY(int speed READ GetSpeed WRITE SetSpeed)

public:
	Pet();
	Pet(int, int, int, int);
	~Pet(void);
	Pet(const Pet&);

	void RoundUpdate();

	bool HasStatus(QString);
	int GetNumStatuses();
	QString* GetStatus(int);
	QQmlListProperty<QString> GetStatuses();

	void AddAbility(bool, int, int);
	void ReplaceAbility(int, bool, int, int);
	int GetNumAbilities();
	PetAbility* GetAbility(int);
	QQmlListProperty<PetAbility> GetAbilities();

	void AddAura(int, int, bool);
	void RemoveAuras();
	int GetNumAuras();
	PetAura* GetAura(int);
	QQmlListProperty<PetAura> GetAuras();

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
	int maxHealth, currentHealth, currentMaxHealth, currentPower, currentSpeed;
	QJsonArray abilityList;
	QList<QString*> petStatuses;
	QList<PetAbility*> petAbilities;
	QList<PetAura*> petAuras;
	QQueue<int> petDamage;	//Placeholder
};

#endif
