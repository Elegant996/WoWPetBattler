#include "PetHelper.h"

//Checks the damage dealt.
void PetHelper::CheckDamage(PetStage *petStage, quint8 teamIndex, quint8 petIndex, quint16 damage, bool mainAttack, bool useLightning)
{
	Pet *curPet = petStage->GetTeam(teamIndex)->GetPet(petIndex);
	quint16 totalDamage = damage;

	//Special exception is the use of Lightning Storm weather effect.
	if (useLightning && petStage->GetTeam(0)->GetPet(0)->GetNumAuras() > 0
			&& petStage->GetTeam(0)->GetPet(0)->GetAura(1)->GetAuraId() == 203)
		totalDamage += 2 + petStage->GetTeam(0)->GetPet(0)->GetAura(1)->GetPower() * 0.10;

	//Use Magic racial if applicable.
	if (curPet->GetType() == PetType::Magic && totalDamage > (int)(curPet->GetMaxHealth() * 0.35))
		//Check if health is greater than 35%.
		if (curPet->GetHealthPercentage() > 0.35)
			curPet->SetHealth(curPet->GetHealth() - curPet->GetMaxHealth() * 0.35);
		else
		{	//Set health to 0 and check racial procs for attacking team.
			curPet->SetHealth(0);
			CheckRacials(curPet);
		}
	else
	{
		//Check if the pet can sustain the hit.
		if (curPet->GetHealth() - totalDamage > 0)
			curPet->SetHealth(curPet->GetHealth() - totalDamage);
		else
		{	//Pet can't sustain the hit, set health to 0 and check racials.
			curPet->SetHealth(0);
			CheckRacials(curPet);
		}
	}

	//Check if this is the main attack.
	if (mainAttack)
	{	//Check to see if racials have proc'd and set attack to true.
		CheckRacialsProc(petStage, (teamIndex%2)+1);
		petStage->GetTeam((teamIndex%2)+1)->GetActivePet()->AttackedThisRound(true);
	}
}

//Check the healing done.
void PetHelper::CheckHealing(PetStage *petStage, quint8 teamIndex, quint8 petIndex, quint16 healing, bool mainAttack)
{
	Pet *curPet = petStage->GetTeam(teamIndex)->GetPet(petIndex);

	if (curPet->GetHealth() + healing > curPet->GetMaxHealth())
		curPet->SetHealth(curPet->GetMaxHealth());
	else
		curPet->SetHealth(curPet->GetHealth() + healing);
}

//Checks whether the Dragonkin racial should proc.
void PetHelper::CheckRacialsProc(PetStage *petStage, quint8 teamIndex)
{
	Pet *curPet = petStage->GetTeam(teamIndex)->GetActivePet();

	//Check if active pet is Dragonkin type and has brought the other team's pet below 50%.
	if (curPet->GetType() == PetType::Dragonkin
                && petStage->GetTeam((teamIndex%2)+1)->GetActivePet()->GetHealthPercentage() < 0.50
                && !curPet->RacialUsed())
	{
		curPet->RacialUsed(true);			//Racial now used.
		curPet->AddAura(245, 1, true);		//Will replace persisting racial.
    }
}

//Called by everything else to handle racial effects.
void PetHelper::CheckRacials(Pet *curPet)
{
	//Check if active pet is Flying type is now below 50% and racial is active.
	if (curPet->GetType() == PetType::Flying)
	{
		if (curPet->GetHealthPercentage() > 0.50 && !curPet->RacialUsed())
		{
			curPet->SetSpeed(curPet->GetSpeed() * 1.5);
			curPet->RacialUsed(true);
		}
		else if (curPet->GetHealthPercentage() <= 0.50 && curPet->RacialUsed())
		{
			curPet->SetSpeed(curPet->GetSpeed() / 1.5);
			curPet->RacialUsed(false);
		}
	}
	//Check if active pet is Beast type and is now above/below 25% health and racial is active/inactive.
	else if (curPet->GetType() == PetType::Beast)
	{
		//Disable the racial.
		if (curPet->GetHealthPercentage() >= 0.50 && curPet->RacialUsed())
		{
			curPet->SetDamageModifier(curPet->GetDamageModifier() / 1.25);
			curPet->RacialUsed(false);
		}
		else if (curPet->GetHealthPercentage() < 0.50	&& !curPet->RacialUsed())
		{
			curPet->SetDamageModifier(curPet->GetDamageModifier() * 1.25);
			curPet->RacialUsed(true);
		}
	}
	//Check if active pet is Undead type and has just died.
	else if (curPet->IsDead())
	{
		if (curPet->GetType() == PetType::Undead && !curPet->RacialUsed())
		{
			curPet->SetHealth(1);						//Ensures pet is alive.
			curPet->RacialUsed(true);					//Racial now used.
			curPet->AddStatus(Pet::Unkillable);			//Pet can't die.
			curPet->AddAura(242, 1, true);				//Will replace persisting racial.
		}
		else if (curPet->GetType() == PetType::Mechanical)
		{
			curPet->SetHealth(curPet->GetMaxHealth() * 0.20);	//Set pet's new health value.
			curPet->RacialUsed(true);							//Racial now used.
			curPet->AddAura(244, 1, true);						//Will replace persisting racial.
		}
	}
}

//Finds the power of the first pet who most likely cast the aura.
void PetHelper::CheckAuraPower(PetStage* petStage, PetAura *curAura, quint8 teamIndex, quint8 abilityId)
{
	//Find the first pet with has the ability and use it's power.
	if (teamIndex == 3)
	{	//Check both teams.
		for (quint8 i=1; i < teamIndex; i+=1)
			for (quint8 j=1; j < petStage->GetTeam(i)->GetNumPets()+1; j+=1)
				for (quint8 k=1; k < petStage->GetTeam(i)->GetPet(j)->GetNumAbilities()+1; k+=1)
					 if (petStage->GetTeam(i)->GetPet(j)->GetAbility(k)->GetAbilityId() == abilityId)
						 curAura->SetPower(petStage->GetTeam(i)->GetPet(j)->GetPower());
	}
	else
	{	//We know which team to check already.
		for (quint8 i=1; i < petStage->GetTeam(teamIndex)->GetNumPets()+1; i+=1)
			for (quint8 j=1; j < petStage->GetTeam(teamIndex)->GetPet(i)->GetNumAbilities()+1; j+=1)
					if (petStage->GetTeam(teamIndex)->GetPet(i)->GetAbility(j)->GetAbilityId() == abilityId)
						curAura->SetPower(petStage->GetTeam(teamIndex)->GetPet(i)->GetPower());
	}
}

//Checks if a weather effect can decrease the duration of a harmful effect.
void PetHelper::CheckCleansingRain(PetStage* petStage, quint8 teamIndex, quint8 petIndex, quint16 auraId, qint8 duration, bool isFresh, quint16 power)
{
	if (petStage->GetTeam(0)->GetPet(0)->GetNumAuras() > 0 && petStage->GetTeam(0)->GetPet(0)->GetAura(1)->GetAuraId() == 229)
		petStage->GetTeam(teamIndex)->GetPet(petIndex)->AddAura(auraId, duration-1, isFresh, power);
	else
		petStage->GetTeam(teamIndex)->GetPet(petIndex)->AddAura(auraId, duration, isFresh, power);
}

//Checks to see if there is a bonus to be gained from weather and applies it.
float PetHelper::CheckWeatherBonus(PetStage *petStage, PetType::Type petType)
{
	if (petType == PetType::Magic && petStage->GetTeam(0)->GetPet(0)->GetNumAuras() > 0
			&& petStage->GetTeam(0)->GetPet(0)->GetAura(1)->GetAuraId() == 596)
		return 0.10;
	else if (petType == PetType::Mechanical && petStage->GetTeam(0)->GetPet(0)->GetNumAuras() > 0
			&& petStage->GetTeam(0)->GetPet(0)->GetAura(1)->GetAuraId() == 203)
		return 0.25;
	else
		return 0;
}
