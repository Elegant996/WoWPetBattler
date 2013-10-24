// MyItem.qml
import QtQuick 2.0

Item
{
    function printActivePet()
    {
        console.log("Test");
        console.log(petStage);
        console.log(petStage.Teams[1]);
        console.log(petStage.Teams[1].ActivePet);
        petStage.Teams[1].ActivePetIndex = 2;
        console.log(petStage.Teams[1].ActivePet);
        console.log(petStage.Teams[1].ActivePet.Health);
    }
}
