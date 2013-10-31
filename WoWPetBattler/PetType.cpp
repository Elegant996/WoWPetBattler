#include "PetType.h"

//Define aura ids for each pet type.
quint8 PetType::auraIds[] = { 238, 245, 239, 242, 236, 243, 241, 237, 240, 244 };

//Return the aura id of the pet type.
quint8 PetType::GetTypeAuraId(PetType::Type petType)
{
	return auraIds[petType];
}
