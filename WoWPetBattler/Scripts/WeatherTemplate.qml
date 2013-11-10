// Template.qml
import QtQuick 2.0
import PetType 1.0
import PetStatus 1.0
import PetAction 1.0

Item
{
    property variant curActivePet;

    //Used to allow access to static functions in PetType class.
    PetType { id: petType }

    //Used to allow access to static functions in PetHelper class.
    PetHelper { id: petHelper }

    //Returns the accuracy of the pet given the move.
    function GetAccuracyRating(curTeam)
    {
        return 1;
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
    function ApplyAuraStart(curTeam, curPet, auraIndex, duration)
    {

    }

    //Applies the aura effect to the active pet.
    function ApplyAura(curTeam)
    {

    }

    //Apply the aura's effect at the end of the turn.
    function ApplyAuraEnd(curTeam, curPet, duration, isFresh)
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
        var numHits = 0;
        var scaleFactor = 0.40;
        var baseDamage = 8;
        var normalDamage = Math.round(baseDamage + petStage.GetTeam(curTeam).ActivePet.Power * scaleFactor);
        var effectiveness = petType.GetxEffectiveness(5, petStage.GetTeam((curTeam%2)+1).Type);



        //Remove any other weather effects.
        if (petStage.GetTeam(0).GetPet(0).NumAuras > 0)
        {
            //Scorched Earth
            if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 171)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Burning);
            //Blizzard
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 205)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Chilled);
            //Sunlight
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 403)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).Health /= 1.5;
                        petStage.GetTeam(i).GetPet(j).HealingModifier -= 0.25;
                    }
            //Darkness
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 257)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).RemoveStatus(PetStatus.Blinded);
                        petStage.GetTeam(i).GetPet(j).AccuracyOffset += 0.10;
                        petStage.GetTeam(i).GetPet(j).HealingModifier += 0.50;
                    }
            //Sandstorm
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 257)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                    {
                        petStage.GetTeam(i).GetPet(j).AccuracyOffset += 0.10;
                        petStage.GetTeam(i).GetPet(j).BlockDamage = 0;
                    }
            //Moonlight
            else if (petStage.GetTeam(0).GetPet(0).GetAura(1).AuraId == 596)
                for (var i=1; i < 3; i++)
                    for (var j=1; j < petTeam.GetTeam(curTeam).NumPets+1; j++)
                        petStage.GetTeam(i).GetPet(j).HealingModifier -= 0.25;

            petStage.GetTeam(0).RemoveAura(1);
        }

        petStage.GetTeam(0).AddAura(590, 9, true, petStage.GetTeam(curTeam).ActivePet.Power);

        return numHits;
    }
}
