#ifndef PETAURA_H
#define PETAURA_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

class PetAura
{
friend class ScriptHelper;

public:
	PetAura();
	~PetAura(void);
	PetAura(const PetAura&);

	void Initialize(int, int);
	void Remove();

	int GetAuraId();

private:
	QString name;
	int auraId, cooldown, rounds, duration, petTypeId;
	bool isPassive;
};

#endif

