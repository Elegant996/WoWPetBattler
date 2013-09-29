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
	//petTeam = other.petTeam;

	for (int i=0; i < other.petTeam.size(); i++)
		petTeam.append(new PetTeam(*other.petTeam[i]));
}

//Operator Overload for '='
PetStage& PetStage::operator=(const PetStage &rhs)
{
	//petTeam = rhs.petTeam;

	for (int i=0; i < rhs.petTeam.size(); i++)
		petTeam.append(new PetTeam(*rhs.petTeam[i]));

	return *this;
}

//Return the desired pet team; 1 for player, 2 for opponent;
PetTeam* PetStage::GetPetTeam(int index)
{
	return petTeam.at(index-1);
}