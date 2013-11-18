// Plagued Blood - Aura
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
        if (petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).Power == 0)
            petHelper.CheckAuraPower(petStage, petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex), (teamIndex%2)+1, 657);
    }

    //Applies the aura effect to the active pet.
    function applyAura(teamIndex)
    {
        //petHelper.CheckHealing(petStage, (teamIndex%2)+1, petStage.GetTeam((teamIndex%2)+1).ActivePetIndex, Math.round(petStage.GetTeam((teamIndex%2)+1).ActivePet.MaxHealth * 0.01), false);
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
        return 0;
    }
}
