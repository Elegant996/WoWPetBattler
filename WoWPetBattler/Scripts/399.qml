// Entangling Roots - Aura
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
        if (petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).Power == 0)
            petHelper.CheckAuraPower(petStage, petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex), (teamIndex%2)+1, 400);
    }

    //Applies the aura effect to the active pet.
    function applyAura(teamIndex)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function applyAuraEnd(teamIndex, petIndex, auraIndex, duration)
    {
        if (Math.random() < petStage.GetTeam(teamIndex).GetPet(petIndex).AvoidanceRating
                || !petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).IsFresh)
            return;

        var scaleFactor = 1.50;
        var baseDamage = 30;
        var attackType = PetType.Elemental;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).Power * scaleFactor);
        var damage = Math.round((normalDamage - petStage.GetTeam(teamIndex).ActivePet.DamageOffset)
                        * petType.GetEffectiveness(attackType, petStage.GetTeam(teamIndex).ActivePet.Type)
                        * petStage.GetTeam(teamIndex).ActivePet.DefenseModifier);

        petHelper.CheckDamage(petStage, teamIndex, petIndex, 2*damage, false, false);

        if (petStage.GetTeam(teamIndex).GetPet(petIndex).Type != PetType.Critter
                && !petStage.GetTeam(0).GetPet(0).HasAura(590))
        {
            petStage.GetTeam(teamIndex).GetPet(petIndex).AddAura(248, 2, true);
            petStage.GetTeam(teamIndex).GetPet(petIndex).AddStatus(PetStatus.Rooted);
        }
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
