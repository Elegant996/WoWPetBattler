// Slicing Wind - Ability
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
        var scaleFactor = 0.5;
        var baseDamage = 10;
        var attackType = PetType.Flying;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(teamIndex).ActivePet.Power * scaleFactor);
        var damage = Math.round((normalDamage - petStage.GetTeam((teamIndex%2)+1).ActivePet.DamageOffset)
                        * petType.GetEffectiveness(attackType, petStage.GetTeam((teamIndex%2)+1).ActivePet.Type)
                        * petStage.GetTeam((teamIndex%2)+1).ActivePet.DefenseModifier
                        * (petStage.GetTeam(teamIndex).ActivePet.DamageModifier
                           + CheckWeatherDamageBonus(petStage, attackType)));

        //Used below.
        var randomNumHits = Math.floor((Math.random()*3)+1);
        var critHit = Math.floor((Math.random()*randomNumHits)+1);
        var hitHit = -1;
        if (!isHitting)
            hitHit = Math.floor((Math.random()*randomNumHits)+1);

        //Check whether it is avoid/crit/hit/proc.
        if (!isAvoiding)
        {
            for (var i=0; i < randomNumHits; i++)
            {
                numHits += 1;
                if (isCritting && critHit == i+1 && hitHit != i+1)
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, petStage.GetTeam((teamIndex%2)+1).ActivePetIndex, 2*damage, true, true);
                else if (hitHit != i+1)
                    petHelper.CheckDamage(petStage, (teamIndex%2)+1, petStage.GetTeam((teamIndex%2)+1).ActivePetIndex, damage, true, true);
            }
        }

        return numHits;
    }
}
