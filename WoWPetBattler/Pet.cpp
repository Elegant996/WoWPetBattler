#include "Pet.h"

//Constructors
Pet::Pet()
{
	this->name = "";
	this->speciesId = 0;
	this->breed = 0;
	this->quality = 0;
	this->level = 0;
	this->type = 0;
	this->baseHealth = 0;
	this->basePower = 0;
	this->baseSpeed = 0;
	this->currentHealth = 0;
	this->currentMaxHealth = 0;
	this->currentPower = 0;
	this->currentSpeed = 0;
	this->abilityList;
}

Pet::Pet(int speciesId, int breed, int quality, int level)
{
	QFile speciesJson;
	QDir::setCurrent(QDir::currentPath() + "/Species");
	speciesJson.setFileName(QString::number(speciesId) + ".json");
	speciesJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString speciesJsonContents = speciesJson.readAll();
	speciesJson.close();

	QJsonDocument speciesDocument = QJsonDocument::fromJson(speciesJsonContents.toUtf8());
	QJsonObject species = speciesDocument.object();

	this->name = species.value(QString("name")).toString();
	this->speciesId = speciesId;
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
}

//Deconstructor
Pet::~Pet(void)
{
	qDeleteAll(this->petAbility);
	this->petAbility.clear();
	RemoveAuras();
}

//Copy Constructor
Pet::Pet(const Pet& other)
{
	this->name = other.name;
	this->speciesId = other.speciesId;
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
	for (int i=0; i < other.petAura.size(); i++)
		this->petAura.append(new PetAura(*other.petAura.at(i)));
}

//Add an ability to the current pet.
void Pet::AddAbility(bool verification, int tier, int cooldown)
{
	this->petAbility.append(new PetAbility(abilityList[(2*this->petAbility.size())+tier-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Replace the ability of the current pet at specified index.
void Pet::ReplaceAbility(int index, bool verification, int tier, int cooldown)
{
	this->petAbility.replace(index-1, new PetAbility(abilityList[(2*this->petAbility.size())+tier-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Return the desired ability at the specified index.
PetAbility* Pet::GetAbility(int index)
{
	return this->petAbility.at(index-1);
}

//Add an aura to the current pet.
void Pet::AddAura(int auraId, int duration)
{
	this->petAura.append(new PetAura(auraId, duration));
}

//Removes all pet auras on the current pet.
void Pet::RemoveAuras()
{
	qDeleteAll(this->petAura);
	this->petAura.clear();
}

//Return the desired aura at the specified index.
PetAura* Pet::GetAura(int index)
{
	return this->petAura.at(index-1);
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

//Return pet's species Id.
int Pet::GetSpeciesId()
{
	return this->speciesId;
}

//Return pet's level.
int Pet::GetLevel()
{
	return this->level;
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
