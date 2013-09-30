#include "PetAbility.h"

//Constructors
PetAbility::PetAbility(int abilityID, int cooldown, bool isVerified)
{
	this->abilityID = abilityID;
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
	this->abilityID = other.abilityID;
	this->cooldown = other.cooldown;
	this->isVerified = other.isVerified;
}

//Update the cooldown of the ability.
void PetAbility::SetCooldown(int CD)
{
	cooldown = CD;
}

//Confirm whether we know this ability is known.
void PetAbility::IsVerified(bool verification)
{
	isVerified = verification;
}

//Return ability ID.
int PetAbility::GetAbilityID()
{
	return abilityID;
}

//Return cooldown status.
int PetAbility::GetCooldown()
{
	return cooldown;
}

//Return whether or not the ability is verified.
bool PetAbility::IsVerified()
{
	return isVerified;
}
