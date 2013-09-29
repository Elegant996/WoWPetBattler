#include "Pet.h"

//Constructors
Pet::Pet(int speciesID)
{
	this->speciesID = speciesID;
	this->petAbility.reserve(3);
}

//Deconstructor
Pet::~Pet(void)
{
	qDeleteAll(petAbility);
	petAbility.clear();
}

//Copy Constructor
Pet::Pet(const Pet& other)
{
	speciesID = other.speciesID;
	health = other.health;
	power = other.power;
	speed = other.speed;
	petAbility = other.petAbility;
}

//Operator Overload for '='
Pet& Pet::operator=(const Pet &rhs)
{
	speciesID = rhs.speciesID;
	health = rhs.health;
	power = rhs.power;
	speed = rhs.speed;
	petAbility = rhs.petAbility;

	return *this;
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
