#ifndef PETAURA_H
#define PETAURA_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

class PetAura : public QObject
{
	Q_OBJECT

public:
	PetAura(int, int, bool);
	~PetAura(void);
	PetAura(const PetAura&);

	void RoundUpdate();

private:
	QString name;
	int auraId, cooldown, rounds, duration, petTypeId;
	bool isPassive, isFresh;
};

#endif

