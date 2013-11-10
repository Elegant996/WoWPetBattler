#include "PetHelper.h"

//Checks the damage to see if it will trigger a Magic pet's racial.
void PetHelper::CheckRacialsDamage(PetStage *petStage, quint8 curTeam, quint16 damage)
{
	Pet *curActivePet = petStage->GetTeam(curTeam)->GetActivePet();

	if (curActivePet->GetType() == PetType::Magic && damage > curActivePet->GetMaxHealth() * 0.35)
		curActivePet->SetHealth(curActivePet->GetHealth() - curActivePet->GetMaxHealth() * 0.35);
	else
		curActivePet->SetHealth(curActivePet->GetHealth() - damage);
}

//Checks whether the Dragonkin racial should proc.
void PetHelper::CheckRacialsProc(PetStage *petStage, quint8 curTeam)
{
	Pet *curActivePet = petStage->GetTeam(curTeam)->GetActivePet();

	//Check if active pet is Dragonkin type and has brought the other team's pet below 50%.
	if (curActivePet->GetType() == PetType::Dragonkin
                && petStage->GetTeam((curTeam%2)+1)->GetActivePet()->GetHealthPercentage() < 0.50
                && !curActivePet->RacialUsed())
	{
		curActivePet->RacialUsed(true);				//Racial now used.
		curActivePet->AddAura(245, 1, true);		//Will replace persisting racial.
    }
}

//Called by everything else to handle racial effects.
void PetHelper::CheckRacials(PetStage *petStage, quint8 curTeam)
{
	Pet *curActivePet = petStage->GetTeam(curTeam)->GetActivePet();

	//Check if active pet is Flying type is now below 50% and racial is active.
	if (curActivePet->GetType() == PetType::Flying)
	{
		if (curActivePet->GetHealthPercentage() > 0.50 && !curActivePet->RacialUsed())
		{
			curActivePet->SetSpeed(curActivePet->GetSpeed() * 1.5);
			curActivePet->RacialUsed(true);
		}
		else if (curActivePet->GetHealthPercentage() <= 0.50 && curActivePet->RacialUsed())
		{
			curActivePet->SetSpeed(curActivePet->GetSpeed() / 1.5);
			curActivePet->RacialUsed(false);
		}
	}
	//Check if active pet is Beast type and is now above/below 25% health and racial is active/inactive.
	else if (curActivePet->GetType() == PetType::Beast)
	{
		//Disable the racial.
		if (curActivePet->GetHealthPercentage() >= 0.50 && curActivePet->RacialUsed())
		{
			curActivePet->SetDamageModifier(curActivePet->GetDamageModifier() / 1.25);
			curActivePet->RacialUsed(false);
		}
		else if (curActivePet->GetHealthPercentage() < 0.50	&& !curActivePet->RacialUsed())
		{
			curActivePet->SetDamageModifier(curActivePet->GetDamageModifier() * 1.25);
			curActivePet->RacialUsed(true);
		}
	}
	//Check if active pet is Undead type and has just died.
	else if (curActivePet->IsDead())
	{
		if (curActivePet->GetType() == PetType::Undead && !curActivePet->RacialUsed())
		{
			curActivePet->SetHealth(1);							//Ensures pet is alive.
			curActivePet->RacialUsed(true);						//Racial now used.
			curActivePet->AddStatus(Pet::Unkillable);			//Pet can't die.
			curActivePet->AddAura(242, 1, true);				//Will replace persisting racial.
		}
		else if (curActivePet->GetType() == PetType::Mechanical)
		{
			curActivePet->SetHealth(curActivePet->GetMaxHealth() * 0.20);	//Set pet's new health value.
			curActivePet->RacialUsed(true);									//Racial now used.
			curActivePet->AddAura(244, 1, true);							//Will replace persisting racial.
		}
	}
}

//Finds the power of the first pet who most likely cast the aura.
void PetHelper::CheckAuraPower(PetStage* petStage, PetAura *curAura, quint8 curTeam, quint8 abilityId)
{
	if (curTeam == 3)
		for (quint8 i=1; i < curTeam; i+=1)
			for (quint8 j=1; j < petStage->GetTeam(i)->GetNumPets()+1; j+=1)
				for (quint8 k=1; k < petStage->GetTeam(i)->GetPet(j)->GetNumAbilities()+1; k+=1)
					 if (petStage->GetTeam(i)->GetPet(j)->GetAbility(k)->GetAbilityId() == abilityId)
						 curAura->SetPower(petStage->GetTeam(i)->GetPet(j)->GetPower());
}
