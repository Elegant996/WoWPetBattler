#include "Pet.h"

//Constructors
Pet::Pet(int speciesID)
{
	this->speciesID = speciesID;
}

//Deconstructor
Pet::~Pet(void)
{
	qDeleteAll(petAbility);
	petAbility.clear();
}

//Add an ability to the current pet.
void Pet::AddAbility(int abilityID, int cooldown, bool verification)
{
	petAbility.append(new PetAbility(abilityID, cooldown, verification));
}

//Update the cooldown of a pet's ability.
void Pet::UpdateCooldown(int abilityID, int cooldown)
{
	QVector<PetAbility*>::iterator i = petAbility.begin();
	while (i != petAbility.end())
	{
		if ((*i)->GetAbilityID() == abilityID)
		{
			(*i)->SetCooldown(cooldown);
			break;
		}

		++i;
	}
}

//Confirm that the pet knows this ability.
void Pet::VerifyAbility(int abilityID, bool verification)
{
	QVector<PetAbility*>::iterator i = petAbility.begin();
	while (i != petAbility.end())
	{
		if ((*i)->GetAbilityID() == abilityID)
		{
			(*i)->IsVerified(verification);
			break;
		}

		++i;
	}
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
