#include "Pet.h"

//Constructor
Pet::Pet(int speciesID, int breed, int quality, int level)
{
	QFile speciesJson;
	QDir::setCurrent(QDir::currentPath() + "/Species");
	speciesJson.setFileName(QString::number(speciesID) + ".json");
	speciesJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString speciesJsonContents = speciesJson.readAll();
	speciesJson.close();

	QJsonDocument speciesDocument = QJsonDocument::fromJson(speciesJsonContents.toUtf8());
	QJsonObject species = speciesDocument.object();

	this->name = species.value(QString("name")).toString();
	this->speciesID = speciesID;
	this->breed = breed;
	this->quality = quality;
	this->level = level;
	this->type = species.value(QString("petTypeId")).toDouble();
	this->baseHealth = species.value(QString("baseHealth")).toDouble();
	this->basePower = species.value(QString("basePower")).toDouble();
	this->baseSpeed = species.value(QString("baseSpeed")).toDouble();
	this->currentHealth = PetHelper::CalculateHealth(this->baseHealth, PetBreed::GetHealth(this->breed), this->level, this->quality);
	this->currentMaxHealth = this->currentHealth;
	this->currentPower = PetHelper::CalculatePower(this->basePower, PetBreed::GetPower(this->breed), this->level, this->quality);
	this->currentSpeed = PetHelper::CalculateSpeed(this->baseSpeed, PetBreed::GetSpeed(this->breed), this->level, this->quality);
	this->abilityList = species.value(QString("abilities")).toArray();
	this->petAbility.reserve(3);
}

//Deconstructor
Pet::~Pet(void)
{
	qDeleteAll(this->petAbility);
	this->petAbility.clear();
}

//Copy Constructor
Pet::Pet(const Pet& other)
{
	this->name = other.name;
	this->speciesID = other.speciesID;
	this->breed = other.breed;
	this->quality = other.quality;
	this->level = other.level;
	this->type = other.type;
	this->baseHealth = other.baseHealth;
	this->basePower = other.basePower;
	this->baseSpeed = other.baseSpeed;
	this->currentHealth = other.currentHealth;
	this->currentMaxHealth = other.currentMaxHealth;
	this->currentPower = other.currentPower;
	this->currentSpeed = other.currentSpeed;
	this->abilityList = other.abilityList;
	this->petAbility.reserve(3);
	for (int i=0; i < other.petAbility.size(); i++)
		this->petAbility.append(new PetAbility(*other.petAbility.at(i)));
}

//Add an ability to the current pet.
void Pet::AddAbility(bool verification, int tier, int cooldown)
{
	this->petAbility.append(new PetAbility(abilityList[(2*this->petAbility.size())+tier-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Return the desired ability at the specified index.
PetAbility* Pet::GetAbility(int index)
{
	return this->petAbility.at(index-1);
}

//Set the pet's current health.
void Pet::SetHealth(int health)
{
	this->currentHealth = health;
}

//Set the pet's current max health.
void Pet::SetMaxHealth(int maxHealth)
{
	this->currentMaxHealth = maxHealth;
}

//Set the pet's current power.
void Pet::SetPower(int power)
{
	this->currentPower = power;
}

//Set the pet's current speed.
void Pet::SetSpeed(int speed)
{
	this->currentSpeed = speed;
}

//Return pet's species ID.
int Pet::GetSpeciesID()
{
	return this->speciesID;
}

//Return pet's current health.
int Pet::GetHealth()
{
	return this->currentHealth;
}
//Return pet's current max health.
int Pet::GetMaxHealth()
{
	return this->currentMaxHealth;
}

//Return pet's current power.
int Pet::GetPower()
{
	return this->currentPower;
}

//Return pet's current speed.
int Pet::GetSpeed()
{
	return this->currentSpeed;
}
