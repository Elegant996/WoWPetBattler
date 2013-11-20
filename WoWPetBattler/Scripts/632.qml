// Confusing Sting - Ability
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
        //Check whether it is avoid/crit/hit/proc.
        if (!isAvoiding && isHitting)
        {
            petStage.GetTeam((teamIndex%2)+1).ActivePet.AddAura(633, 5, true, teamIndex, petStage.GetTeam(teamIndex).ActivePetIndex, petStage.GetTeam(teamIndex).ActivePet.Power);
            petStage.GetTeam((teamIndex%2)+1).ActivePet.AddStatus(PetStatus.Poisoned);
        }

        return numHits;
    }
}
