#include "PetTeam.h"

//Constructors
PetTeam::PetTeam(void)
{

}

//Destructor
PetTeam::~PetTeam(void)
{
	qDeleteAll(pet);
	pet.clear();
}

//Add a pet to the current team.
void PetTeam::AddPet(int speciesID)
{
	pet.append(new Pet(speciesID));
}