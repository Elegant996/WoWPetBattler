#include "PetType.h"

//Define aura ids for each pet type.
quint8 PetType::auraIds[] = { 238, 245, 239, 242, 236, 243, 241, 237, 240, 244 };

//Effectiveness chart used by scripts.
float PetType::effectiveness[10][10] = {{1.00, 1.50, 1.00, 1.00, 1.00, 1.00, 1.00, 0.66, 1.00, 1.00},
										{1.00, 1.00, 1.00, 0.66, 1.00, 1.50, 1.00, 1.00, 1.00, 1.00},
										{1.00, 0.66, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.50, 1.00},
										{1.50, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0.66, 1.00},
										{0.66, 1.00, 1.00, 1.50, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00},
										{1.00, 1.00, 1.50, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0.66},
										{1.00, 1.00, 1.00, 1.00, 0.66, 1.00, 1.00, 1.00, 1.00, 1.50},
										{1.00, 1.00, 0.66, 1.00, 1.50, 1.00, 1.00, 1.00, 1.00, 1.00},
										{1.00, 1.00, 1.00, 1.00, 1.00, 0.66, 1.50, 1.00, 1.00, 1.00},
										{1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0.66, 1.50, 1.00, 1.00}};

//Return the aura id of the pet type.
quint8 PetType::GetTypeAuraId(PetType::Type petType)
{
	return auraIds[petType];
}

float PetType::GetEffectiveness(PetType::Type attacker, PetType::Type defender)
{
	return effectiveness[attacker][defender];
}
