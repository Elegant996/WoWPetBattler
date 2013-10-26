#include "PetBreed.h"

//Define all breed arrays.
float PetBreed::health[] = { 0.5, 0, 0, 2, 0.9, 0, 0.9, 0.4, 0.4, 0.9, 0.5, 0, 0, 2, 0.9, 0, 0.9, 0.4, 0.4, 0.9 };
float PetBreed::power[] = { 0.5, 2, 0, 0, 0.9, 0.9, 0, 0.9, 0.4, 0.4, 0.5, 2, 0, 0, 0.9, 0.9, 0, 0.9, 0.4, 0.4 };
float PetBreed::speed[] = { 0.5, 0, 2, 0, 0, 0.9, 0.9, 0.4, 0.9, 0.4, 0.5, 0, 2, 0, 0, 0.9, 0.9, 0.4, 0.9, 0.4 };

//Get the health increase from this breed.
float PetBreed::GetHealth(int index)
{
	return health[index - 3];
}

//Get the power increase from this breed.
float PetBreed::GetPower(int index)
{
	return power[index - 3];
}

//Get the speed increase from this breed.
float PetBreed::GetSpeed(int index)
{
	return speed[index - 3];
}