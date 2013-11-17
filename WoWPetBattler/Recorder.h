#ifndef RECORDER_H
#define RECORDER_H

#include <QDebug>

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "PetStage.h"

class Recorder
{
public:
	static QString RecordBattle(PetStage*);

private:
	static QString GetTeamId(PetStage*, quint8);
	static QString CreateBattleRecord(PetStage*, quint8, QString);
	static QString UpdateBattleRecord(PetStage*, quint8, QString);
};

#endif

