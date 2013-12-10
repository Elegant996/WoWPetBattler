#ifndef RECORDER_H
#define RECORDER_H

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
	static void RecordPets(PetStage*);

private:
	static QString GetTeamId(PetStage*, quint8);

	static void CreateBattleRecord(PetStage*, quint8, QString);
	static QString UpdateBattleRecord(PetStage*, quint8, QString);

	static void CreatePetRecord(PetStage*, quint8);
	static void UpdatePetRecord(PetStage*, quint8);
};

#endif

