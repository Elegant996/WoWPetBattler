#ifndef PETAURA_H
#define PETAURA_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class PetAura
{
public:
	PetAura(int, int);
	~PetAura(void);
	PetAura(const PetAura&);

private:
	QString name;
	int auraId, cooldown, rounds, duration, petTypeId;
	bool isPassive;
};

#endif

