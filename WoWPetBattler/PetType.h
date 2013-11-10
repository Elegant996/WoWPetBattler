#ifndef PETTYPE_H
#define PETTYPE_H

#include <QObject>

class PetType : public QObject
{
	Q_OBJECT
	Q_ENUMS(Type)
public:
	static enum Type { Humanoid, Dragonkin, Flying, Undead, Critter, Magic, Elemental, Beast, Aquatic, Mechanical };

	static quint8 GetTypeAuraId(Type);
	Q_INVOKABLE static float GetEffectiveness(Type, Type);

private:
	static quint8 auraIds[];
	static float effectiveness[10][10];
};

#endif

