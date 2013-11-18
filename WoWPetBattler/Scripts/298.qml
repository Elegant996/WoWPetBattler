// Inspiring Song - Ability
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
        return 0;
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
        var scaleFactor = 0.60;
        var baseHealing = 12;
        var attackType = PetType.Elemental;
        var normalHealing = Math.round(baseHealing + petStage.GetTeam(teamIndex).ActivePet.Power * scaleFactor);

        //Used below.
        var randomPetIndex = Math.floor((Math.random()*petStage.GetTeam(teamIndex).NumPets)+1);

        //Apply healing to all pets.
        for (var i=1; i < petStage.GetTeam(teamIndex).NumPets+1; i++)
        {
            var healing = Math.round(normalHealing * petStage.GetTeam(teamIndex).GetPet(i).HealingModifier);

            if (isCritting && i == randomPetIndex)
                petHelper.CheckHealing(petStage, teamIndex, i, 2*healing, true);
            else
                petHelper.CheckHealing(petStage, teamIndex, i, healing, true);
        }

        return numHits;
    }
}
