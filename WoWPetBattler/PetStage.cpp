#include "PetStage.h"

//Constructors
PetStage::PetStage(void)
{
	this->petTeam.reserve(2);
	this->petTeam.append(new PetTeam());
	this->petTeam.append(new PetTeam());
}

//Destructor
PetStage::~PetStage(void)
{
	qDeleteAll(this->petTeam);
	this->petTeam.clear();
}

//Copy Constructor
PetStage::PetStage(const PetStage& other)
{
	for (int i=0; i < other.petTeam.size(); i++)
		this->petTeam.append(new PetTeam(*other.petTeam.at(i)));
}

//Return the desired pet team; 1 for player, 2 for opponent;
PetTeam* PetStage::GetPetTeam(int index)
{
	return this->petTeam.at(index-1);
}

//Update the queue state.
void PetStage::QueueState(int queueState)
{
	this->queueState = queueState;
}

//Update whether or not we're in a pet battle.
void PetStage::InPetBattle(bool inPetBattle)
{
	this->inPetBattle = inPetBattle;
}

//Update whether or not the team is alive before queueing.
void PetStage::TeamIsAlive(bool teamIsAlive)
{
	this->teamIsAlive = teamIsAlive;
}

//Update whether or not the queue system is enabled.
void PetStage::QueueEnabled(bool queueEnabled)
{
	this->queueEnabled = queueEnabled;
}

//Update whether or not we can accept a pet battle.
void PetStage::CanAccept(bool canAccept)
{
	this->canAccept = canAccept;
}

//Update whether or not the player is a ghost.
void PetStage::PlayerIsGhost(bool playerIsGhost)
{
	this->playerIsGhost = playerIsGhost;
}

//Update whether or not the player is dead.
void PetStage::PlayerIsDead(bool playerIsDead)
{
	this->playerIsDead = playerIsDead;
}

//Update whether or not the player is affected by combat.
void PetStage::PlayerAffectingCombat(bool playerAffectingCombat)
{
	this->playerAffectingCombat = playerAffectingCombat;
}

//Update whether or not we have selected the first pet and can comfirm the field.
void PetStage::Initialized(bool initialized)
{
	this->initialized = initialized;
}

//Update whether or not we are currently at the select pet screen.
void PetStage::SelectPet(bool selectPet)
{
	this->selectPet = selectPet;
}

//Update whether or not we are currently at the select pet ability screen.
void PetStage::SelectAbility(bool selectAbility)
{
	this->selectAbility = selectAbility;
}

//Update whether or not the last game ended in victory.
void PetStage::WonLastBattle(bool wonLastBattle)
{
	this->wonLastBattle = wonLastBattle;
}

//Return the current queue state.
int PetStage::QueueState()
{
	//0 - not in queue; 1 - suspended; 2 - queued; 3 - proposal
	return this->queueState;
}

//Return whether or not we are in battle.
bool PetStage::InPetBattle()
{
	return this->inPetBattle;
}

//Return whether or not the team is alive.
bool PetStage::TeamIsAlive()
{
	return this->teamIsAlive;
}

//Return whether or not the queue system is enabled.
bool PetStage::QueueEnabled()
{
	return this->queueEnabled;
}

//Return whether or not we can accept the queue.
bool PetStage::CanAccept()
{
	return this->canAccept;
}

//Return whether or not the player is a ghost.
bool PetStage::PlayerIsGhost()
{
	return this->playerIsGhost;
}

//Return whether or not the player is dead.
bool PetStage::PlayerIsDead()
{
	return this->playerIsDead;
}

//Return whether or not the player is in combat.
bool PetStage::PlayerAffectingCombat()
{
	return this->playerAffectingCombat;
}

//Return whether or not we are past the initial pet selection.
bool PetStage::Initialized()
{
	return this->initialized;
}

//Return whether or not we are at the select pet screen.
bool PetStage::SelectPet()
{
	return this->selectPet;
}

//Return whether or not we are at the select ability screen.
bool PetStage::SelectAbility()
{
	return this->selectAbility;
}

//Return whether or not the last game ended in victory.
bool PetStage::WonLastBattle()
{
	return this->wonLastBattle;
}