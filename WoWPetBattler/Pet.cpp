#include "Pet.h"

//Constructors
Pet::Pet(int speciesID, int breed, int quality, int level)
{
	this->speciesID = speciesID;
	this->breed = breed;
	this->quality = quality;
	this->level = level;
	this->type = 0;
	this->baseHealth = 0;
	this->basePower = 0;
	this->baseSpeed = 0;
	this->currentHealth = 0;
	this->currentMaxHealth = 0;
	this->currentPower = 0;
	this->currentSpeed = 0;
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
	for (int i=0; i < other.petAbility.size(); i++)
		this->petAbility.append(new PetAbility(*other.petAbility.at(i)));
}

//Add an ability to the current pet.
void Pet::AddAbility(bool verification, int tier, int cooldown)
{
	//this->petAbility.append(new PetAbility(abilityID, cooldown, verification));
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
