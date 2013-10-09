#include "PetAbility.h"

//Constructor
PetAbility::PetAbility(int abilityId, int cooldown, bool isVerified)
{
	this->abilityId = abilityId;
	this->cooldown = cooldown;
	this->isVerified = isVerified;
}

//Deconstructor
PetAbility::~PetAbility(void)
{

}

//Copy Constructor
PetAbility::PetAbility(const PetAbility& other)
{
	this->abilityId = other.abilityId;
	this->cooldown = other.cooldown;
	this->isVerified = other.isVerified;
}

//Update the cooldown of the ability.
void PetAbility::SetCooldown(int CD)
{
	this->cooldown = CD;
}

//Confirm whether we know this ability is known.
void PetAbility::IsVerified(bool verification)
{
	this->isVerified = verification;
}

//Return ability Id.
int PetAbility::GetAbilityId()
{
	return this->abilityId;
}

//Return cooldown status.
int PetAbility::GetCooldown()
{
	return this->cooldown;
}

//Return whether or not the ability is verified.
bool PetAbility::IsVerified()
{
	return this->isVerified;
}
