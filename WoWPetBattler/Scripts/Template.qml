// Template.qml
import QtQuick 2.0
import PetType 1.0
import PetStatus 1.0
import PetAction 1.0

Item
{
    property variant activePet;

    //Returns the accuracy of the pet given the move.
    function GetAccuracyRating(curTeam)
    {
        return 0;
    }

    //Returns the critical strike rating of the pet given the move.
    function GetCriticalRating(curTeam)
    {
        return 0;
    }

    //Returns the chance on hit rating if the move has any.
    function GetChanceOnHitRating(curTeam)
    {
        return 0;
    }

    //Apply the aura's effect at the start of the turn.
    function ApplyAuraStart(curTeam, curPet, duration)
    {

    }

    //Applies the aura effect to the active pet.
    function ApplyAura(curTeam)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function ApplyAuraEnd(curTeam, curPet, duration)
    {

    }

    //Grants the pet any special statuses the ability has.
    function PreUseAbility(curTeam)
    {

    }

    //Applies the ability and returns the number of hits made.
    function UseAbility(curTeam, priority, isAvoiding,
                        isHitting, isCritting, isProcing)
    {
        return 0;
    }
}
