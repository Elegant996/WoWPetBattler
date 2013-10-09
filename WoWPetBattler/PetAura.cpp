#include "PetAura.h"

//Constructor
PetAura::PetAura(int auraId, int duration)
{
	this->auraId = auraId;
	this->duration = (duration == 0) ? -1 : duration;
}

//Destructor
PetAura::~PetAura(void)
{
}

//Copy Constructor
PetAura::PetAura(const PetAura& other)
{
	this->auraId = other.auraId;
	this->duration = other.duration;
}
