#include "Recorder.h"

//Records the battle info to the appropriate record.
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
		//Create the new directory and add default record for the team.
		QDir().mkdir("BattleRecords/" + playerTeamId);
		QDir::setCurrent("BattleRecords/" + playerTeamId);
		CreateBattleRecord(petStage, 1, QString("%1").arg(QString::number(0), 15, '0'));
		QDir::setCurrent("../../");
	}
	
	//Set folder to that of the player's team id.
	QDir::setCurrent("BattleRecords/" + playerTeamId);

	//Create the record if it doesn't exist.
	if (!QFile::exists(opponentTeamId + ".json"))
		CreateBattleRecord(petStage, 2, opponentTeamId);			//Create a new json for the opponent's team.
	else
		UpdateBattleRecord(petStage, 2, opponentTeamId);			//Update the current json for the opponent's team.

	//Update the battle record for our team.
	output = UpdateBattleRecord(petStage, 1, QString("%1").arg(QString::number(0), 15, '0'));
	
	//Reset directory path.
	QDir::setCurrent("../../");

	//Return the output.
	return output;
}

//Records the pet info to the appropriate record.
void Recorder::RecordPets(PetStage *petStage)
{
	//Record each pet.
	for (quint8 i=1; i < petStage->GetTeam(2)->GetNumPets()+1; i+=1)
	{
		//Create the record if it doesn't exist.
		if (!QFile::exists("PetRecords/" + QString::number(petStage->GetTeam(2)->GetPet(i)->GetSpeciesId()) + ".json"))
			CreatePetRecord(petStage, i);
		
		//Update the record.
		UpdatePetRecord(petStage, i);
	}
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
void Recorder::CreateBattleRecord(PetStage *petStage, quint8 teamIndex, QString teamId)
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
	currentTeam.insert("wins", QJsonValue((petStage->WonLastBattle() && teamIndex == 2) ? 1 : 0));
	currentTeam.insert("losses", QJsonValue((!petStage->WonLastBattle() && teamIndex == 2) ? 1 : 0));
	
	//Add object to document.
	QJsonDocument battleRecordDocument;
	battleRecordDocument.setObject(currentTeam);
	
	//Write info to file.
	QFile battleRecord(teamId + ".json");						//Load the record.
	battleRecord.open(QIODevice::WriteOnly | QIODevice::Text);	//Open the battle record for reading and writing; create if it doesn't exist.
	battleRecord.write(battleRecordDocument.toJson());			//Write the battle record.
	battleRecord.close();										//Close the record.
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
		wins += 1;
		battleRecordObject.remove(QString("wins"));
		battleRecordObject.insert(QString("wins"), QJsonValue(wins));
	}
	else
	{
		losses += 1;
		battleRecordObject.remove(QString("losses"));
		battleRecordObject.insert(QString("losses"), QJsonValue(losses));
	}

	battleRecordDocument.setObject(battleRecordObject);			//Add object to document.
	battleRecord.resize(0);										//Empty the record.
	battleRecord.write(battleRecordDocument.toJson());			//Write the update battle record.
	battleRecord.close();										//Close the record.

	//Return the output.
	return QString("This team has %1 wins and %2 losses.").arg(QString::number(wins), QString::number(losses));
}

//Creates a pet record.
void Recorder::CreatePetRecord(PetStage *petStage, quint8 petIndex)
{
	//Get the pet species.
	quint16 petSpecies = petStage->GetTeam(2)->GetPet(petIndex)->GetSpeciesId();

	//Object that holds all info.
	QJsonObject currentPet;

	//Insert the team id into the object.
	currentPet.insert("id", QJsonValue(petSpecies));

	QJsonArray abilities;
	//Process each ability of the pet.
	for (quint8 i=1; i < petStage->GetTeam(2)->GetPet(petIndex)->GetNumAbilities()+1; i+=1)
	{
		QJsonObject currentAbility;
		QJsonArray currentTiers;

		//For each tier of an ability set it's count to 0.
		for (quint8 j=1; j < 3; j+=1)
		{
			QJsonObject currentTier;
			currentTier.insert("tier", QJsonValue(j));
			currentTier.insert("count", QJsonValue(0));
			currentTiers.append(currentTier);
		}

		//Add the current tier to the ability.
		currentAbility.insert("ability" + QString::number(i), currentTiers);
		abilities.append(currentAbility);
	}

	//Insert the pet array into the object.
	currentPet.insert("abilities", abilities);

	//Add object to document.
	QJsonDocument petRecordDocument;
	petRecordDocument.setObject(currentPet);

	//Write info to file.
	QFile petRecord("PetRecords/" + QString::number(petSpecies) + ".json");		//Load the record.
	petRecord.open(QIODevice::WriteOnly | QIODevice::Text);						//Open the battle record for reading and writing; create if it doesn't exist.
	petRecord.write(petRecordDocument.toJson());								//Write the battle record.
	petRecord.close();															//Close the record.
}

//Updates a pet record.
void Recorder::UpdatePetRecord(PetStage *petStage, quint8 petIndex)
{
	//Get the pet species.
	quint16 petSpecies = petStage->GetTeam(2)->GetPet(petIndex)->GetSpeciesId();

	//Open the pet record to read and write.
	QFile petRecord("PetRecords/" + QString::number(petSpecies) + ".json");
	petRecord.open(QIODevice::ReadWrite | QIODevice::Text);

	//Create a parser and read the document.
	QJsonParseError parser;
	QJsonDocument petRecordDocument = QJsonDocument::fromJson(petRecord.readAll(), &parser);

	//Convert document to object.
	QJsonObject petRecordObject, newPetRecordObject;
	petRecordObject = petRecordDocument.object();	

	//Go through each ability.
	QJsonArray abilities, newAbilities;
	abilities = petRecordObject.value(QString("abilities")).toArray();
	for (quint8 i=0; i < abilities.size(); i+=1)
	{
		QJsonObject currentAbility, newCurrentAbility;
		currentAbility = abilities.at(i).toObject();

		QJsonArray currentTiers, newCurrentTiers;
		currentTiers = currentAbility.value(QString("ability" + QString::number(i+1))).toArray();

		//Go through each tier the ability can have.
		for (quint8 j=0; j < currentTiers.size(); j+=1)
		{
			QJsonObject currentTier, newCurrentTier;
			currentTier = currentTiers.at(j).toObject();

			//Get the frequency of the ability and increase it if it was used this battle.
			int count = currentTier.value(QString("count")).toDouble();
			count += (!petStage->GetTeam(2)->GetPet(petIndex)->GetAbility(i+1)->IsVerified()
				&& petStage->GetTeam(2)->GetPet(petIndex)->GetAbility(i+1)->GetTier() == j+1) ? 1 : 0;

			//Insert it into the new variable.
			newCurrentTier.insert(QString("tier"), QJsonValue(j+1));
			newCurrentTier.insert(QString("count"), QJsonValue(count));
			newCurrentTiers.append(newCurrentTier);
		}

		//Replace current ability with updated version.
		newCurrentAbility.insert((QString("ability" + QString::number(i+1))), newCurrentTiers);
		newAbilities.append(newCurrentAbility);
	}

	//Replace abilities with updated version.
	newPetRecordObject.insert(QString("abilities"), newAbilities);

	petRecordDocument.setObject(newPetRecordObject);		//Add object to document.
	petRecord.resize(0);									//Empty the record.
	petRecord.write(petRecordDocument.toJson());			//Write the update battle record.
	petRecord.close();										//Close the record.
}