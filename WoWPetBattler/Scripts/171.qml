// Scorched Earth - Weather
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
        //Find power if it is 0.
        if (petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).Power == 0)
            petHelper.CheckAuraPower(petStage, petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex), 3, 172);

        //Apply Scorched Earth effects.
        for (var i=1; i < 3; i++)
            for (var j=1; j < petStage.GetTeam(i).NumPets+1; j++)
                if (petStage.GetTeam(i).GetPet(j).Type != PetType.Elemetal)
                    petStage.GetTeam(i).GetPet(j).AddStatus(PetStatus.Burning);
    }

    //Applies the aura effect to the active pet.
    function applyAura(teamIndex)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function applyAuraEnd(teamIndex, petIndex, auraIndex, duration)
    {        
        var scaleFactor = 0.2;
        var baseDamage = 4;
        var attackType = PetType.Elemental;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(teamIndex).GetPet(petIndex).GetAura(auraIndex).Power * scaleFactor);

        //Apply the weather effect to each team.
        for (var i=1; i < 3; i++)
        {
            var damage = Math.round((normalDamage - petStage.GetTeam(i).ActivePet.DamageOffset)
                                    * petType.GetEffectiveness(attackType, petStage.GetTeam(i).Type)
                                    * petStage.GetTeam(i).ActivePet.DefenseModifier);

            if (petStage.GetTeam(i).ActivePet.Type != PetType.Elemetal)
                petHelper.CheckDamage(petStage, i, petStage.GetTeam(i).ActivePetIndex, damage, false, false);
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
