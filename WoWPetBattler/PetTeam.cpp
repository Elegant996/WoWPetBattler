#include "PetTeam.h"

//Constructors
PetTeam::PetTeam(void)
	: QObject(NULL)
{
	this->activePet = 0;
	this->pets.reserve(3);
}

//Destructor
PetTeam::~PetTeam(void)
{
	qDeleteAll(this->pets);
	this->pets.clear();
}

//Copy Constructor
PetTeam::PetTeam(const PetTeam& other)
	: QObject(NULL)
{
	this->activePet = other.activePet;
	this->pets.reserve(3);
	//foreach (Pet *myPet, other.pet)
		//this->pet.append(new Pet(*myPet));

	for (int i=0; i < other.pets.size(); i+=1)
		this->pets.append(new Pet(*other.pets.at(i)));
}

//Update CDs and auras.
void PetTeam::RoundUpdate()
{
	foreach (Pet *pet, this->pets)
		pet->RoundUpdate();
}

//Adds a dummy pet, used for weather.
void PetTeam::AddPet()
{
	this->pets.append(new Pet());
}

//Add a pet to the current team.
void PetTeam::AddPet(int speciesID, int breed, int quality, int level)
{
	this->pets.append(new Pet(speciesID, breed, quality, level));
}

//Set the index of the active pet.
void PetTeam::SetActivePet(int index)
{
	this->activePet = index;
}

//Return the active pet.
Pet* PetTeam::GetActivePet()
{
	return this->pets.at(activePet-1);
}

//Return the index of the active pet.
int PetTeam::GetActivePetIndex()
{
	return this->activePet;
}

//Get the number of pets on the team.
int PetTeam::GetNumPets()
{
	return this->pets.size();
}

//Get the pet at the current index.
Pet* PetTeam::GetPet(int index)
{
	return this->pets.at((index == 0) ? 0 : index-1);
}

//For QML purposes.
QQmlListProperty<Pet> PetTeam::GetPets()
{
	return QQmlListProperty<Pet>(this, pets);
}