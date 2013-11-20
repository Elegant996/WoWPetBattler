// Surge - Ability
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
        //This ability goes first.
        petStage.GetTeam(teamIndex).ActivePet.AddStatus(PetStatus.First);
    }

    //Applies the ability and returns the number of hits made.
    function useAbility(teamIndex, curRound, isFirst, isAvoiding,
                        isHitting, isCritting, isProcing)
    {
        var numHits = 0;
        var scaleFactor = 0.75;
        var baseDamage = 15;
        var attackType = PetType.Aquatic;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(teamIndex).ActivePet.Power * scaleFactor);
        var damage = Math.round((normalDamage - petStage.GetTeam((teamIndex%2)+1).ActivePet.DamageOffset)
                        * petType.GetEffectiveness(attackType, petStage.GetTeam((teamIndex%2)+1).ActivePet.Type)
                        * petStage.GetTeam((teamIndex%2)+1).ActivePet.DefenseModifier
                        * (petStage.GetTeam(teamIndex).ActivePet.DamageModifier
							+ petHelper.CheckWeatherBonus(petStage, attackType)));

        //Check whether it is avoid/crit/hit/proc.
        if (!isAvoiding && isHitting)
        {
            numHits += 1;
            if (isCritting)
                petHelper.CheckDamage(petStage, (teamIndex%2)+1, petStage.GetTeam((teamIndex%2)+1).ActivePetIndex, 2*damage, true, true);
            else
                petHelper.CheckDamage(petStage, (teamIndex%2)+1, petStage.GetTeam((teamIndex%2)+1).ActivePetIndex, damage, true, true);
        }

        return numHits;
    }
}
