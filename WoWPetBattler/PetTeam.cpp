#include "PetTeam.h"

//Constructors
PetTeam::PetTeam(void)
{
	this->activePet = 0;
	this->pet.reserve(3);
}

//Destructor
PetTeam::~PetTeam(void)
{
	qDeleteAll(pet);
	pet.clear();
}

//Copy Constructor
PetTeam::PetTeam(const PetTeam& other)
{
	pet = other.pet;
}

//Operator Overload for '='
PetTeam& PetTeam::operator=(const PetTeam &rhs)
{
	pet = rhs.pet;

	return *this;
}

//Add a pet to the current team.
void PetTeam::AddPet(int speciesID)
{
	pet.append(new Pet(speciesID));
}

//Set the index of the active pet.
void PetTeam::SetActivePet(int index)
{
	activePet = index;
}

//Return the index of the active pet.
int PetTeam::GetActivePet()
{
	return activePet;
}

//Get the pet at the current index.
Pet* PetTeam::GetPet(int index)
{
	return pet.at(index-1);
}