#include "Pet.h"

//Constructors
Pet::Pet()
	: QObject(NULL)
{
	this->name = "Dummy Pet";
	this->speciesId = 0;
	this->breed = 0;
	this->quality = 0;
	this->level = 0;
	this->type = (PetType::Type)0;
	this->baseHealth = 0;
	this->basePower = 0;
	this->baseSpeed = 0;
	this->normalMaxHealth = 0;
	this->normalPower = 0;
	this->normalSpeed = 0;
	this->lastKnownHealth = 0;
	this->currentHealth = 0;
	this->currentMaxHealth = 0;
	this->currentPower = 0;
	this->currentSpeed = 0;
	this->accuracyOffset = 0.00;
	this->avoidanceRating = 0.00;
	this->criticalStrikeRating = 0.05;
	this->damageModifier = 1.00;
	this->healingModifier = 1.00;
	this->defenseModifier = 1.00;
	this->damageOffset = 0;
	this->racialUsed = false;
	this->attackedThisRound = false;
	this->currentAction = new PetAction();
}

Pet::Pet(quint16 speciesId, quint8 breed, quint8 quality, quint8 level)
{
	QFile speciesJson("Species/" + QString::number(speciesId) + ".json");
	speciesJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString speciesJsonContents = speciesJson.readAll();
	speciesJson.close();

	QJsonDocument speciesDocument = QJsonDocument::fromJson(speciesJsonContents.toUtf8());
	QJsonObject species = speciesDocument.object();

	this->name = species.value(QString("name")).toString();
	this->speciesId = speciesId;
	this->breed = breed;
	this->type = (PetType::Type)(int)species.value(QString("petTypeId")).toDouble();
	this->quality = quality;
	this->level = level;
	this->baseHealth = species.value(QString("baseHealth")).toDouble();
	this->basePower = species.value(QString("basePower")).toDouble();
	this->baseSpeed = species.value(QString("baseSpeed")).toDouble();
	this->normalMaxHealth = PetStats::CalculateHealth(this->baseHealth, PetBreed::GetHealth(this->breed), this->level, this->quality);
	this->normalPower = PetStats::CalculatePower(this->basePower, PetBreed::GetPower(this->breed), this->level, this->quality);
	this->normalSpeed = PetStats::CalculateSpeed(this->baseSpeed, PetBreed::GetSpeed(this->breed), this->level, this->quality);
	this->lastKnownHealth = 0;
	this->currentHealth = this->normalMaxHealth;
	this->currentMaxHealth = this->currentHealth;
	this->currentPower = this->normalPower;
	this->currentSpeed = this->normalSpeed;
	this->accuracyOffset = 0.00;
	this->avoidanceRating = 0.00;
	this->criticalStrikeRating = 0.05;
	this->damageModifier = 1.00;
	this->healingModifier = 1.00;
	this->defenseModifier = 1.00;
	this->damageOffset = 0;
	this->racialUsed = false;
	this->attackedThisRound = false;
	this->currentAction = new PetAction();
	this->abilityList = species.value(QString("abilities")).toArray();
	this->petAuras.append(new PetAura(PetType::GetTypeAuraId(type), 0, false));
}

//Deconstructor
Pet::~Pet(void)
{
	delete currentAction;

	this->petStatuses.clear();

	while (!this->petAbilities.isEmpty())
		delete (this->petAbilities.takeFirst());
	this->petAbilities.clear();

	while (!this->petAuras.isEmpty())
		delete (this->petAuras.takeFirst());
	this->petAuras.clear();
}

//Copy Constructor
Pet::Pet(const Pet& other)
	: QObject(NULL)
{
	this->name = other.name;
	this->speciesId = other.speciesId;
	this->breed = other.breed;
	this->type = other.type;
	this->quality = other.quality;
	this->level = other.level;
	this->baseHealth = other.baseHealth;
	this->basePower = other.basePower;
	this->baseSpeed = other.baseSpeed;
	this->normalMaxHealth = other.normalMaxHealth;
	this->normalPower = other.normalPower;
	this->normalSpeed = other.normalSpeed;
	this->lastKnownHealth = other.lastKnownHealth;
	this->currentHealth = other.currentHealth;
	this->currentMaxHealth = other.currentMaxHealth;
	this->currentPower = other.currentPower;
	this->currentSpeed = other.currentSpeed;
	this->accuracyOffset = other.accuracyOffset;
	this->avoidanceRating = other.avoidanceRating;
	this->criticalStrikeRating = other.criticalStrikeRating;
	this->damageModifier = other.damageModifier;
	this->healingModifier = other.healingModifier;
	this->defenseModifier = other.defenseModifier;
	this->damageOffset = other.damageOffset;
	this->racialUsed = other.racialUsed;
	this->attackedThisRound = other.attackedThisRound;
	this->currentAction = new PetAction(*other.currentAction);
	this->abilityList = other.abilityList;
	for (int i=0; i < other.petAbilities.size(); i+=1)
		this->petAbilities.append(new PetAbility(*other.petAbilities.at(i)));
	for (int i=0; i < other.petAuras.size(); i+=1)
		this->petAuras.append(new PetAura(*other.petAuras.at(i)));
	for (int i=0; i < other.petStatuses.size(); i+=1)
		this->petStatuses.append(PetStatus(other.petStatuses.at(i)));
}

//Update current action, CDs and auras.
void Pet::RoundUpdate()
{
	//Update the current action.
	this->currentAction->RoundUpdate();

	//Remove all statuses.
	this->petStatuses.clear();

	//Update each ability.
	foreach (PetAbility *petAbility, this->petAbilities)
		petAbility->RoundUpdate();

	//Update each aura and remove expired ones.
	for (int i=0; i < petAuras.size(); i+=1)
	{
		petAuras.at(i)->RoundUpdate();
		if (petAuras.at(i)->GetDuration() == 0)
		{
			delete (petAuras.takeAt(i));
			i -= 1; //To correct the loop.
		}
	}

	this->currentSpeed = this->normalSpeed;
	this->accuracyOffset = 0.00;
	this->avoidanceRating = 0.00;
	this->criticalStrikeRating = 0.05;
	this->damageModifier = 1.00;
	this->healingModifier = 1.00;
	this->defenseModifier = 1.00;
	this->damageOffset = 0;
	this->attackedThisRound = false;
}

//Adds the status to the list.
void Pet::AddStatus(Pet::PetStatus status)
{
	//if (!petStatuses.contains(status))
		petStatuses.append(status);
}

//Remove the status from the list.
void Pet::RemoveStatus(Pet::PetStatus status)
{
	petStatuses.removeOne(status);
}

//Return whether or not the pet has a specific status.
bool Pet::HasStatus(Pet::PetStatus petStatus)
{
	return petStatuses.contains(petStatus);
}

//Return the number of status effects on the pet.
int Pet::GetNumStatuses()
{
	return petStatuses.size();
}

//Return the pet's status vector.
Pet::PetStatus Pet::GetStatus(quint8 index)
{
	return (Pet::PetStatus)this->petStatuses.at(index-1);
}

//For QML purposes.
/*QList<int> Pet::GetStatuses()
{
	return petStatuses;
}*/

//Add an ability to the current pet.
void Pet::AddAbility(bool verified, bool isPvPBattle, quint8 tier, qint8 cooldown)
{
	//If it's not a PvP battle or it is a PvP battle and the record is is not available.
	if (!isPvPBattle || !QFile::exists("PetRecords/" + QString::number(this->speciesId) + ".json"))
		this->petAbilities.append(new PetAbility(abilityList[(this->petAbilities.size()+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), tier, cooldown, verified));
	//It is a PvP battle and the record is available.
	else
	{
		//No point in checking anything else if it's verified.
		if (verified)
			this->petAbilities.append(new PetAbility(abilityList[(this->petAbilities.size()+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), tier, cooldown, verified));
		else
		{
			QFile petRecord("PetRecords/" + QString::number(speciesId) + ".json");
			petRecord.open(QIODevice::ReadOnly | QIODevice::Text);

			//Create a parser and read the document.
			QJsonParseError parser;
			QJsonDocument petRecordDocument = QJsonDocument::fromJson(petRecord.readAll(), &parser);

			//Reduces a bit of clutter to have an object.
			QJsonObject petRecordObject = petRecordDocument.object();

			//Get each tier's frequency.
			quint32 tier1Count = petRecordObject.value(QString("abilities")).toArray().at(petAbilities.size()).toObject().value("ability" + QString::number(petAbilities.size()+1)).toArray().at(0).toObject().value(QString("count")).toDouble();
			quint32 tier2Count = petRecordObject.value(QString("abilities")).toArray().at(petAbilities.size()).toObject().value("ability" + QString::number(petAbilities.size()+1)).toArray().at(1).toObject().value(QString("count")).toDouble();

			//Use the tier with the greatest frequency.
			if (tier1Count > tier2Count)
				this->petAbilities.append(new PetAbility(abilityList[(this->petAbilities.size()+1)-1].toObject().value(QString("id")).toDouble(), tier, cooldown, verified));
			else
				this->petAbilities.append(new PetAbility(abilityList[(this->petAbilities.size()+1)+2].toObject().value(QString("id")).toDouble(), tier, cooldown, verified));

			petRecord.close();	//Close the record.
		}
	}
}

//Replace the ability of the current pet at specified index.
void Pet::ReplaceAbility(quint8 index, bool verified, quint8 tier, qint8 cooldown)
{
	this->petAbilities.replace(index-1, new PetAbility(abilityList[(index+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), tier, cooldown, verified));
}

//Return the number of abilities known by the pet.
int Pet::GetNumAbilities()
{
	return petAbilities.size();
}

//Return the desired ability at the specified index.
PetAbility* Pet::GetAbility(quint8 index)
{
	return this->petAbilities.at(index-1);
}

//For QML purposes.
/*QQmlListProperty<PetAbility> Pet::GetAbilities()
{
	return QQmlListProperty<PetAbility>(this, petAbilities);
}*/

//Add an aura to the current pet.
void Pet::AddAura(quint16 auraId, qint8 duration, bool isFresh)
{
	//Check to see if petAuras is empty, if not check to see if it exists already and overwrite.
	if (!petAuras.isEmpty())
		for (int i=0; i < this->petAuras.size(); i+=1)
			if (auraId == this->petAuras.at(i)->GetAuraId())
			{
				this->petAuras.at(i)->UpdateAura(duration, isFresh);
				return;
			}

	//If it doesn't exist, add it.
	this->petAuras.append(new PetAura(auraId, duration, isFresh));
}

//Add an aura to the current pet.
void Pet::AddAura(quint16 auraId, qint8 duration, bool isFresh, quint8 teamIndex, quint8 petIndex, quint16 power)
{
	//Check to see if petAuras is empty, if not check to see if it exists already and overwrite.
	if (!petAuras.isEmpty())
		for (int i=0; i < this->petAuras.size(); i+=1)
			if (auraId == this->petAuras.at(i)->GetAuraId())
			{
				this->petAuras.at(i)->UpdateAura(duration, isFresh, teamIndex, petIndex, power);
				return;
			}

	//If it doesn't exist, add it.
	this->petAuras.append(new PetAura(auraId, duration, isFresh, teamIndex, petIndex, power));
}

//Remove the aura at the specified index.
void Pet::RemoveAura(quint8 index)
{
	delete (petAuras.takeAt(index-1));
}

//Remove the specified auraId should it exist in the list.
void Pet::RemoveAuraId(quint16 auraId)
{
	for (quint8 i=0; i < petAuras.size(); i+=1)
		if (petAuras.at(i)->GetAuraId() == auraId)
		{
			delete (petAuras.takeAt(i));
			return;
		}
}

//Removes all pet auras except the racial passive on the pet.
void Pet::RemoveAuras()
{
	//Ignore the first aura for real pets.
	quint8 auraIndex = (speciesId==0)?0:1;
	while (petAuras.size() != auraIndex)
		delete (petAuras.takeAt(auraIndex));
}

//Returns whether or not the pet has the aura id specified.
bool Pet::HasAura(quint16 auraId)
{
	for (quint8 i=0; i < petAuras.size(); i+=1)
		if (this->petAuras.at(i)->GetAuraId() == auraId)
			return true;
	return false;
}

//Return number of auras on the pet.
quint8 Pet::GetNumAuras()
{
	return petAuras.size();
}

//Return the desired aura at the specified index.
PetAura* Pet::GetAura(quint8 index)
{
	return this->petAuras.at(index-1);
}

//Return the last aura applied.
PetAura* Pet::GetLastAura()
{
	return this->petAuras.last();
}

//For QML purposes.
/*QQmlListProperty<PetAura> Pet::GetAuras()
{
	return QQmlListProperty<PetAura>(this, petAuras);
}*/

//Return whether or not the pet is dead.
bool Pet::IsDead()
{
	return (currentHealth == 0) ? true : false;
}

//Set the pet's last know health.
void Pet::SetLastKnownHealth(quint16 lastKnownHealth)
{
	this->lastKnownHealth = lastKnownHealth;
}

//Set the pet's current health.
void Pet::SetHealth(quint16 health)
{
	this->currentHealth = health;
}

//Set the pet's current max health.
void Pet::SetMaxHealth(quint16 maxHealth)
{
	this->currentMaxHealth = maxHealth;
}

//Set the pet's current power.
void Pet::SetPower(quint16 power)
{
	this->currentPower = power;
}

//Set the pet's current speed.
void Pet::SetSpeed(quint16 speed)
{
	this->currentSpeed = speed;
}

//Set the pet's accuracy offset.
void Pet::SetAccuracyOffset(float accuracyOffset)
{
	this->accuracyOffset = accuracyOffset;
}

//Set the pet's avoidance modifier.
void Pet::SetAvoidanceRating(float avoidanceRating)
{
	this->avoidanceRating = avoidanceRating;
}

//Set the pet's critical strike modifier.
void Pet::SetCriticalStrikeRating(float criticalStrikeRating)
{
	this->criticalStrikeRating = criticalStrikeRating;
}

//Set the pet's damage modifier.
void Pet::SetDamageModifier(float damageModifier)
{
	this->damageModifier = damageModifier;
}

//Set the pet's healing modifier.
void Pet::SetHealingModifier(float healingModifier)
{
	this->healingModifier = healingModifier;
}

//Set the pet's defense modifier.
void Pet::SetDefenseModifier(float defenseModifier)
{
	this->defenseModifier = defenseModifier;
}

//Set the pet's damage offset.
void Pet::SetDamageOffset(int damageOffset)
{
	this->damageOffset = damageOffset;
}

//Set whether or not the racial has been used.
void Pet::RacialUsed(bool racialUsed)
{
	this->racialUsed = racialUsed;
}

//Set whether or not the pet attacked this round.
void Pet::AttackedThisRound(bool attackedThisRound)
{
	this->attackedThisRound = attackedThisRound;
}

//Return pet's name.
QString Pet::GetName()
{
	return this->name;
}

//Return pet's species Id.
quint16 Pet::GetSpeciesId()
{
	return this->speciesId;
}

//Return pet's type.
PetType::Type Pet::GetType()
{
	return this->type;
}

//Return pet's level.
quint8 Pet::GetLevel()
{
	return this->level;
}

//Return pet's normal max health.
quint16 Pet::GetNormalMaxHealth()
{
	return this->normalMaxHealth;
}

//Return pet's normal power.
quint16 Pet::GetNormalPower()
{
	return this->normalPower;
}

//Return pet's normal speed.
quint16 Pet::GetNormalSpeed()
{
	return this->normalSpeed;
}

//Return pet's last known health;
quint16 Pet::GetLastKnownHealth()
{
	return this->lastKnownHealth;
}

//Return pet's current health.
quint16 Pet::GetHealth()
{
	return this->currentHealth;
}
//Return pet's current max health.
quint16 Pet::GetMaxHealth()
{
	return this->currentMaxHealth;
}

//Return pet's current heath as a percentage.
float Pet::GetHealthPercentage()
{
	return (float)currentHealth / (float)currentMaxHealth;
}

//Return pet's current power.
quint16 Pet::GetPower()
{
	return this->currentPower;
}

//Return pet's current speed.
quint16 Pet::GetSpeed()
{
	return this->currentSpeed;
}

//Return the pet's accuracy offset.
float Pet::GetAccuracyOffset()
{
	return this->accuracyOffset;
}

//Return the pet's avoidance modifier.
float Pet::GetAvoidanceRating()
{
	return this->avoidanceRating;
}

//Return the pet's critical strike modifier.
float Pet::GetCriticalStrikeRating()
{
	return this->criticalStrikeRating;
}

//Return the pet's damage modifier.
float Pet::GetDamageModifier()
{
	return this->damageModifier;
}

//Return the pet's healing modifier.
float Pet::GetHealingModifier()
{
	return this->healingModifier;
}

//Return the pet's defense modifier.
float Pet::GetDefenseModifier()
{
	return this->defenseModifier;
}

//Return the pet's damage offset.
int Pet::GetDamageOffset()
{
	return this->damageOffset;
}

//Return the pet's current action.
PetAction* Pet::GetCurrentAction()
{
	return this->currentAction;
}

//Return whether or not the pet's racial has been used.
bool Pet::RacialUsed()
{
	return this->racialUsed;
}

//Return whether or not the pet attacked this round.
bool Pet::AttackedThisRound()
{
	return this->attackedThisRound;
}
