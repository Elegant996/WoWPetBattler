#include "PetStage.h"

PetStage::PetStage(void)
{

}

PetStage::~PetStage(void)
{
	qDeleteAll(petTeam);
	petTeam.clear();
}
