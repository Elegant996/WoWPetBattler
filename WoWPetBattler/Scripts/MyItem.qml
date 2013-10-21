// MyItem.qml
import QtQuick 2.0

Item
{
    function printActivePet()
    {
        console.log("Test");
        console.log(petStage);
        console.log(petStage.teams[1]);
        console.log(petStage.teams[1].activePet);
        petStage.teams[1].activePetIndex = 2;
        console.log(petStage.teams[1].activePet);
    }
}
