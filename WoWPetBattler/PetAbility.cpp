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
	abilityID = other.abilityID;
	cooldown = other.cooldown;
	isVerified = other.isVerified;
}

//Operator Overload for '='
PetAbility& PetAbility::operator=(const PetAbility &rhs)
{
	abilityID = rhs.abilityID;
	cooldown = rhs.cooldown;
	isVerified = rhs.isVerified;

	return *this;
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
