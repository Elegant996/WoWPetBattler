#include "PetAction.h"

//Constructor
PetAction::PetAction(quint16 abilityId, qint8 roundsRemaining)
	: QObject(NULL)
{
	this->abilityId = abilityId;
	this->roundsRemaining = roundsRemaining;
}

//Destructor
PetAction::~PetAction(void)
{
}

//Copy Constructor
PetAction::PetAction(const PetAction& other)
	: QObject(NULL)
{
	this->abilityId = other.abilityId;
	this->roundsRemaining = other.roundsRemaining;
}

//Set the ability id.
void PetAction::SetAbilityId(quint16 abilityId)
{
	this->abilityId = abilityId;
}

//Set the rounds remaining.
void PetAction::SetRoundsRemaining(qint8 roundsRemaining)
{
	this->roundsRemaining = roundsRemaining;
}

//Return the ability id.
quint16 PetAction::GetAbilityId()
{
	return this->abilityId;
}


//Return the rounds remaining.
qint8 PetAction::GetRoundsRemaining()
{
	return this->roundsRemaining;
}
