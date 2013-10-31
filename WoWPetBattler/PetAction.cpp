#include "PetAction.h"

//Constructor
PetAction::PetAction()
	: QObject(NULL)
{
	this->action = Action::None;
	this->roundsRemaining = 0;
}

//Destructor
PetAction::~PetAction(void)
{
}

//Copy Constructor
PetAction::PetAction(const PetAction& other)
	: QObject(NULL)
{
	this->action = other.action;
	this->roundsRemaining = other.roundsRemaining;
}

//Update rounds remaining on the current action.
void PetAction::RoundUpdate()
{
	if (this->roundsRemaining > 0)
	{
		this->roundsRemaining -= 1;
		this->action = (roundsRemaining == 0) ? Action::None : this->action;
	}
}

//Set the action.
void PetAction::SetAction(PetAction::Action action)
{
	this->action = action;
}

//Set the rounds remaining.
void PetAction::SetRoundsRemaining(qint8 roundsRemaining)
{
	this->roundsRemaining = roundsRemaining;
}

//Return the action.
PetAction::Action PetAction::GetAction()
{
	return this->action;
}

//Return the rounds remaining.
qint8 PetAction::GetRoundsRemaining()
{
	return this->roundsRemaining;
}
