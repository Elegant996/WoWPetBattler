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
	qDeleteAll(petTeam);
	petTeam.clear();
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
	return petTeam.at(index-1);
}