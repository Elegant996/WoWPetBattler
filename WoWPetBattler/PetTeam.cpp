#include "PetTeam.h"

//Constructors
PetTeam::PetTeam(int numPets)
{
	this->activePet = 0;
	this->pet.reserve(numPets);
	for (int i=0; i < numPets; i+=1)
		pet.append(new Pet());
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
	for (int i=0; i < other.pet.size(); i+=1)
		this->pet.append(new Pet(*other.pet.at(i)));
}

//"Zero-out" the pet team.
void PetTeam::Remove()
{
	this->activePet = 0;
	for (int i=0; i < pet.size(); i+=1)
		pet.at(i)->Remove();
}

//Add a pet to the current team.
void PetTeam::AddPet(int speciesID, int breed, int quality, int level)
{
	for (int i=0; i < pet.size(); i+=1)
		if (pet.at(i)->GetSpeciesId() == 0)
		{
			this->pet.at(i)->Initialize(speciesID, breed, quality, level);
			return;
		}
}

//Set the index of the active pet.
void PetTeam::SetActivePet(int index)
{
	this->activePet = index;
}

//Return the active pet.
Pet* PetTeam::GetActivePet()
{
	return this->pet.at(activePet);
}

//Return the index of the active pet.
int PetTeam::GetActivePetIndex()
{
	return this->activePet;
}

//Get the number of pets on the team.
int PetTeam::GetNumPets()
{
	int petCount = 0;
	for (int i=0; i < pet.size(); i+=1)
		if (pet.at(i)->GetSpeciesId() != 0)
			petCount += 1;
		else
			break;

	return petCount;
}

//Get the pet at the current index.
Pet* PetTeam::GetPet(int index)
{
	return this->pet.at((index == 0) ? 0 : index-1);
}