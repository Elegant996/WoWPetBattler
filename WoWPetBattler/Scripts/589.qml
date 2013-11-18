// Arcane Storm - Ability
import QtQuick 2.0

import PetAction 1.0
import PetHelper 1.0
import PetStatus 1.0
import PetType 1.0

Item
{
    //Used to allow access to static functions in PetType class.
    PetType { id: petType }

    //Used to allow access to static functions in PetHelper class.
    PetHelper { id: petHelper }

    //Returns the accuracy of the pet given the move.
    function getAccuracyRating(teamIndex)
    {
        return 1;
    }

    //Returns the critical strike rating of the pet given the move.
    function getCriticalRating(teamIndex)
    {
        return 0;
    }

    //Returns the chance on hit rating if the move has any.
    function getChanceOnHitRating(teamIndex)
    {
        return 0;
    }

    //Apply the aura's effect at the start of the turn.
    function applyAuraStart(teamIndex, petIndex, auraIndex, duration)
    {

    }

    //Applies the aura effect to the active pet.
    function applyAura(teamIndex)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function applyAuraEnd(teamIndex, petIndex, auraIndex, duration)
    {

    }

    //Grants the pet any special statuses the ability has.
    function preUseAbility(teamIndex)
    {

    }

    //Applies the ability and returns the number of hits made.
    function useAbility(teamIndex, curRound, isFirst, isAvoiding,
                        isHitting, isCritting, isProcing)
    {
        var numHits = 0;
        var scaleFactor = 0.40;
        var baseDamage = 8;
        var attackType = PetType.Magic;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(teamIndex).ActivePet.Power * scaleFactor);

        //Check whether it is avoid/crit/hit/proc.
        if (!isAvoiding && isHitting)
            for (var i=1; i < petStage.GetTeam((teamIndex%2)+1).NumPets+1; i++)
            {
                var damage = Math.round((normalDamage - petStage.GetTeam((teamIndex%2)+1).GetPet(i).DamageOffset)
                                * petType.GetEffectiveness(attackType, petStage.GetTeam((teamIndex%2)+1).ActivePet.Type)
                                * petStage.GetTeam((teamIndex%2)+1).GetPet(i).DefenseModifier
                                * (petStage.GetTeam(teamIndex).ActivePet.DamageModifier
                                   + petHelper.CheckWeatherBonus(petStage, attackType)));

                numHits += 1;
                if (isCritting && i == randomPetIndex)
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, i, 2*damage, true, false);
                else
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, i, damage, true, false);
            }
        else if (isAvoiding)
            for (var i=2; i < petStage.GetTeam((teamIndex%2)+1).NumPets+1; i++)
            {
                var damage = Math.round((normalDamage - petStage.GetTeam((teamIndex%2)+1).GetPet(i).DamageOffset)
                                * petType.GetEffectiveness(attackType, petStage.GetTeam((teamIndex%2)+1).ActivePet.Type)
                                * petStage.GetTeam((teamIndex%2)+1).GetPet(i).DefenseModifier
                                * (petStage.GetTeam(teamIndex).ActivePet.DamageModifier
                                   + petHelper.CheckWeatherBonus(petStage, attackType)));

                numHits += 1;
                if (isCritting && i == randomPetIndex)
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, i, 2*damage, true, false);
                else
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, i, damage, true, false);
            }

        //Remove any other weather effects.
        if (petStage.GetTeam(0).GetPet(0).NumAuras > 0)
        {
            //Scorched Earth
            if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 171)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Burning);
            //Blizzard
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 205)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Chilled);
            //Sunny Day
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 403)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).MaxHealth = petStage.GetTeam(i).GetPet(j).NormalMaxHealth;
                        petStage.GetTeam(i).GetPet(j).HealingModifier -= 0.25;
                    }
            //Darkness
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 257)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Blinded);
                        petStage.GetTeam(i).GetPet(j).AccuracyOffset += 0.10;
                        petStage.GetTeam(i).GetPet(j).HealingModifier += 0.50;
                    }
            //Sandstorm
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 454)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).AccuracyOffset += 0.10;
                        petStage.GetTeam(i).GetPet(j).DamageOffset -= 5 + petStage.GetTeam(0).GetAura(1).Power * 0.25;
                    }
            //Moonlight
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 596)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).HealingModifier -= 0.25;
            //Cleansing Rain
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 229)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                        if (petStage.GetTeam(i).GetPet(j).Type == PetType.Aquatic)
                            petStage.GetTeam(i).GetPet(j).DamageModifier -= 0.25;

            petStage.GetTeam(0).GetPet(0).RemoveAura(1);
        }

        petStage.GetTeam(0).GetPet(0).AddAura(590, 9, true, teamIndex, petStage.GetTeam(teamIndex).ActivePetIndex, petStage.GetTeam(teamIndex).ActivePet.Power);

        return numHits;
    }
}
