#include "PetStage.h"

//Constructors
PetStage::PetStage(void)
	: QObject(NULL), parentStage(NULL)
{
	this->queueState = 0;
	this->inPetBattle = false;
	this->teamIsAlive = false;
	this->queueEnabled = false;
	this->canAccept = false;
	this->playerIsGhost = true;
	this->playerIsDead = true;
	this->playerAffectingCombat = true;
	this->initialized = false;
	this->selectPet = false;
	this->selectAbility = false;
	this->wonLastBattle = false;
	this->isPvPBattle = false;
	for (int i=0; i < 3; i+=1)
		this->petTeams.append(new PetTeam());
}

//Destructor
PetStage::~PetStage(void)
{
	for (int i=0; i < petTeams.size(); i+=1)
		delete (petTeams.takeAt(0));
	petTeams.clear();
}

//Copy Constructor
PetStage::PetStage(const PetStage& other)
	: QObject(NULL), parentStage(&other)
{
	this->queueState = other.queueState;
	this->inPetBattle = other.inPetBattle;
	this->teamIsAlive = other.teamIsAlive;
	this->queueEnabled = other.queueEnabled;
	this->canAccept = other.canAccept;
	this->playerIsGhost = other.playerIsGhost;
	this->playerIsDead = other.playerIsDead;
	this->playerAffectingCombat = other.playerAffectingCombat;
	this->initialized = other.initialized;
	this->selectPet = other.selectPet;
	this->selectAbility = other.selectAbility;
	this->wonLastBattle = other.wonLastBattle;
	this->isPvPBattle = other.isPvPBattle;
	this->petTeams.reserve(3);
	for (int i=0; i < other.petTeams.size(); i+=1)
		this->petTeams.append(new PetTeam(*other.petTeams.at(i)));
}

//Recreates the basic setup for the stage.
void PetStage::Reinitialize()
{
	//Delete all teams
	qDeleteAll(this->petTeams);
	this->petTeams.clear();

	this->queueState = 0;
	this->inPetBattle = false;
	this->teamIsAlive = false;
	this->queueEnabled = false;
	this->canAccept = false;
	this->playerIsGhost = true;
	this->playerIsDead = true;
	this->playerAffectingCombat = true;
	this->initialized = false;
	this->selectPet = false;
	this->selectAbility = false;
	this->wonLastBattle = false;
	this->isPvPBattle = false;
	this->petTeams.append(new PetTeam());
	this->petTeams.append(new PetTeam());
	this->petTeams.append(new PetTeam());
}

//Update CDs and auras.
void PetStage::RoundUpdate()
{
	foreach(PetTeam *petTeam, this->petTeams)
		petTeam->RoundUpdate();
}

//Return whether or not the match is over.
bool PetStage::IsMatchOver()
{
	if (petTeams.at(1)->IsTeamDead() || petTeams.at(2)->IsTeamDead())
		return true;
	return false;
}

//Return the desired pet team; 0 for field, 1 for player, 2 for opponent;
PetTeam* PetStage::GetTeam(quint8 index)
{
	return this->petTeams.at(index);
}

//For QML purposes.
/*QQmlListProperty<PetTeam> PetStage::GetTeams()
{
	return QQmlListProperty<PetTeam>(this, petTeams);
}*/

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

//Update whether or not it is a PvP Battle.
void PetStage::IsPvPBattle(bool isPvPBattle)
{
	this->isPvPBattle = isPvPBattle;
}

//Return the current queue state.
qint8 PetStage::QueueState()
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

//Return whether or not it is a PvP battle.
bool PetStage::IsPvPBattle()
{
	return this->isPvPBattle;
}
