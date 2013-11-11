// Cleansing Rain - Ability
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
    function preuseAbility(teamIndex)
    {

    }

    //Applies the ability and returns the number of hits made.
    function useAbility(teamIndex, priority, isAvoiding,
                        isHitting, isCritting, isProcing)
    {
        var numHits = 0;
        var scaleFactor = 0.40;
        var baseHealing = 8;
        var attackType = PetType.Aquatic;
        var normalHealing = Math.round(baseHealing + petStage.GetTeam(teamIndex).ActivePet.Power * scaleFactor);

        //Used below.
        var randomPetIndex = Math.floor((Math.random()*petStage.GetTeam(teamIndex).NumPets)+1);

        //Apply healing to all pets.
        for (var i=1; i < petStage.GetTeam(teamIndex).NumPets+1; i++)
        {
            var healing = Math.round((normalHealing + petStage.GetTeam(teamIndex).GetPet(i).BonusHealing)
                            * petStage.GetTeam(teamIndex).GetPet(i).HealingModifier);

            if (isCritting && i == randomPetIndex)
                petHelper.CheckHealing(petStage, teamIndex, i, 2*healing);
            else
                petHelper.CheckHealing(petStage, teamIndex, i, healing);
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

        //Increase damage done by all Aquatic pets.
        for (var i=1; i < 3; i++)
            for (var j=1; j < petStage.GetTeam(teamIndex).NumPets+1; j++)
                if (petStage.GetTeam(i).GetPet(j).Type == PetType.Aquatic)
                    petStage.GetTeam(i).GetPet(j).DamageModifier += 0.25;

        petStage.GetTeam(0).GetPet(0).AddAura(229, 9, true, petStage.GetTeam(teamIndex).ActivePet.Power);

        return numHits;
    }
}
