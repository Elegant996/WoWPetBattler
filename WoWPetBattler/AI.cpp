#include "AI.h"

//Constructor
AI::AI(PetStage *petStage, Robot::Window *window)
{
	this->petStage = petStage;
	this->window = window;
}

//Destructor
AI::~AI(void)
{
}

void AI::Run()
{
	//PostMessage((HWND)window->GetHandle(), 
	keyboard.AutoDelay = (15, 20);
	if (petStage->SelectAbility())
		qDebug() << "Select Ability";
	else if (petStage->SelectPet() && petStage->Initialized())
		qDebug() << "Select Pet";
	else if (petStage->SelectPet() && !petStage->Initialized())
		keyboard.Click("F1");	//Select First Pet
	else if (petStage->QueueState() == 3)
		qDebug() << "`";		//Accept Queue
	else if (petStage->QueueState() == 0)
		keyboard.Click("`");	//Queue Up
}