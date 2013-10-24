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
	Q_PROPERTY(bool IsObject READ IsObject WRITE IsObject)
	Q_PROPERTY(bool OnSwapIn READ OnSwapIn WRITE OnSwapIn)

public:
	PetAura(quint16, qint8, bool);
	~PetAura(void);
	PetAura(const PetAura&);

	void RoundUpdate();

	QString GetName();
	quint16 GetAuraId();

	void IsObject(bool);
	void OnSwapIn(bool);

	bool IsObject();
	bool OnSwapIn();

private:
	QString name;
	quint16 auraId;
	qint8 cooldown, rounds, duration;
	PetType::Type petTypeId;
	bool isPassive, isFresh, isObject, onSwapIn;
};

#endif

