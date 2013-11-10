#ifndef PETAURA_H
#define PETAURA_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

#include "PetType.h"

class PetAura : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString Name READ GetName)
	Q_PROPERTY(quint16 AuraId READ GetAuraId)
	Q_PROPERTY(bool IsFresh READ IsFresh WRITE IsFresh)
	Q_PROPERTY(bool IsObject READ IsObject WRITE IsObject)
	Q_PROPERTY(bool OnSwapIn READ OnSwapIn WRITE OnSwapIn)
	Q_PROPERTY(quint16 Power READ GetPower WRITE SetPower)
	Q_PROPERTY(quint8 Charges READ GetCharges WRITE SetCharges)

public:
	PetAura(quint16, qint8, bool);
	PetAura(quint16, qint8, bool, quint16);
	~PetAura(void);
	PetAura(const PetAura&);

	void RoundUpdate();

	void UpdateAura(int, bool);
	void UpdateAura(int, bool, quint16);

	void SetPower(quint16);
	void SetCharges(quint8);
	void IsFresh(bool);
	void IsObject(bool);
	void OnSwapIn(bool);

	QString GetName();
	quint16 GetAuraId();
	qint8 GetDuration();
	quint16 GetPower();
	quint8 GetCharges();
	bool IsFresh();
	bool IsObject();
	bool OnSwapIn();	

private:
	QString name;
	quint16 auraId, power;
	qint8 cooldown, rounds, duration;
	PetType::Type petTypeId;
	bool isPassive, isFresh, isObject, onSwapIn;
	quint8 charges;
};

#endif

