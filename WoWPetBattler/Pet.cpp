#include "Pet.h"

//Constructors
Pet::Pet(int speciesID)
{
	this->speciesID = speciesID;
	this->type = 0;
	this->health = 0;
	this->power = 0;
	this->speed = 0;
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
	this->type = other.type;
	this->health = other.health;
	this->power = other.power;
	this->speed = other.speed;
	for (int i=0; i < other.petAbility.size(); i++)
		this->petAbility.append(new PetAbility(*other.petAbility.at(i)));
}

//Add an ability to the current pet.
void Pet::AddAbility(int abilityID, int cooldown, bool verification)
{
	petAbility.append(new PetAbility(abilityID, cooldown, verification));
}

//Return the desired ability at the specified index.
PetAbility* Pet::GetPetAbility(int index)
{
	return petAbility.at(index-1);
}

//Return pet's species ID.
int Pet::GetSpeciesID()
{
	return speciesID;
}

//Return pet's health.
int Pet::GetHealth()
{
	return health;
}

//Return pet's power.
int Pet::GetPower()
{
	return power;
}

//Return pet's speed.
int Pet::GetSpeed()
{
	return speed;
}
