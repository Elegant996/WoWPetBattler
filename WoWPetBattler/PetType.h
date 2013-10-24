#ifndef PETTYPE_H
#define PETTYPE_H

#include <QObject>

class PetType : public QObject
{
	Q_OBJECT
	Q_ENUMS(Type)
public:
	static enum Type { Humanoid, Dragonkin, Flying, Undead, Critter, Magic, Elemental, Beast, Aquatic, Mechanical };
};

#endif

