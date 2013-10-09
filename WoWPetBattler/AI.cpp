#include "AI.h"

//Constructor
AI::AI(PetStage *petStage)
{
	this->petStage = petStage;
}

//Destructor
AI::~AI(void)
{
}

void AI::Run()
{
	//PostMessage((HWND)window->GetHandle(), 
	keyboard.AutoDelay = (5, 10);
	if (petStage->SelectAbility())
		qDebug() << "Select Ability";
	else if (petStage->SelectPet() && petStage->Initialized())
		qDebug() << "Select Pet";
	else if (petStage->SelectPet() && !petStage->Initialized())
		qDebug() << "F1";
		//keyboard.Click("F1");	//Select First Pet
	else if (petStage->QueueState() == 3)
		//keyboard.Click("`");		//Accept Queue
		qDebug() << "`";
	else if (petStage->QueueState() == 0)
		//keyboard.Click("`");	//Queue Up
		qDebug() << "`";
}