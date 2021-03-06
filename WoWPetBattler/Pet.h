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

#include "PetAbility.h"
#include "PetAction.h"
#include "PetAura.h"
#include "PetBreed.h"
#include "PetStats.h"
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
	Q_PROPERTY(quint16 NormalMaxHealth READ GetNormalMaxHealth)
	Q_PROPERTY(quint16 NormalPower READ GetNormalPower)
	Q_PROPERTY(quint16 NormalSpeed READ GetNormalSpeed)
	Q_PROPERTY(bool IsDead READ IsDead)
	Q_PROPERTY(quint16 LastKnownHealth READ GetLastKnownHealth WRITE SetLastKnownHealth)
	Q_PROPERTY(quint16 Health READ GetHealth WRITE SetHealth)
	Q_PROPERTY(quint16 MaxHealth READ GetMaxHealth WRITE SetMaxHealth)
	Q_PROPERTY(float HealthPercentage READ GetHealthPercentage)
	Q_PROPERTY(quint16 Power READ GetPower WRITE SetPower)
	Q_PROPERTY(quint16 Speed READ GetSpeed WRITE SetSpeed)
	Q_PROPERTY(quint8 NumAuras READ GetNumAuras)
	Q_PROPERTY(float AccuracyOffset READ GetAccuracyOffset WRITE SetAccuracyOffset)
	Q_PROPERTY(float AvoidanceRating READ GetAvoidanceRating WRITE SetAvoidanceRating)
	Q_PROPERTY(float CriticalStrikeRating READ GetCriticalStrikeRating WRITE SetCriticalStrikeRating)
	Q_PROPERTY(float DamageModifier READ GetDamageModifier WRITE SetDamageModifier)
	Q_PROPERTY(float HealingModifier READ GetHealingModifier WRITE SetHealingModifier)
	Q_PROPERTY(float DefenseModifier READ GetDefenseModifier WRITE SetDefenseModifier)
	Q_PROPERTY(int DamageOffset READ GetDamageOffset WRITE SetDamageOffset)
	Q_PROPERTY(PetAction* CurrentAction READ GetCurrentAction)
	Q_PROPERTY(bool RacialUsed READ RacialUsed WRITE RacialUsed)
	Q_PROPERTY(bool AttackedThisRound READ AttackedThisRound WRITE AttackedThisRound)

public:
	Pet();
	Pet(quint16, quint8, quint8, quint8);
	~Pet(void);
	Pet(const Pet&);

	enum PetStatus { First, Second, Stunned, Rooted, Burning, Chilled, Polymorphed,
					Webbed, Blinded, Poisoned, Bleeding, Burrowed, Resilient, Asleep,
					Flying, Unkillable, Swapping, Underwater };

	void RoundUpdate();

	Q_INVOKABLE void AddStatus(PetStatus);
	Q_INVOKABLE void RemoveStatus(PetStatus);
	Q_INVOKABLE bool HasStatus(PetStatus);
	Q_INVOKABLE int GetNumStatuses();
	Q_INVOKABLE PetStatus GetStatus(quint8);
	//QList<int> GetStatuses();

	void AddAbility(bool, bool, quint8, qint8);
	void ReplaceAbility(quint8, bool, quint8, qint8);
	int GetNumAbilities();
	Q_INVOKABLE PetAbility* GetAbility(quint8);
	//QQmlListProperty<PetAbility> GetAbilities();

	Q_INVOKABLE void AddAura(quint16, qint8, bool);
	Q_INVOKABLE void AddAura(quint16, qint8, bool, quint8, quint8, quint16);
	Q_INVOKABLE void RemoveAura(quint8);
	Q_INVOKABLE void RemoveAuraId(quint16);
	void RemoveAuras();
	Q_INVOKABLE bool HasAura(quint16);
	Q_INVOKABLE quint8 GetNumAuras();
	Q_INVOKABLE PetAura* GetAura(quint8);
	Q_INVOKABLE PetAura* GetLastAura();
	//QQmlListProperty<PetAura> GetAuras();

	bool IsDead();

	void SetLastKnownHealth(quint16);
	void SetHealth(quint16);
	void SetMaxHealth(quint16);
	void SetPower(quint16);
	void SetSpeed(quint16);
	void SetAccuracyOffset(float);
	void SetAvoidanceRating(float);
	void SetCriticalStrikeRating(float);
	void SetDamageModifier(float);
	void SetHealingModifier(float);
	void SetDefenseModifier(float);
	void SetDamageOffset(int);
	void RacialUsed(bool);
	void AttackedThisRound(bool);

	QString GetName();
	quint16 GetSpeciesId();
	quint8 GetLevel();
	PetType::Type GetType();
	quint16 GetNormalMaxHealth();
	quint16 GetNormalPower();
	quint16 GetNormalSpeed();
	quint16 GetLastKnownHealth();
	quint16 GetHealth();
	quint16 GetMaxHealth();
	float GetHealthPercentage();
	quint16 GetPower();
	quint16 GetSpeed();
	float GetAccuracyOffset();
	float GetAvoidanceRating();
	float GetCriticalStrikeRating();
	float GetDamageModifier();
	float GetHealingModifier();
	float GetDefenseModifier();
	int GetDamageOffset();
	Q_INVOKABLE PetAction* GetCurrentAction();
	bool RacialUsed();
	bool AttackedThisRound();

private:
	QString name;
	quint16 speciesId;
	PetType::Type type;
	quint8 breed, quality, level;
	float baseHealth, basePower, baseSpeed;
	quint16 normalMaxHealth, normalPower, normalSpeed, lastKnownHealth;
	quint16 currentHealth, currentMaxHealth, currentPower, currentSpeed;
	float accuracyOffset, avoidanceRating, criticalStrikeRating;
	float damageModifier, healingModifier, defenseModifier;
	int damageOffset;

	bool racialUsed, attackedThisRound;
	PetAction *currentAction;

	QJsonArray abilityList;
	QList<int> petStatuses;
	QList<PetAbility*> petAbilities;
	QList<PetAura*> petAuras;
	QQueue<int> petDamage;	//Placeholder, if needed.
};

#endif
