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
	if (petStage->SelectAbility())
		qDebug() << "Select Ability";
	else if (petStage->SelectPet() && petStage->Initialized())
		qDebug() << "Select Pet";
	else if (petStage->SelectPet() && !petStage->Initialized())
		qDebug() << "Select First Pet";
	else if (petStage->QueueState() == 3)
		qDebug() << "Accept Queue";
	else if (petStage->QueueState() == 0)
	{
		keyboard.AutoDelay = (15, 20);
		keyboard.Click("~/run +C+-+Pet+Battles.+Start+P+V+P+Matchmaking+9+0~");
		qDebug() << "Queue";
	}
}