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

//Begin AI simulation and respond with best move.
void AI::Run()
{
	//PostMessage((HWND)window->GetHandle(), 
	//keyboard.AutoDelay = (5, 10);
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

//Modified minimax that also uses expected in computation.
Move Expectiminimax(PetStage* stageNode, int depth)
{
	//Get weather.
	PetAura *weather = NULL;
	if (stageNode->GetTeam(0)->GetPet(0)->GetNumAuras() != 0)
		weather = stageNode->GetTeam(0)->GetPet(0)->GetAura(1);

	//Assess weather situation.
	if (weather != NULL)
	{

	}

	//Who goes first?
	if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() > stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
	{
	}
	else if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() < stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
	{
	}
	else	//It's a tie.
	{
		int index = (qrand() % 2) + 1;	//Decide pet team index randomly, as the game will do the same.
	}

	//Create a list of all possible moves that can be made at this node.
	QList<PetStage*> stageMove;
	if (stageNode->SelectAbility())
	{
	}
	else if (stageNode->SelectPet())
	{
		for (int i=0; i <stageNode->GetTeam(1)->GetNumPets(); i+=1)
			if (stageNode->GetTeam(1)->GetPet(i)->GetHealth() > 0)
			{
				PetStage *tempStage = new PetStage(*stageNode);
				tempStage->GetTeam(1)->SetActivePet(i);
				stageMove.append(tempStage);
			}
	}

	return Move(0);
}