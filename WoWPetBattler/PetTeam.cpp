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
	qDeleteAll(this->pet);
	this->pet.clear();
}

//Copy Constructor
PetTeam::PetTeam(const PetTeam& other)
{
	this->activePet = other.activePet;
	this->pet.reserve(3);
	for (int i=0; i < other.pet.size(); i++)
		this->pet.append(new Pet(*other.pet.at(i)));
}

//Adds a dummy pet, used for weather.
void PetTeam::AddPet()
{
	this->pet.append(new Pet());
}

//Add a pet to the current team.
void PetTeam::AddPet(int speciesID, int breed, int quality, int level)
{
	this->pet.append(new Pet(speciesID, breed, quality, level));
}

//Set the index of the active pet.
void PetTeam::SetActivePet(int index)
{
	this->activePet = index;
}

//Return the index of the active pet.
int PetTeam::GetActivePet()
{
	return this->activePet;
}

//Get the pet at the current index.
Pet* PetTeam::GetPet(int index)
{
	return this->pet.at((index == 0) ? 0 : index-1);
}

//Get the number of pets on the team.
int PetTeam::GetNumPets()
{
	return this->pet.size();
}