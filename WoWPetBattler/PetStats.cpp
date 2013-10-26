#include "PetStats.h"

//Calculate the pet's health.
int PetStats::CalculateHealth(float baseHealth, float breedHealth, float level, float quality)
{
	return Round((baseHealth + breedHealth) * 5 * level * (1 + ((quality - 1) / 10)) + 100);
}

//Calculate the pet's power.
int PetStats::CalculatePower(float basePower, float breedPower, float level, float quality)
{
	return Round((basePower + breedPower) * level * (1 + ((quality - 1) / 10)));
}

//Calculate the pet's speed.
int PetStats::CalculateSpeed(float baseSpeed, float breedSpeed, float level, float quality)
{
	return Round((baseSpeed + breedSpeed) * level * (1 + ((quality - 1) / 10)));
}

//Rounds up or down depending on the decimal.
int PetStats::Round(float value)
{
	return qFloor(value + 0.5);
}
