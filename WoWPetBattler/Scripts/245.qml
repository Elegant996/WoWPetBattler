//Dragonkin - Racial
import QtQuick 2.0
import PetType 1.0
import PetStatus 1.0
import PetAction 1.0

Item
{
    property variant curActivePet;

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
    function ApplyAuraStart(curTeam, curPet, duration)
    {
        petStage.GetTeam(curTeam).GetPet(curPet).DamageModifier += 0.50;
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
        return 0;
    }

    //Checks the damage to see if it will trigger a Magic pet's racial.
    function CheckRacialsDamage(curTeam, damage)
    {
        curActivePet = petStage.GetTeam(curTeam).ActivePet;

        if (curActivePet.Type == PetType.Magic
                && damage > curActivePet.MaxHealth * 0.35)
            return curActivePet.MaxHealth * 0.35;
        else
            return damage;
    }

    //Checks whether the Dragonkin racial should proc.
    function CheckRacialsProc(curTeam)
    {
        curActivePet = petStage.GetTeam(curTeam).ActivePet;

        //Check if active pet is Dragonkin type and has brought the other team's pet below 50%.
        if (curActivePet.ActivePet.Type == PetType.Dragonkin
                 && petStage.GetTeam((curTeam%2)+1).HealthPercentage < 0.50
                 && !curActivePet.RacialUsed)
        {
            curActivePet.RacialUsed = true;        //Racial now used.
            curActivePet.AddAura(245, 1, true);    //Will replace persisting racial.
        }
    }

    //Called by everything else to handle racial effects.
    function CheckRacials(curTeam)
    {
        curActivePet = petStage.GetTeam(curTeam).ActivePet;

        //Check if active pet is Flying type is now below 50% and racial is active.
        if (curActivePet.Type == PetType.Flying)
        {
            if (curActivePet.HealthPercentage > 0.50
                    && !curActivePet.RacialUsed)
            {
                curActivePet.Speed *= 1.5;
                curActivePet.RacialUsed = true;
            }
            else if (curActivePet.HealthPercentage <= 0.50
                     && curActivePet.RacialUsed)
            {
                curActivePet.Speed /= 1.5;
                curActivePet.RacialUsed = false;
            }
        }
        //Check if active pet is Beast type and is now above/below 25% health and racial is active/inactive.
        else if (curActivePet.Type == PetType.Beast)
        {
            //Disable the racial.
            if (curActivePet.HealthPercentage >= 0.50
                    && curActivePet.RacialUsed)
            {
                curActivePet.DamageModifier /= 1.25;
                curActivePet.RacialUsed = false;
            }
            else if (curActivePet.HealthPercentage < 0.50
                     && !curActivePet.RacialUsed)
            {
                curActivePet.DamageModifier *= 1.25;
                curActivePet.RacialUsed = true;
            }
        }
        //Check if active pet is Undead type and has just died.
        else if (curActivePet.IsDead)
        {
            if (curActivePet.Type == PetType.Undead
                && !curActivePet.RacialUsed)
            {
                curActivePet.Health = 1;                           //Ensures pet is alive.
                curActivePet.RacialUsed = true;                    //Racial now used.
                curActivePet.AddStatus(PetStatus.Unkillable);      //Pet can't die.
                curActivePet.AddAura(242, 1, true);                //Will replace persisting racial.
            }
            else if (curActivePet.Type == PetType.Mechanical)
            {
                curActivePet.Health = oppTeam.ActivePet.MaxHealth() * 0.20;    //Set pet's new health value.
                curActivePet.RacialUsed = true;                                //Racial now used.
                curActivePet.AddAura(244, 1, true);                            //Will replace persisting racial.
            }
        }
    }
}
