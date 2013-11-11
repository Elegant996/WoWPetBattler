#include "AI.h"

//Constructor
AI::AI(PetStage *petStage)
{
	//Set stage.
	this->petStage = petStage;

	qmlRegisterType<PetStage>();
	qmlRegisterType<PetTeam>();
	qmlRegisterType<Pet>("PetStatus", 1, 0, "PetStatus");
	qmlRegisterType<PetAbility>();
	qmlRegisterType<PetAction>("PetAction", 1, 0, "PetAction");
	qmlRegisterType<PetAura>();
	qmlRegisterType<PetType>("PetType", 1, 0, "PetType");
	qmlRegisterType<PetHelper>();

	//QtQml member variables.
	this->engine = new QQmlEngine;
	this->objectContext = new QQmlContext(engine->rootContext());
	this->component = new QQmlComponent(engine);

	this->tieBreaker = false;		//Used to decide if more nodes should be created.
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
Move AI::Expectiminimax(PetStage* stageNode, quint8 depth, quint8 turnIndex)
{
	Move desiredMove;		//Used for returning the desired move.

	if (depth == 0 || stageNode->IsMatchOver())
	{
		float score = 0;	//Default score.

		/*Use health values to calculate score of the node.
		Note: 52 = 5 * 1.3 * 8 (where 8 is assumed to be the average health base of pets)
		The full equation is similar to how pet health is actually calculated: petHealthPercent * 52 * Level + 100*/
		for (quint8 i=1; i < 3; i+=1)
			for (quint8 j=1; j < stageNode->GetTeam(1)->GetNumPets()+1; j+=1)
				score += ((i==1)?-1:1) * (stageNode->GetTeam(i)->GetPet(j)->GetHealthPercentage()
							* 52 * stageNode->GetTeam(i)->GetPet(j)->GetLevel() + 100);

		
		desiredMove.SetHeuristic(score);	//Pass it the score.		
		return desiredMove;					//Return the moves' value.
	}

	//Player selects action.
	if (turnIndex == 1)
	{
		//Apply weather conditions once.
		for (quint8 i=0; i < stageNode->GetTeam(0)->GetPet(0)->GetNumAuras(); i+=1)
		{
			objectContext->setContextProperty("petStage", stageNode);	
			component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)stageNode->GetTeam(0)->GetPet(0)->GetAura(i)->GetAuraId() + ".qml"));
			object = component->create(objectContext);
			//Call ApplyAuraStart; paramters are TeamNumber, PetNumber, AuraIndex and AuraDuration.
			QMetaObject::invokeMethod(object, "applyAuraStart", Q_ARG(QVariant, 0), Q_ARG(QVariant, 0), Q_ARG(QVariant, 1),
										Q_ARG(QVariant, stageNode->GetTeam(0)->GetPet(0)->GetAura(i)->GetDuration()));
			//Catch any exceptions and report them.
			if (component->status() == 3)
				while (!component->errors().isEmpty())
					emit OutputToGUI(component->errors().takeAt(0).toString());
		}

		//Begin move selection process.
		desiredMove = SelectAction(stageNode, depth, turnIndex);
		return desiredMove;
	}
	//Opponent selects action.
	else if (turnIndex == 2)
	{
		//Begin move selection process.
		desiredMove = SelectAction(stageNode, depth, turnIndex);
		return desiredMove;
	}
	//It's time to actually determine what happens when both players have selected a move.
	else	//turnIndex == 0;
	{
		//Determine who goes first.
		quint8 currentTeam = CalculatePriority(stageNode);

		float heuristic = 0.00;

		//In the case that there is a tie for speed, split the value in half and weigh each outcome.
		if (currentTeam == 3)
		{
			heuristic += 0.5 * ActionOutcomes(stageNode, depth, 1, true);
			heuristic += 0.5 * ActionOutcomes(stageNode, depth, 2, true);
		}
		//We know who's going first already, use that team.
		else
			heuristic = ActionOutcomes(stageNode, depth, currentTeam, true);

		desiredMove.SetHeuristic(heuristic);
		return desiredMove;
	}
}

//Selects the action that the pet/team will use.
Move AI::SelectAction(PetStage *stageNode, quint8 depth, quint8 turnIndex)
{
	//Apply aura effects that take place at the start of the turn.
	for (quint8 i=0; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
		for (quint8 j=1; j < stageNode->GetTeam(turnIndex)->GetPet(i)->GetNumAuras()+1; j+=1)
		{
			objectContext->setContextProperty("petStage", stageNode);	
			component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetAuraId() + ".qml"));
			object = component->create(objectContext);
			//Call ApplyAuraStart; paramters are TeamNumber, PetNumber, AuraIndex and AuraDuration.
			QMetaObject::invokeMethod(object, "applyAuraStart", Q_ARG(QVariant, turnIndex), Q_ARG(QVariant, i), Q_ARG(QVariant, j),
										Q_ARG(QVariant, stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetDuration()));
			//Catch any exceptions and report them.
			if (component->status() == 3)
				while (!component->errors().isEmpty())
					emit OutputToGUI(component->errors().takeAt(0).toString());
		}

	//Add all available actions to the list.
	QList<PetStage*> stageMoves;
	QList<Move> nextMoves;

	//Check of the pet is dead.
	/*if (stageNode->GetTeam(turnIndex)->GetActivePet()->IsDead())
		//Swap to each pet that is still able to battle.
		for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
			//Ignore same index an dead pets.
			if (stageNode->GetTeam(turnIndex)->GetActivePetIndex() != i || !stageNode->GetTeam(turnIndex)->GetPet(i)->IsDead())
			{
				//Copy the node and add it to the list.
				PetStage *actionNode = new PetStage(*stageNode);
				actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)(i+3));
				actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
				actionNode->GetTeam(turnIndex)->GetActivePet()->AddStatus(Pet::Swapping);
				stageMoves.append(actionNode);

				//Set the action and add the move to the list.
				Move nextMove;
				nextMove.SetAction((PetAction::Action)(i+3));
				nextMoves.append(nextMove);
			}*/
	//If an action is already in progress, continue to use that action.
	if (stageNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->GetRoundsRemaining() > 0)
	{
		//Copy the node and add it to the list.
		PetStage *actionNode = new PetStage(*stageNode);
		stageMoves.append(actionNode);

		//Set the action and add the move to the list.
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
					//"Pre-use" the ability to determine it's priority later.
					objectContext->setContextProperty("petStage", stageNode);	
					component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)stageNode->GetTeam(i)->GetActivePet()->GetAbility(i)->GetAbilityId() + ".qml"));
					object = component->create(objectContext);
					//Call PreUseAbility; paramters are TeamNumber. This is used to make the move tell us it's priority.
					QMetaObject::invokeMethod(object, "preUseAbility", Q_ARG(QVariant, turnIndex));
					//Catch any exceptions and report them.
					if (component->status() == 3)
						qDebug() << component->errors();

					//Copy the node and add it to the list.
					PetStage *actionNode = new PetStage(*stageNode);
					actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)i);
					stageMoves.append(actionNode);

					//Set the action and add the move to the list.
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
					//Copy the node and add it to the list.
					PetStage *actionNode = new PetStage(*stageNode);
					actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)(i+3));
					actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
					actionNode->GetTeam(turnIndex)->GetActivePet()->AddStatus(Pet::Swapping);
					stageMoves.append(actionNode);

					//Set the action and add the move to the list.
					Move nextMove;
					nextMove.SetAction((PetAction::Action)(i+3));
					nextMoves.append(nextMove);
				}

		//Passing is a valid option in some unique cases so we'll add it.
		PetStage *actionNode = new PetStage(*stageNode);
		actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::Pass);
		actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
		stageMoves.append(actionNode);

		//Set the action and add the move to the list.
		Move nextMove;
		nextMove.SetAction(PetAction::Action::Pass);
		nextMoves.append(nextMove);
	}

	//Set the action for each move.
	QList<Move>::iterator iter = nextMoves.begin();
	for (int i=0; i < stageMoves.size(); i+=1)
	{
		PetStage *nextStage = stageMoves.takeAt(0);								//Remove the stageMove from the list.
		Move currentMove = Expectiminimax(nextStage, depth, (turnIndex+1)%3);	//Set currentMove to call our Expectiminimax again.
		(*iter).SetHeuristic(currentMove.GetHeuristic());						//Set the heuristic of the move in the nextMoves list.
		delete (nextStage);														//Delete the stageMove we removed from the list earlier.
		++iter;																	//Increment the iterator to the next index of nextMoves.
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

//Determine who goes first when evaluating the round.
quint8 AI::CalculatePriority(PetStage *stageNode)
{
	//If either team is swapping pets, they get priority.
	for (quint8 i=1; i < 3; i+=1)
		if (stageNode->GetTeam(i)->GetActivePet()->HasStatus(Pet::Swapping))
			return i;

	//If either team is passing return the opposite team. Both teams passing will not affect this.
	for (quint8 i=1; i < 3; i+=1)
		if (stageNode->GetTeam(i)->GetActivePet()->GetCurrentAction()->GetAction() == PetAction::Pass)
			return (i % 2) + 1;

	//Check for priority and see if anyone has to go first.
	if (stageNode->GetTeam(1)->GetActivePet()->HasStatus(Pet::First))
		if (stageNode->GetTeam(2)->GetActivePet()->HasStatus(Pet::First))
			if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() > stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
				return 1;
			else if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() < stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
				return 2;
			else
				return (tieBreaker) ? 3 : ((qrand() % 2) + 1);		//If no tie breaking randomize it.
		else
			return 1;
	//Continue checking to see if anyone has to go first.
	else if (stageNode->GetTeam(2)->GetActivePet()->HasStatus(Pet::First))
		return 2;

	//Check for priority and see if anyone has to go second.
	if (stageNode->GetTeam(1)->GetActivePet()->HasStatus(Pet::Second))
		if (stageNode->GetTeam(2)->GetActivePet()->HasStatus(Pet::Second))
			if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() > stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
				return 2;
			else if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() < stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
				return 1;
			else
				return (tieBreaker) ? 3 : ((qrand() % 2) + 1);		//If no tie breaking randomize it.
		else
			return 1;
	//Continue checking to see if anyone has to go second.
	else if (stageNode->GetTeam(2)->GetActivePet()->HasStatus(Pet::Second))
		return 1;

	//All priorities handled, proceed based on speed.
	if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() > stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
		return 2;
	else if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() < stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
		return 1;
	else
		return (tieBreaker) ? 3 : ((qrand() % 2) + 1);		//If no tie breaking randomize it.
}

//Uses the first action during round playback. Note: Actions as a result of death happen in scripts but real deaths happen here.
float AI::ActionOutcomes(PetStage *stageNode, quint8 depth, quint8 currentTeam, bool firstCall)
{
	float heuristic = 0.00;	//Used for holding heuristic.

	//Pet swap occuring.
	if (stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction() > 3
			&& stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction() < 7)		
	{
		PetStage *currentStage = new PetStage(*stageNode);
		currentStage->GetTeam(currentTeam)->SetActivePet(currentStage->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction());
		//TODO: Call other teams move.
	}
	//Normal ability usage.
	else if (stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction() > 0
			&& stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction() < 4)
	{
		//Put the ability on cooldown.
		stageNode->GetTeam(currentTeam)->GetActivePet()->GetAbility(stageNode->GetTeam(currentTeam)
			->GetActivePet()->GetCurrentAction()->GetAction())->UseAbility();

		//Set the number of rounds the ability will persist for.
		stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(
			stageNode->GetTeam(currentTeam)->GetActivePet()->GetAbility(stageNode->GetTeam(currentTeam)
			->GetActivePet()->GetCurrentAction()->GetAction())->GetRounds());

		//Set variables to be used.
		quint16 abilityId = stageNode->GetTeam(currentTeam)->GetActivePet()->GetAbility(stageNode->GetTeam(currentTeam)->GetActivePet()->GetCurrentAction()->GetAction())->GetAbilityId();
		float avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating;
		QVariant variantAvoidanceRating, variantAccuracyRating, variantCriticalRating, variantChanceOnHitRating;

		//Set script.
		objectContext->setContextProperty("petStage", stageNode);
		component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)abilityId + ".qml"));
		object = component->create(objectContext);

		//Set QVariants based on script info.
		QMetaObject::invokeMethod(object, "getAccuracyRating", Q_RETURN_ARG(QVariant, variantAccuracyRating), Q_ARG(QVariant, currentTeam));
		QMetaObject::invokeMethod(object, "getCriticalRating", Q_RETURN_ARG(QVariant, variantCriticalRating), Q_ARG(QVariant, currentTeam));
		QMetaObject::invokeMethod(object, "getChanceOnHitRating", Q_RETURN_ARG(QVariant, variantChanceOnHitRating), Q_ARG(QVariant, currentTeam));

		//Catch any exceptions and report them.
		if (component->status() == 3)
			while (!component->errors().isEmpty())
				emit OutputToGUI(component->errors().takeAt(0).toString());

		//Set ratings based on pet info and QVariants.
		avoidanceRating = stageNode->GetTeam((currentTeam%2)+1)->GetActivePet()->GetAvoidanceRating();
		accuracyRating = variantAccuracyRating.toFloat() + stageNode->GetTeam(currentTeam)->GetActivePet()->GetAccuracyOffset();
		criticalRating = variantCriticalRating.toFloat() + stageNode->GetTeam(currentTeam)->GetActivePet()->GetCriticalStrikeRating();
		chanceOnHitRating = variantChanceOnHitRating.toFloat();

		//Check current team's opponent's pet's avoidance rating and if it is in between 0 and 1.
		//This is important as guaranteed dodge or none will not affect the move outcome in later steps.
		avoidanceRating = stageNode->GetTeam((currentTeam%2)+1)->GetActivePet()->GetAvoidanceRating();
		if (avoidanceRating > 0.00 && avoidanceRating < 1.00)
		{
			//Determine if ability can miss.
			if (accuracyRating > 0.00 && accuracyRating < 1.00)
			{
				//Determine if the ability can crit.
				if (criticalRating > 0.00 && criticalRating < 1.00)
				{
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//16 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating, true, true, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, criticalRating, 1-chanceOnHitRating, true, true, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, chanceOnHitRating, true, true, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, true, true, false, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, chanceOnHitRating, true, false, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, true, false, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, true, false, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, true, false, false, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating, false, true, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, 1-chanceOnHitRating, false, true, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, chanceOnHitRating, false, true, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, false, true, false, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, chanceOnHitRating, false, false, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, false, false, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, false, false, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, false, false, false, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, criticalRating, 1.00, true, true, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, 1.00, true, true, false, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, 1.00, true, false, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, 1.00, true, false, false, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, 1.00, false, true, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, 1.00, false, true, false, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, 1.00, false, false, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, 1.00, false, false, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{	
					bool isCritting = (criticalRating <= 0.00) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1.00, chanceOnHitRating, true, true, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1.00, 1-chanceOnHitRating, true, true, isCritting, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1.00, chanceOnHitRating, true, false, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1.00, 1-chanceOnHitRating, true, false, isCritting, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1.00, chanceOnHitRating, false, true, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1.00, 1-chanceOnHitRating, false, true, isCritting, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, chanceOnHitRating, false, false, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, 1-chanceOnHitRating, false, false, isCritting, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, accuracyRating, 1.00, 1.00, true, true, isCritting, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1-accuracyRating, 1.00, 1.00, true, false, isCritting, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, accuracyRating, 1.00, 1.00, false, true, isCritting, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, 1.00, false, false, isCritting, isProcing);
					}
				}
			}
			else	//We are going to hit no matter what or not at all.
			{
				bool isHitting = (accuracyRating <= 0.00) ? false : true;

				//Determine if the ability can crit.
				if (criticalRating > 0.00 && criticalRating < 1.00)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, criticalRating, chanceOnHitRating, true, isHitting, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, criticalRating, 1-chanceOnHitRating, true, isHitting, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1-criticalRating, chanceOnHitRating, true, isHitting, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1-criticalRating, 1-chanceOnHitRating, true, isHitting, false, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, criticalRating, chanceOnHitRating, false, isHitting, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, criticalRating, 1-chanceOnHitRating, false, isHitting, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, chanceOnHitRating, false, isHitting, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, 1-chanceOnHitRating, false, isHitting, false, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, criticalRating, 1.00, true, isHitting, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1-criticalRating, 1.00, true, isHitting, false, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, criticalRating, 1.00, false, isHitting, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, 1.00, false, isHitting, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{
					bool isCritting = (criticalRating <= 0.00) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1.00, chanceOnHitRating, true, isHitting, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1.00, 1-chanceOnHitRating, true, isHitting, isCritting, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1.00, chanceOnHitRating, false, isHitting, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1.00, 1-chanceOnHitRating, false, isHitting, isCritting, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, avoidanceRating, 1.00, 1.00, 1.00, true, isHitting, isCritting, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1-avoidanceRating, 1.00, 1.00, 1.00, false, isHitting, isCritting, isProcing);
					}
				}
			}
		}
		else	//We are either avoiding or not avoiding.
		{
			bool isAvoiding = (avoidanceRating <= 0.00) ? false : true;

			//Determine if ability can miss.
			if (accuracyRating > 0.00 && accuracyRating < 1.00)
			{
				//Determine if the ability can crit.
				if (criticalRating > 0.00 && criticalRating < 1.00)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, criticalRating, chanceOnHitRating, isAvoiding, true, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, criticalRating, 1-chanceOnHitRating, isAvoiding, true, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1-criticalRating, chanceOnHitRating, isAvoiding, true, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, true, false, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, criticalRating, chanceOnHitRating, isAvoiding, false, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, isAvoiding, false, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, isAvoiding, false, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, false, false, false);
					}
					else
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, criticalRating, 1.00, isAvoiding, true, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1-criticalRating, 1.00, isAvoiding, true, false, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, criticalRating, 1.00, isAvoiding, false, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, 1.00, isAvoiding, false, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{	
					bool isCritting = (criticalRating <= 0.00) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1.00, chanceOnHitRating, isAvoiding, true, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1.00, 1-chanceOnHitRating, isAvoiding, true, isCritting, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1.00, chanceOnHitRating, isAvoiding, false, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1.00, 1-chanceOnHitRating, isAvoiding, false, isCritting, false);
					}
					else
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, accuracyRating, 1.00, 1.00, isAvoiding, true, isCritting, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1-accuracyRating, 1.00, 1.00, isAvoiding, false, isCritting, isProcing);
					}
				}
			}
			else	//We are going to hit no matter what or not at all.
			{
				bool isHitting = (accuracyRating <= 0.00) ? false : true;
				//Determine if the ability can crit.
				if (criticalRating > 0.00 && criticalRating < 1.00)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, criticalRating, chanceOnHitRating, isAvoiding, isHitting, true, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, criticalRating, 1-chanceOnHitRating, isAvoiding, isHitting, true, false);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1-criticalRating, chanceOnHitRating, isAvoiding, isHitting, false, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, isHitting, false, false);
					}
					else
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, criticalRating, 1.00, isAvoiding, isHitting, true, isProcing);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1-criticalRating, 1.00, isAvoiding, isHitting, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{
					bool isCritting = (criticalRating <= 0.00) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > 0.00 && chanceOnHitRating < 1.00)
					{
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1.00, chanceOnHitRating, isAvoiding, isHitting, isCritting, true);
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1.00, 1-chanceOnHitRating, isAvoiding, isHitting, isCritting, false);
					}
					else
					{
						bool isProcing = (chanceOnHitRating <= 0.00) ? false : true;
						heuristic += UseAction(stageNode, depth, currentTeam, firstCall, 1.00, 1.00, 1.00, 1.00, isAvoiding, isHitting, isCritting, chanceOnHitRating);
					}
				}
			}
		}
	}

	return heuristic;
}

//Uses action given certain conditions.
float AI::UseAction(PetStage* stageNode, quint8 depth, quint8 currentTeam, bool firstCall,
						 float avoidanceRating, float hitRating, float critRating, float chanceOnHitRating,
						 bool isAvoiding, bool isHitting, bool isCritting, bool isProcing)
{
	float heuristic = 0.00;		//Used for holding heuristic.

	QVariant variantNumHits;	//Used for acquiring the number of hits.
	quint8 numHits;				//Number of hits.

	PetStage *outcome = new PetStage(*stageNode);
	objectContext->setContextProperty("petStage", outcome);
	object = component->create(objectContext);
	//Parameters are currentTeam, priority, isAvoiding, isHitting, isCritting and isPrcoing.
	QMetaObject::invokeMethod(object, "useAbility", Q_RETURN_ARG(QVariant, variantNumHits), Q_ARG(QVariant, currentTeam), Q_ARG(QVariant, ((firstCall)?1:2)),
								Q_ARG(QVariant, isAvoiding), Q_ARG(QVariant, isHitting), Q_ARG(QVariant, isCritting), Q_ARG(QVariant, isProcing));
	//Catch any exceptions and report them.
	if (component->status() == 3)
			while (!component->errors().isEmpty())
				emit OutputToGUI(component->errors().takeAt(0).toString());

	//Convert QVariant for number of hits.
	numHits = variantNumHits.toFloat();

	//If the pet died as a result of the battle.
	if (outcome->GetTeam((currentTeam%2)+1)->GetActivePet()->IsDead())
	{
		//Pet is dead, remove its current action.
		outcome->GetTeam((currentTeam%2)+1)->GetActivePet()->RemoveAuras();
		outcome->GetTeam((currentTeam%2)+1)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
		outcome->GetTeam((currentTeam%2)+1)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);

		//Attempt to find a new pet to substitute if the team is not dead.
		if (!outcome->GetTeam((currentTeam%2)+1)->IsTeamDead())
		{
			QList<PetStage*> substituteStages;
			//Find a pet that is alive.
			for (quint8 i=1; i < outcome->GetTeam((currentTeam%2)+1)->GetNumPets()+1; i+=1)
				if (!outcome->GetTeam((currentTeam%2)+1)->GetPet(i)->IsDead())
				{
					PetStage *substituteStage = new PetStage(*outcome);
					substituteStage->GetTeam((currentTeam%2)+1)->SetActivePet(i);
					substituteStage->GetTeam((currentTeam%2)+1)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
					substituteStage->GetTeam((currentTeam%2)+1)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);
					//Pet swap has occured; Use Minefield, etc..
					for (quint8 j=1; j < substituteStage->GetTeam((currentTeam%2)+1)->GetPet(0)->GetNumAuras()+1; j+=1)
						if (substituteStage->GetTeam((currentTeam%2)+1)->GetPet(0)->GetAura(j)->OnSwapIn())
						{
							QMetaObject::invokeMethod(object, "applyAura", Q_ARG(QVariant, (currentTeam%2)+1));		//Use the aura; parameters are teamIndex.
							//Catch any exceptions and report them.
							if (component->status() == 3)
								while (!component->errors().isEmpty())
									emit OutputToGUI(component->errors().takeAt(0).toString());
							substituteStage->GetTeam((currentTeam%2)+1)->GetPet(0)->RemoveAura(j);					//Remove the aura.
							break;																					//There should not be more than 1.
						}
					substituteStages.append(substituteStage);														//Append the substitute stage to the QList.
				}
							
			quint8 tempSize = substituteStages.size();		//Temporary size variable for dividing.
			for (quint8 i=0; i < substituteStages.size(); i+=1)
			{
				//If it is the first time this function was called we must still process the other team's action.
				if (firstCall)
					//If there is more than one option divide by the size (max 2 pets to choose from).
					heuristic += avoidanceRating * hitRating * critRating * ActionOutcomes(substituteStages.at(i), depth, (currentTeam%2)+1, false) / tempSize;
				else
					heuristic += avoidanceRating * hitRating * critRating * EndTurn(outcome, depth);
				delete (substituteStages.takeAt(0));
			}
			substituteStages.clear();
		}
		else	//No living pet found, let's just move on.
			//If it is the first time this function was called we must still process the other team's action.
			if (firstCall)
				heuristic += avoidanceRating * hitRating * critRating * ActionOutcomes(outcome, depth, (currentTeam%2)+1, false);
			else
				heuristic += avoidanceRating * hitRating * critRating * EndTurn(outcome, depth);
	}
	else
	{
		//If it is the first time this function was called we must still process the other team's action.
		if (firstCall)
			heuristic += avoidanceRating * hitRating * critRating * ActionOutcomes(outcome, depth, (currentTeam%2)+1, false);
		else
			heuristic += avoidanceRating * hitRating * critRating * EndTurn(outcome, depth);
	}
					
	delete outcome;

	return heuristic;
}

//Apply auras at the end of the turn.
float AI::EndTurn(PetStage* stageNode, quint8 depth)
{
	Move nextTurn;						//Used calling Expectiminimax.
	float heuristic = 0;				//What will be returned.
	QList<PetStage*> substituteStages;	//Used for when the pet dies and we have other options.

	for (quint8 i=0; i < 3; i+=1)															//For each team...
		for (quint8 j=0; j < stageNode->GetTeam(i)->GetNumPets()+1; j+=1)					//For each pet...
			for (quint8 k=1; k < stageNode->GetTeam(i)->GetPet(j)->GetNumAuras()+1; k+=1)	//For each aura...
			{
				objectContext->setContextProperty("petStage", stageNode);	
				component->loadUrl(QUrl::fromLocalFile("Scripts/" + (QString)stageNode->GetTeam(i)->GetPet(j)->GetAura(k)->GetAuraId() + ".qml"));
				object = component->create(objectContext);
				//Call ApplyAuraEnd; paramters are TeamNumber, PetNumber and AuraDuration.
				QMetaObject::invokeMethod(object, "applyAuraEnd", Q_ARG(QVariant, i), Q_ARG(QVariant, j), Q_ARG(QVariant, k),
					Q_ARG(QVariant, stageNode->GetTeam(i)->GetPet(j)->GetAura(k)->GetDuration()));
				//Catch any exceptions and report them.
				if (component->status() == 3)
				while (!component->errors().isEmpty())
					emit OutputToGUI(component->errors().takeAt(0).toString());
			}


	//Check to see if a pet is dead.
	quint8 tempSize = 0;
	for (quint8 i=1; i < 3; i+=1)
	{
		tempSize = substituteStages.size();

		//If the pet died as a result of the aura's effect.
		if (stageNode->GetTeam(i)->GetActivePet()->IsDead())
		{
			//Pet is dead, remove its auras and clean-up.
			stageNode->GetTeam(i)->GetActivePet()->RemoveAuras();
			stageNode->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
			stageNode->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);

			//Attempt to find a new pet to substitute if the team is not dead.
			if (!stageNode->GetTeam(i)->IsTeamDead())
			{
				//Find a pet that is alive.
				for (quint8 j=1; j < stageNode->GetTeam(i)->GetNumPets()+1; j+=1)
					if (!stageNode->GetTeam(i)->GetPet(j)->IsDead())
					{
						//Check to see if there are already some stages in the QList indicating that both pets fainted this round.
						if (tempSize > 0)
							//This happens to each outcome then.
							for (quint8 k=0; k < tempSize; k+=1)
							{
								PetStage *substituteStage = new PetStage(*substituteStages.at(k));
								substituteStage->GetTeam(i)->SetActivePet(j);
								substituteStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
								substituteStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);
								//Pet swap has occured; Use Minefield, etc..
								for (quint8 l=1; l < substituteStage->GetTeam(i)->GetPet(0)->GetNumAuras()+1; l+=1)
									if (substituteStage->GetTeam(i)->GetPet(0)->GetAura(l)->OnSwapIn())
									{
										QMetaObject::invokeMethod(object, "applyAura", Q_ARG(QVariant, i));		//Use the aura; parameters are teamIndex.
										//Catch any exceptions and report them.
										if (component->status() == 3)
										while (!component->errors().isEmpty())
											emit OutputToGUI(component->errors().takeAt(0).toString());
										substituteStage->GetTeam(i)->GetPet(0)->RemoveAura(l);					//Remove the aura.
										break;																	//There should not be more than 1.
									}
								substituteStages.append(substituteStage);										//Append the substitute stage to the QList.	
							}
						else	//No substitute stages so far so we can copy stageNode.
						{
							PetStage *substituteStage = new PetStage(*stageNode);
							substituteStage->GetTeam(i)->SetActivePet(j);
							substituteStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
							substituteStage->GetTeam(i)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);
							//Pet swap has occured; Use Minefield, etc..
							for (quint8 k=1; k < substituteStage->GetTeam(i)->GetPet(0)->GetNumAuras()+1; k+=1)
								if (substituteStage->GetTeam(i)->GetPet(0)->GetAura(k)->OnSwapIn())
								{
									QMetaObject::invokeMethod(object, "applyAura", Q_ARG(QVariant, i));		//Use the aura; parameters are teamIndex.
									//Catch any exceptions and report them.
									if (component->status() == 3)
										while (!component->errors().isEmpty())
											emit OutputToGUI(component->errors().takeAt(0).toString());
									substituteStage->GetTeam(i)->GetPet(0)->RemoveAura(k);					//Remove the aura.
									break;																	//There should not be more than 1.
								}
							substituteStages.append(substituteStage);										//Append the substitute stage to the QList.	
						}
					}
			}
		}
	}

	//Process the substitute stages.
	tempSize = substituteStages.size();
	if (tempSize > 0)
	{
		for (quint8 i=0; i < substituteStages.size(); i+=1)
		{
			//Update the round.
			substituteStages.at(i)->RoundUpdate();
			//Call Expectiminimax again, reduce depth by 1 as we are proceeding into the next turn.
			nextTurn = Expectiminimax(substituteStages.at(i), depth-1, 1);
			//Add the heuristic to our return value.
			heuristic += nextTurn.GetHeuristic() / tempSize;

			delete (substituteStages.takeAt(0));
		}
		substituteStages.clear();
	}
	else
	{
		//Update the round.
		stageNode->RoundUpdate();
		//Call Expectiminimax again, reduce depth by 1 as we are proceeding into the next turn.
		nextTurn = Expectiminimax(stageNode, depth-1, 1);
	}

	//Return heuristic.
	return nextTurn.GetHeuristic();
}