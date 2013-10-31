#include "AI.h"

//Constructor
AI::AI(PetStage *petStage)
{
	qmlRegisterType<PetStage>();
	qmlRegisterType<PetTeam>();
	qmlRegisterType<Pet>("PetStatus", 1, 0, "PetStatus");
	qmlRegisterType<PetAbility>();
	qmlRegisterType<PetAction>("PetAction", 1, 0, "PetAction");
	qmlRegisterType<PetAura>();
	qmlRegisterType<PetType>("PetType", 1, 0, "PetType");

	//QtQml member variables.
	this->engine = new QQmlEngine;
	this->objectContext = new QQmlContext(engine->rootContext());
	this->component = new QQmlComponent(engine);

	this->petStage = petStage;
}

//Destructor
AI::~AI(void)
{
	delete component;
	delete objectContext;
	delete engine;
}

//Accept the queue when it has popped.
void AI::QueueUp()
{
	//keyboard.Click("`");		//Accept Queue.
	qDebug() << "`";
}

//Queue up for PvP Battle.
void AI::AcceptQueue()
{
	//keyboard.Click("`");		//Queue Up.	
	qDebug() << "`";
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
}

//Modified minimax that also uses expected in computation.
Move AI::Expectiminimax(PetStage* stageNode, int depth)
{
	/*Important for setup procedure
	objectContext->setContextProperty("petStage", stageNode);	
	component->loadUrl(QUrl::fromLocalFile("Scripts/MyItem.qml"));
	object = component->create(objectContext);
	QMetaObject::invokeMethod(object, "printActivePet");
	*/

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

	return Move();
}

Move AI::temp(PetStage* stageNode, int depth, int turnIndex)
{
	if (depth == 0 || stageNode->IsMatchOver())
	{
		float score = 0;	//Default score.

		/*Use health values to calculate score of the node.
		Note: 52 = 5 * 1.3 * 8 (where 8 is assumed to be the average health base of pets)
		The full equation is similar to how pet health is actually calculated: petHealthPercent * 52 * Level + 100*/
		for (quint8 i=1; i < 3; i+=1)
			for (quint8 j=1; j < stageNode->GetTeam(1)->GetNumPets()+1; j+=1)
				score += ((i==1)?-1:1) * (stageNode->GetTeam(i)->GetPet(j)->GetHealth() / stageNode->GetTeam(i)->GetPet(j)->GetMaxHealth())
							* (52 * stageNode->GetTeam(i)->GetPet(j)->GetLevel() + 100);

		//Create Move object and pass it the score.
		Move moveValue;
		moveValue.SetHeuristic(score);

		//Return the moves' value.
		return moveValue;
	}

	if (turnIndex != 0)
	{
		//Apply aura effects that take place at the start of the turn.
		for (quint8 i=0; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
			for (quint8 j=1; j < stageNode->GetTeam(turnIndex)->GetPet(i)->GetNumAuras()+1; j+=1)
			{
				stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetAuraId();
				objectContext->setContextProperty("petStage", stageNode);	
				component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetAuraId() + ".qml"));
				object = component->create(objectContext);
				//Call ApplyAuraStart; paramters are TeamNumber, PetNumber and AuraDuration.
				QMetaObject::invokeMethod(object, "ApplyAuraStart", Q_ARG(QVariant, turnIndex), Q_ARG(QVariant, i),
											Q_ARG(QVariant, stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetDuration()));
			}

		//Add all available actions to the list.
		QList<PetStage*> stageMoves;
		QList<Move> nextMoves;

		//If an action is already in progress, continue to use that action.
		if (stageNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->GetRoundsRemaining() > 0)
		{
			PetStage *actionNode = new PetStage(*stageNode);
			stageMoves.append(actionNode);

			Move nextMove;
			nextMove.SetAction(actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->GetAction());
			nextMoves.append(nextMove);
		}
		else	//There is no active ability, use selection process.
		{
			//Check to see if we can select an ability for the current round.
			if (!stageNode->GetTeam(turnIndex)->GetActivePet()->HasStatus(Pet::Asleep)
					&& !stageNode->GetTeam(turnIndex)->GetActivePet()->HasStatus(Pet::Polymorphed)
					&& !stageNode->GetTeam(turnIndex)->GetActivePet()->HasStatus(Pet::Stunned))
				for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetActivePet()->GetNumAbilities()+1; i+=1)
					//Use the ability if it is off cooldown.
					if (stageNode->GetTeam(turnIndex)->GetActivePet()->GetAbility(i)->GetCooldown() == 0)
					{
						PetStage *actionNode = new PetStage(*stageNode);
						actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)i);
						stageMoves.append(actionNode);

						Move nextMove;
						nextMove.SetAction((PetAction::Action)i);
						nextMoves.append(nextMove);
					}
		
			//Check to see if swapping a pet is possible.
			if (!stageNode->GetTeam(turnIndex)->GetActivePet()->HasStatus(Pet::Rooted))
				//Swap to each pet that is still able to battle.
				for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
					//Ignore same index an dead pets.
					if (stageNode->GetTeam(turnIndex)->GetActivePetIndex() != i || !stageNode->GetTeam(turnIndex)->GetPet(i)->IsDead())
					{
						PetStage *actionNode = new PetStage(*stageNode);
						actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)(i+3));
						actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
						actionNode->GetTeam(turnIndex)->GetActivePet()->AddStatus(Pet::Swapping);
						stageMoves.append(actionNode);

						Move nextMove;
						nextMove.SetAction((PetAction::Action)(i+3));
						nextMoves.append(nextMove);
					}

			//Passing is a valid option in some unique cases so we'll add it.
			PetStage *actionNode = new PetStage(*stageNode);
			actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::Pass);
			actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
			stageMoves.append(actionNode);

			Move nextMove;
			nextMove.SetAction(PetAction::Action::Pass);
			nextMoves.append(nextMove);
		}

		//Set the action for each move.
		QList<Move>::iterator iter = nextMoves.begin();
		for (int i=0; i < stageMoves.size(); i+=1)
		{
			PetStage *nextStage = stageMoves.takeAt(0);							//Remove the stageMove from the list.
			Move currentMove = temp(nextStage, depth-1, (turnIndex+1)%3);		//Set currentMove to call our Expectiminimax again.
			(*iter).SetHeuristic(currentMove.GetHeuristic());					//Set the heuristic of the move in the nextMoves list.
			delete (nextStage);													//Delete the stageMove we removed from the list earlier.
			++iter;																//Increment the iterator to the next index of nextMoves.
		}

		//Empty stageMoves QList.
		stageMoves.clear();

		//Re-use iterator.
		iter = nextMoves.begin();
		Move desiredMove = (*iter);

		//Maximize.
		if (turnIndex == 1)
			for (iter; iter != nextMoves.end(); ++iter)
				if ((*iter).GetHeuristic() > desiredMove.GetHeuristic())
					desiredMove = (*iter);
		//Minimize.
		else	//turnIndex == 2;
			for (iter; iter != nextMoves.end(); ++iter)
				if ((*iter).GetHeuristic() < desiredMove.GetHeuristic())
					desiredMove = (*iter);

		//Empty the nextMoves QList.
		nextMoves.clear();

		//Return the best move.
		return desiredMove;
	}
	//It's time to actually determine what happens when both players have selected a move.
	else	//turnIndex == 0;
	{
		//Determine who goes first.
		quint8 startingTeam = CalculatePriority();

		return Move();
	}
}

//Determine who goes first when evaluating the round.
quint8 AI::CalculatePriority()
{
	return 0;
}