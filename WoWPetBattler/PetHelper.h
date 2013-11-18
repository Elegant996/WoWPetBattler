#ifndef PETHELPER_H
#define PETHELPER_H

#include <QObject>
#include <QtCore/qmath.h>

#include "PetStage.h"

class PetHelper : public QObject
{
	Q_OBJECT
public:
	Q_INVOKABLE static void CheckDamage(PetStage*, quint8, quint8, quint16, bool, bool);
	Q_INVOKABLE static void CheckHealing(PetStage*, quint8, quint8, quint16, bool);
	static void CheckRacialsProc(PetStage*, quint8);
	static void CheckRacials(Pet*);
	Q_INVOKABLE static void CheckAuraPower(PetStage*, PetAura*, quint8, quint16);
	Q_INVOKABLE static void CheckCleansingRain(PetStage*, quint8, quint8, quint16, qint8, bool, quint16);
	Q_INVOKABLE static float CheckWeatherBonus(PetStage*, PetType::Type);

private:
	static quint16 Round(float);
};

#endif

