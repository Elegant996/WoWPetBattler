#ifndef PETHELPER_H
#define PETHELPER_H

#include <QObject>

#include "PetStage.h"

class PetHelper : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE void CheckDamage(PetStage*, quint8, quint8, quint16);
	Q_INVOKABLE void CheckRacialsProc(PetStage*, quint8);
	Q_INVOKABLE void CheckRacials(Pet*);
	Q_INVOKABLE void CheckAuraPower(PetStage*, PetAura*, quint8, quint8);
};

#endif

