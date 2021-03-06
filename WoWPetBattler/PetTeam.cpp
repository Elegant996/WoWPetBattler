#include "PetTeam.h"

//Constructors
PetTeam::PetTeam(void)
	: QObject(NULL)
{
	this->activePet = 0;
	this->pets.append(new Pet());
}

//Destructor
PetTeam::~PetTeam(void)
{
	while (!this->pets.isEmpty())
		delete (this->pets.takeFirst());
	this->pets.clear();
}

//Copy Constructor
PetTeam::PetTeam(const PetTeam& other)
	: QObject(NULL)
{
	this->activePet = other.activePet;

	for (int i=0; i < other.pets.size(); i+=1)
		this->pets.append(new Pet(*other.pets.at(i)));
}

//Update CDs and auras.
void PetTeam::RoundUpdate()
{
	foreach (Pet *pet, this->pets)
		pet->RoundUpdate();
}

//Determine whether or not the team is dead.
bool PetTeam::IsTeamDead()
{
	//Check to see if anyone's health is above 0.
	for (int i=1; i < pets.size(); i+=1)
		if (!pets.at(i)->IsDead())
			return false;
	//Team must be dead.
	return true;
}

//Returns the number of dead pets.
quint8 PetTeam::GetDeathToll()
{
	quint8 deathToll = 0;
	for (quint8 i=1; i < this->pets.size(); i+=1)
		if (pets.at(i)->IsDead())
			deathToll += 1;

	return deathToll;
}

//Adds a dummy pet, used for weather.
void PetTeam::AddPet()
{
	this->pets.append(new Pet());
}

//Add a pet to the current team.
void PetTeam::AddPet(quint16 speciesID, quint8 breed, quint8 quality, quint8 level)
{
	this->pets.append(new Pet(speciesID, breed, quality, level));
}

//Set the index of the active pet.
void PetTeam::SetActivePet(quint8 index)
{
	this->activePet = index;
}

//Return the active pet.
Pet* PetTeam::GetActivePet()
{
	return this->pets.at(activePet);
}

//Return the index of the active pet.
quint8 PetTeam::GetActivePetIndex()
{
	return this->activePet;
}

//Get the number of pets on the team.
quint8 PetTeam::GetNumPets()
{
	return this->pets.size()-1;
}

//Get the pet at the current index.
Pet* PetTeam::GetPet(quint8 index)
{
	return this->pets.at(index);
}

//For QML purposes.
/*QQmlListProperty<Pet> PetTeam::GetPets()
{
	return QQmlListProperty<Pet>(this, pets);
}*/