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
	this->activePet = other.activePet;
	for (int i=0; i < other.pet.size(); i++)
		this->pet.append(new Pet(*other.pet.at(i)));
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