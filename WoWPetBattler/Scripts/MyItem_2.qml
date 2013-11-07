// MyItem2.qml
import QtQuick 2.0
import PetType 1.0
import PetStatus 1.0
import PetAction 1.0

Item
{
    property int petPos: 2;
    property variant petPos2: 4;
    property string test: "Hello";
    property variant myTest: petStage.GetTeam(1);

    function printActivePet(value)
    {
        //myTest = petStage.GetTeam(1);
        console.log("Override");
        console.log(petStage);
        console.log(petStage.GetTeam(1));
        console.log(petStage.GetTeam(1).ActivePet);
        petStage.GetTeam(1).ActivePetIndex = petPos;
        petStage.GetTeam(1).ActivePetIndex += 1;
        console.log(petStage.GetTeam(1).ActivePet);
        console.log(petStage.GetTeam(1).ActivePet.Health);
        console.log(petStage.GetTeam(1).ActivePet.GetAbility(1));
        petStage.GetTeam(1).ActivePet.AddStatus(PetStatus.Stunned);
        console.log(petStage.GetTeam(1).ActivePet.GetStatus(1));
        console.log(value);
        console.log("Test: " + myTest.ActivePetIndex);
        console.log("Type: " + PetType.Humanoid);
        console.log(petStage.GetTeam(1).ActivePet.GetCurrentAction().Action);
        petStage.GetTeam(1).ActivePet.GetCurrentAction().Action = 1;
        console.log(petStage.GetTeam(1).ActivePet.GetCurrentAction().Action);
        console.log("myTest: " + myTest);
    }

    function testFunction()
    {
        return 5;
    }
}
