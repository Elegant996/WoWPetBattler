// Dragonkin - Racial
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
    function GetAccuracyRating(teamIndex)
    {
        return 1;
    }

    //Returns the critical strike rating of the pet given the move.
    function GetCriticalRating(teamIndex)
    {
        return 0;
    }

    //Returns the chance on hit rating if the move has any.
    function GetChanceOnHitRating(teamIndex)
    {
        return 0;
    }

    //Apply the aura's effect at the start of the turn.
    function ApplyAuraStart(teamIndex, petIndex, auraIndex, duration)
    {
        petStage.GetTeam(curTeam).GetPet(petIndex).DamageModifier += 0.50;
    }

    //Applies the aura effect to the active pet.
    function ApplyAura(teamIndex)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function ApplyAuraEnd(teamIndex, petIndex, duration, isFresh)
    {

    }

    //Grants the pet any special statuses the ability has.
    function PreUseAbility(teamIndex)
    {

    }

    //Applies the ability and returns the number of hits made.
    function UseAbility(teamIndex, priority, isAvoiding,
                        isHitting, isCritting, isProcing)
    {
       return 0;
    }
}
