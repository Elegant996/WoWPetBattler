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
}

Pet::Pet(int speciesId, int breed, int quality, int level)
{
	QFile speciesJson;
	QDir::setCurrent(QDir::currentPath() + "/Species");
	speciesJson.setFileName(QString::number(speciesId) + ".json");
	speciesJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString speciesJsonContents = speciesJson.readAll();
	speciesJson.close();
	QDir::setCurrent(QDir::currentPath() + "/..");

	QJsonDocument speciesDocument = QJsonDocument::fromJson(speciesJsonContents.toUtf8());
	QJsonObject species = speciesDocument.object();

	this->name = species.value(QString("name")).toString();
	this->speciesId = speciesId;
	this->breed = breed;
	this->type = species.value(QString("petTypeId")).toDouble();
	this->quality = quality;
	this->level = level;
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
	this->type = other.type;
	this->quality = other.quality;
	this->level = other.level;
	this->baseHealth = other.baseHealth;
	this->basePower = other.basePower;
	this->baseSpeed = other.baseSpeed;
	this->currentHealth = other.currentHealth;
	this->currentMaxHealth = other.currentMaxHealth;
	this->currentPower = other.currentPower;
	this->currentSpeed = other.currentSpeed;
	this->abilityList = other.abilityList;
	this->petAbility.reserve(3);
	for (int i=0; i < other.petAbility.size(); i+=1)
		this->petAbility.append(new PetAbility(*other.petAbility.at(i)));
	for (int i=0; i < other.petAura.size(); i+=1)
		this->petAura.append(new PetAura(*other.petAura.at(i)));
	for (int i=0; i < other.petStatus.size(); i+=1)
		this->petStatus.append(new QString(*other.petStatus.at(i)));
}

//Return the number of status effects on the pet.
int Pet::GetNumStatus()
{
	return petStatus.size();
}

//Return the pet's status vector.
QString* Pet::GetStatus(int index)
{
	return this->petStatus.at(index-1);
}

//Return whether or not the pet has a specific status.
bool Pet::HasStatus(QString petStatus)
{
	for (int i=0; i < this->petStatus.size(); i+=1)
		if (this->petStatus.at(i) == petStatus)
			return true;
	return false;
}

//Add an ability to the current pet.
void Pet::AddAbility(bool verification, int tier, int cooldown)
{
	this->petAbility.append(new PetAbility(abilityList[(this->petAbility.size()+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Replace the ability of the current pet at specified index.
void Pet::ReplaceAbility(int index, bool verification, int tier, int cooldown)
{
	this->petAbility.replace(index-1, new PetAbility(abilityList[(index+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Return the number of abilities known by the pet.
int Pet::GetNumAbilities()
{
	return petAbility.size();
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

//Return number of auras on the pet
int Pet::GetNumAuras()
{
	return petAura.size();
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

//Return pet's type.
int Pet::GetType()
{
	return this->type;
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
