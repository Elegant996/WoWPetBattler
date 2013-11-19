#include "Recorder.h"

//Records the battle info to the appropriate *.json file.
QString Recorder::RecordBattle(PetStage *petStage)
{
	//Get both team's id.
	QString playerTeamId = GetTeamId(petStage, 1);
	QString opponentTeamId = GetTeamId(petStage, 2);

	//Used for output later on.
	QString output = "";

	//Create player's team id directory if it does not exist.
	if (!QDir("BattleRecords/" + playerTeamId).exists())
	{
		//Create the new directory and add default json file for the team.
		QDir().mkdir("BattleRecords/" + playerTeamId);
		QDir::setCurrent("BattleRecords/" + playerTeamId);
		CreateBattleRecord(petStage, 1, QString("%1").arg(QString::number(0), 15, '0'));
		QDir::setCurrent("../../");
	}
	
	//Set folder to that of the player's team id.
	QDir::setCurrent("BattleRecords/" + playerTeamId);

	//Creat the record if it doesn't exist.
	if (!QFile::exists(opponentTeamId + ".json"))
	{
		output = CreateBattleRecord(petStage, 2, opponentTeamId);	//Create a new json for the opponent's team.
		QDir::setCurrent("../../");									//Reset directory path.
		return output;												//Nothing more to do since we've added a new team id.
	}

	//Update the battle record for the teams.
	output = UpdateBattleRecord(petStage, 1, QString("%1").arg(QString::number(0), 15, '0'));
	UpdateBattleRecord(petStage, 2, opponentTeamId);
	
	//Reset directory path.
	QDir::setCurrent("../../");

	//Return the output.
	return output;
}

//Makes the team's id.
QString Recorder::GetTeamId(PetStage *petStage, quint8 teamIndex)
{
	//Create empty team id.
	QString teamId = "";

	//Get pet ids of the team and put them in a sorted list.
	QList<int> petIds;
	for (quint8 i=1; i < petStage->GetTeam(teamIndex)->GetNumPets()+1; i+=1)
		petIds.append(petStage->GetTeam(teamIndex)->GetPet(i)->GetSpeciesId());
	qSort(petIds);

	//Append the pet ids to form the team id.
	for (quint8 i=0; i < 3; i+=1)
		if (i < petIds.size())
			teamId += QString("%1").arg(QString::number(petIds.at(i)), 5, '0');
		else
			teamId += QString("%1").arg(QString::number(0), 5, '0');

	//Return the team's id.
	return teamId;
}

//Creates a battle record.
QString Recorder::CreateBattleRecord(PetStage *petStage, quint8 teamIndex, QString teamId)
{
	//Object that holds all info.
	QJsonObject currentTeam;

	//Insert the team id into the object.
	currentTeam.insert("id", QJsonValue(teamId));

	//Add each pet to the json array.
	QJsonArray pets;
	for (quint8 i=1; i < petStage->GetTeam(teamIndex)->GetNumPets()+1; i+=1)
	{
		QJsonObject currentPet;
		currentPet.insert("id", QJsonValue(petStage->GetTeam(teamIndex)->GetPet(i)->GetSpeciesId()));
		currentPet.insert("name", QJsonValue(petStage->GetTeam(teamIndex)->GetPet(i)->GetName()));
		pets.append(currentPet);
	}

	//Insert the pet array into the object.
	currentTeam.insert("pets", pets);

	//Insert wins and losses into the object.
	currentTeam.insert("wins", QJsonValue((petStage->WonLastBattle()) ? 1 : 0));
	currentTeam.insert("losses", QJsonValue((!petStage->WonLastBattle()) ? 1 : 0));
	
	//Add object to document.
	QJsonDocument battleRecordDocument;
	battleRecordDocument.setObject(currentTeam);
	
	//Write info to file.
	QFile battleRecord(teamId + ".json");						//Load the record.
	battleRecord.open(QIODevice::WriteOnly | QIODevice::Text);	//Open the battle record for reading and writing; create if it doesn't exist.
	battleRecord.write(battleRecordDocument.toJson());			//Write the battle record.
	battleRecord.close();										//Close the record.

	//Return the output.
	return QString("This team has %1 wins and %2 losses.").arg(QString::number((petStage->WonLastBattle()) ? 1 : 0), QString::number((petStage->WonLastBattle()) ? 1 : 0));
}


//Updates a battle record.
QString Recorder::UpdateBattleRecord(PetStage *petStage, quint8 teamIndex, QString teamId)
{
	//Open the battle record for reading.
	QFile battleRecord(teamId + ".json");
	battleRecord.open(QIODevice::ReadWrite | QIODevice::Text);

	//Create a parser and read the document.
	QJsonParseError parser;
	QJsonDocument battleRecordDocument = QJsonDocument::fromJson(battleRecord.readAll(), &parser);

	//Convert document to object.
	QJsonObject battleRecordObject = battleRecordDocument.object();

	//Get the wins and losses.
	int wins = battleRecordObject.value(QString("wins")).toDouble();
	int losses = battleRecordObject.value(QString("losses")).toDouble();

	//Update the wins/losses based on who won the battle.
	if (petStage->WonLastBattle())
	{
		battleRecordObject.remove(QString("wins"));
		battleRecordObject.insert(QString("wins"), QJsonValue(wins+1));
	}
	else
	{
		battleRecordObject.remove(QString("losses"));
		battleRecordObject.insert(QString("losses"), QJsonValue(losses+1));
	}

	battleRecordDocument.setObject(battleRecordObject);			//Add object to document.
	battleRecord.resize(0);										//Empty the record.
	battleRecord.write(battleRecordDocument.toJson());			//Write the update battle record.
	battleRecord.close();										//Close the record.

	//Return the output.
	return QString("This team has %1 wins and %2 losses.").arg(QString::number(wins), QString::number(losses));
}