#include "AI.h"

//Constructor
AI::AI(PetStage *petStage, Robot::Window *window)
{
	this->petStage = petStage;	//Set stage.
	this->window = window;		//Set the window.

	this->LoadPreferences();	//Setup thresholds.

	this->qmlResourcesLoaded = false;
}

//Destructor
AI::~AI(void)
{
	if (qmlResourcesLoaded)
	{
		delete component;
		delete objectContext;
		engine->deleteLater();
	}
}

//Load preferences.
void AI::LoadPreferences()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open the group.
	setting.beginGroup("Thresholds");

	//Fetch avoidance rating.
	this->minAvoidanceThreshold = setting.value("minAvoidanceThreshold", 0).toFloat() * 0.05;
	this->maxAvoidanceThreshold = setting.value("maxAvoidanceThreshold", 20).toFloat() * 0.05;

	//Fetch hit rating.
	this->minHitThreshold = setting.value("minHitThreshold", 0).toFloat() * 0.05;
	this->maxHitThreshold = setting.value("maxHitThreshold", 16).toFloat() * 0.05;

	//Fetch crit rating.
	this->minCritThreshold = setting.value("minCritThreshold", 1).toFloat() * 0.05;
	this->maxCritThreshold = setting.value("maxCritThreshold", 20).toFloat() * 0.05;

	//Fetch chance on hit rating.
	this->minChanceOnHitThreshold = setting.value("minChanceOnHitThreshold", 0).toFloat() * 0.05;
	this->maxChanceOnHitThreshold = setting.value("maxChanceOnHitThreshold", 20).toFloat() * 0.05;

	//Close the group.
	setting.endGroup();

	//Open Options group.
	setting.beginGroup("Options");

	//Define limitations.
	this->tieBreaker = setting.value("AutoDecideTies", true).toBool();
	this->canPass = setting.value("CanPass", false).toBool();

	//Set depth of the search.
	this->depth = setting.value("TurnDepth", 3).toInt();

	//Fetch heuristic from radio buttons.
	this->heuristicType = (HeuristicType)setting.value("Heuristic", AI::CurrentHealth).toInt();

	//Close Options group.
	setting.endGroup();
}

void AI::LoadQMLResources()
{
	//Register all QML types.
	qmlRegisterType<PetStage>();
	qmlRegisterType<PetTeam>();
	qmlRegisterType<Pet>("PetStatus", 1, 0, "PetStatus");
	qmlRegisterType<PetAbility>();
	qmlRegisterType<PetAction>("PetAction", 1, 0, "PetAction");
	qmlRegisterType<PetAura>();
	qmlRegisterType<PetType>("PetType", 1, 0, "PetType");
	qmlRegisterType<PetHelper>("PetHelper", 1, 0, "PetHelper");

	//QtQml member variables.
	this->engine = new QQmlEngine;
	this->objectContext = new QQmlContext(engine->rootContext());
	this->component = new QQmlComponent(engine);

	//Set QML resources loaded flag to true.
	this->qmlResourcesLoaded = true;
}

//Accept the queue when it has popped.
void AI::QueueUp()
{
	PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyGrave, NULL);
	QThread::msleep(66);
	PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyGrave, NULL);
}

//Queue up for PvP Battle.
void AI::AcceptQueue()
{
	PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyGrave, NULL);
	QThread::msleep(66);
	PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyGrave, NULL);
}

//Begin AI simulation and respond with best move.
void AI::Run(bool initialized)
{
	Move nextMove;		//Holds next ability.

	//Run Expectiminimax if select ability or select pet is present.
	if (initialized)
		nextMove = this->Expectiminimax(this->petStage, this->depth, -4500, 4500, 1);
	//If we are not initialized select the first pet.
	else
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyF1, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyF1, NULL);
		return;		//Avoid the content below.
	}

	//If next move is to use ability 1 press '1'.
	if (nextMove.GetAction() == PetAction::Ability1)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::Key1, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::Key1, NULL);
	}
	//If next move is to use ability 2 press '2'.
	else if (nextMove.GetAction() == PetAction::Ability2)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::Key2, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::Key2, NULL);
	}
	//If next move is to use ability 3 press '3'.
	else if (nextMove.GetAction() == PetAction::Ability3)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::Key3, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::Key3, NULL);
	}
	//If next move is to swap to pet 1 press 'F1'.
	else if (nextMove.GetAction() == PetAction::Pet1)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyF1, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyF1, NULL);
	}
	//If next move is to swap to pet 2 press 'F2'.
	else if (nextMove.GetAction() == PetAction::Pet2)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyF2, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyF2, NULL);
	}
	//If next move is to swap to pet 3 press 'F3'.
	else if (nextMove.GetAction() == PetAction::Pet3)
	{
		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyF3, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyF3, NULL);
	}
	//We are passing, so press 'T'.
	else
	{
		//Do not pass if it's actually over.
		if (petStage->IsMatchOver())
			return;

		PostMessage((HWND)this->window->GetHandle(), WM_KEYDOWN, Robot::KeyT, NULL);
		QThread::msleep(66);
		PostMessage((HWND)this->window->GetHandle(), WM_KEYUP, Robot::KeyT, NULL);
	}
}

//Modified minimax that also uses expected in computation.
Move AI::Expectiminimax(PetStage* petStage, quint8 depth, float alpha, float beta, quint8 turnIndex)
{
	PetStage *stageNode = new PetStage(*petStage);		//Copy the stage.
	Move desiredMove;									//Used for returning the desired move.

	if (depth == 0 || stageNode->IsMatchOver())
	{
		float score = 0.00;	//Default score.

		/*Use health values to calculate score of the node.
		Note: 52 = 5 * 1.3 * 8 (where 8 is assumed to be the average health base of pets)
		The full equation is similar to how pet health is actually calculated: petHealthPercent * 52 * Level + 100*/
		for (quint8 i=1; i < 3; i+=1)
			for (quint8 j=1; j < stageNode->GetTeam(1)->GetNumPets()+1; j+=1)
			{
				//Used the specified heuristic.
				if (this->heuristicType == CurrentHealth)
					score += ((i==1)?1:-1) * stageNode->GetTeam(i)->GetPet(j)->GetHealth();
				else if (this->heuristicType == FixedHealth)
					score += ((i==1)?1:-1) * (stageNode->GetTeam(i)->GetPet(j)->GetHealthPercentage()
							* (52 * stageNode->GetTeam(i)->GetPet(j)->GetLevel() + 100));
			}

		
		desiredMove.SetHeuristic(score);	//Pass it the score.
		delete stageNode;					//Clean up.
		return desiredMove;					//Return the moves' value.
	}

	//Player selects action.
	if (turnIndex == 1)
	{
		//Apply weather conditions once.
		for (quint8 i=1; i < stageNode->GetTeam(0)->GetPet(0)->GetNumAuras()+1; i+=1)
		{
			objectContext->setContextProperty("petStage", stageNode);	
			component->loadUrl(QUrl::fromLocalFile("Scripts/" + QString::number(stageNode->GetTeam(0)->GetPet(0)->GetAura(i)->GetAuraId()) + ".qml"));
			//Catch any exceptions and report them.
			if (component->status() != QQmlComponent::Ready)
				emit OutputToGUI(component->errorString());
			object = component->create(objectContext);
			//Call ApplyAuraStart; paramters are TeamNumber, PetNumber, AuraIndex and AuraDuration.
			QMetaObject::invokeMethod(object, "applyAuraStart", Q_ARG(QVariant, 0), Q_ARG(QVariant, 0), Q_ARG(QVariant, 1),
										Q_ARG(QVariant, stageNode->GetTeam(0)->GetPet(0)->GetAura(i)->GetDuration()));
			//Catch any exceptions and report them.
			if (component->status() != QQmlComponent::Ready)
				emit OutputToGUI(component->errorString());
		}

		//Begin move selection process.
		desiredMove = SelectAction(stageNode, depth, alpha, beta, turnIndex);
		delete stageNode;
		return desiredMove;
	}
	//Opponent selects action.
	else if (turnIndex == 2)
	{
		//Begin move selection process.
		desiredMove = SelectAction(stageNode, depth, alpha, beta, turnIndex);
		delete stageNode;
		return desiredMove;
	}
	//It's time to actually determine what happens when both players have selected a move.
	else	//turnIndex == 0;
	{
		//Determine who goes first.
		quint8 teamIndex = CalculatePriority(stageNode);

		float heuristic = 0.00;

		//In the case that there is a tie for speed, split the value in half and weigh each outcome.
		if (teamIndex == 3)
		{
			heuristic += 0.5 * ActionOutcomes(stageNode, depth, alpha, beta, 1, true);
			heuristic += 0.5 * ActionOutcomes(stageNode, depth, alpha, beta, 2, true);
		}
		//We know who's going first already; use that team.
		else
			heuristic = ActionOutcomes(stageNode, depth, alpha, beta, teamIndex, true);

		desiredMove.SetHeuristic(heuristic);
		delete stageNode;
		return desiredMove;
	}
}

//Selects the action that the pet/team will use.
Move AI::SelectAction(PetStage *stageNode, quint8 depth, float alpha, float beta, quint8 turnIndex)
{
	//Apply aura effects that take place at the start of the turn.
	for (quint8 i=0; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
		for (quint8 j=1; j < stageNode->GetTeam(turnIndex)->GetPet(i)->GetNumAuras()+1; j+=1)
		{
			objectContext->setContextProperty("petStage", stageNode);	
			component->loadUrl(QUrl::fromLocalFile("Scripts/" + QString::number(stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetAuraId()) + ".qml"));
			//Catch any exceptions and report them.
			if (component->status() != QQmlComponent::Ready)
				emit OutputToGUI(component->errorString());
			object = component->create(objectContext);
			//Call ApplyAuraStart; paramters are TeamNumber, PetNumber, AuraIndex and AuraDuration.
			QMetaObject::invokeMethod(object, "applyAuraStart", Q_ARG(QVariant, turnIndex), Q_ARG(QVariant, i), Q_ARG(QVariant, j),
										Q_ARG(QVariant, stageNode->GetTeam(turnIndex)->GetPet(i)->GetAura(j)->GetDuration()));
			//Catch any exceptions and report them.
			if (component->status() != QQmlComponent::Ready)
				emit OutputToGUI(component->errorString());
		}

	//Add all available actions to the list.
	QList<PetStage*> stageMoves;
	QList<Move> nextMoves;

	//Check of the pet is dead.
    if (stageNode->GetTeam(turnIndex)->GetActivePet()->IsDead())
	{
		//Swap to each pet that is still able to battle.
		for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
			//Ignore same index an dead pets.
			if (stageNode->GetTeam(turnIndex)->GetActivePetIndex() != i && !stageNode->GetTeam(turnIndex)->GetPet(i)->IsDead())
			{
				//Copy the node and add it to the list.
				PetStage *actionNode = new PetStage(*stageNode);
				actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
				actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);
				actionNode->GetTeam(turnIndex)->SetActivePet(i);
				stageMoves.append(actionNode);

				//Set the action and add the move to the list.
				Move nextMove;
				nextMove.SetAction((PetAction::Action)(i+3));
				nextMoves.append(nextMove);
			}
	}
	//If an action is already in progress, continue to use that action.
	else if (stageNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->GetRoundsRemaining() > 0)
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
		if (this->CanAttack(stageNode->GetTeam(turnIndex)->GetActivePet()))
			for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetActivePet()->GetNumAbilities()+1; i+=1)
				//Use the ability if it is off cooldown.
				if (stageNode->GetTeam(turnIndex)->GetActivePet()->GetAbility(i)->GetCooldown() == 0)
				{
					//Copy the node and add it to the list.
					PetStage *actionNode = new PetStage(*stageNode);
					actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction((PetAction::Action)i);
					stageMoves.append(actionNode);

					//Set the action and add the move to the list.
					Move nextMove;
					nextMove.SetAction((PetAction::Action)i);
					nextMoves.append(nextMove);

					//"Pre-use" the ability to determine it's priority later.
					objectContext->setContextProperty("petStage", actionNode);	
					component->loadUrl(QUrl::fromLocalFile("Scripts/" + QString::number(actionNode->GetTeam(turnIndex)->GetActivePet()->GetAbility(i)->GetAbilityId()) + ".qml"));
					//Catch any exceptions and report them.
					if (component->status() != QQmlComponent::Ready)
						emit OutputToGUI(component->errorString());
					object = component->create(objectContext);
					//Call PreUseAbility; paramters are TeamNumber. This is used to make the move tell us it's priority.
					QMetaObject::invokeMethod(object, "preUseAbility", Q_ARG(QVariant, turnIndex));
					//Catch any exceptions and report them.
					if (component->status() != QQmlComponent::Ready)
						emit OutputToGUI(component->errorString());
				}
		
		//Check to see if swapping a pet is possible.
		if (this->CanSwap(stageNode, turnIndex))
			//Swap to each pet that is still able to battle.
			for (quint8 i=1; i < stageNode->GetTeam(turnIndex)->GetNumPets()+1; i+=1)
				//Ignore same index and dead pets.
				if (stageNode->GetTeam(turnIndex)->GetActivePetIndex() != i && !stageNode->GetTeam(turnIndex)->GetPet(i)->IsDead())
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

		//If passing is enabled, add it to the list of possible moves.
		if (this->canPass || (stageMoves.isEmpty() && nextMoves.isEmpty()))
		{
			PetStage *actionNode = new PetStage(*stageNode);
			actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::Pass);
			actionNode->GetTeam(turnIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(1);
			stageMoves.append(actionNode);

			//Set the action and add the move to the list.
			Move nextMove;
			nextMove.SetAction(PetAction::Pass);
			nextMoves.append(nextMove);
		}
	}
	
	QList<Move>::iterator iter = nextMoves.begin();											//Used to set the action for each move.
	Move desiredMove, tempMove;																//Used to store the desired and temp move.

	//For each stage.
	while (!stageMoves.isEmpty())
	{
		PetStage *nextStage = stageMoves.takeFirst();										//Remove the stageMove from the list.
		//TODO: Determine if pet died and handle the scenario.
		Move currentMove = Expectiminimax(nextStage, depth, alpha, beta,
			(stageNode->GetTeam(turnIndex)->GetActivePet()->IsDead()
			&& !stageNode->GetTeam(turnIndex)->IsTeamDead()) ? 1 : (turnIndex+1)%3);		//Set currentMove to call our Expectiminimax again.
		(*iter).SetHeuristic(currentMove.GetHeuristic());									//Set the heuristic of the move in the nextMoves list.
		delete (nextStage);																	//Delete the stageMove we removed from the list earlier.

		//If the current heuristic is less than the alpha.
		if ((turnIndex == 1 && (*iter).GetHeuristic() > beta)
			|| (turnIndex == 2 && (*iter).GetHeuristic() < alpha))
		{
			//Remove the moves not explored.
			while (nextMoves.last().GetAction() != (*iter).GetAction())
			{
				nextMoves.removeLast();														//Remove excess move.
				delete stageMoves.takeLast();												//Remove excess stage.
			}

			break;																
		}
		else
			if (turnIndex == 1)
				beta = (*iter).GetHeuristic();												//Set new beta.
			else
				alpha = (*iter).GetHeuristic();												//Set new alpha.

		++iter;																				//Increment the iterator to the next index of nextMoves.
	}

	//Take first move as desired move initially.
	//if (!nextMoves.isEmpty())
		desiredMove = nextMoves.takeFirst();

	//Find the best move for opponent.
	while (!nextMoves.isEmpty())
	{
		tempMove = nextMoves.takeFirst();
		if (turnIndex == 1 && tempMove.GetHeuristic() > desiredMove.GetHeuristic()
				|| (turnIndex == 2 &&tempMove.GetHeuristic() < desiredMove.GetHeuristic()))
			desiredMove = tempMove;
	}

	//Empty stageMoves QList.
	stageMoves.clear();

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
		return 1;
	else if (stageNode->GetTeam(1)->GetActivePet()->GetSpeed() < stageNode->GetTeam(2)->GetActivePet()->GetSpeed())
		return 2;
	else
		return (tieBreaker) ? 3 : ((qrand() % 2) + 1);		//If no tie breaking randomize it.
}

//Uses the first action during round playback. Note: Actions as a result of death happen in scripts but real deaths happen here.
float AI::ActionOutcomes(PetStage *stageNode, quint8 depth, float alpha, float beta, quint8 teamIndex, bool firstCall)
{
	float heuristic = 0.00;									//Used for holding heuristic.
	PetStage *currentStage = new PetStage(*stageNode);		//Clone the stage.

	//Normal ability usage.
	if (currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction() > 0
			&& currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction() < 4)
	{
		//Put the ability on cooldown.
		currentStage->GetTeam(teamIndex)->GetActivePet()->GetAbility(currentStage->GetTeam(teamIndex)
			->GetActivePet()->GetCurrentAction()->GetAction())->UseAbility();

		//Set the number of rounds the ability will persist for.
		currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(
			currentStage->GetTeam(teamIndex)->GetActivePet()->GetAbility(currentStage->GetTeam(teamIndex)
			->GetActivePet()->GetCurrentAction()->GetAction())->GetRounds());

		//Set variables to be used.
		quint16 abilityId = currentStage->GetTeam(teamIndex)->GetActivePet()->GetAbility(currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction())->GetAbilityId();
		float avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating;
		QVariant variantAccuracyRating, variantCriticalRating, variantChanceOnHitRating;

		//Set script.
		objectContext->setContextProperty("petStage", currentStage);
		component->loadUrl(QUrl::fromLocalFile("Scripts/" + QString::number(abilityId) + ".qml"));
		//Catch any exceptions and report them.
		if (component->status() != QQmlComponent::Ready)
			emit OutputToGUI(component->errorString());
		object = component->create(objectContext);

		//Set QVariants based on script info.
		QMetaObject::invokeMethod(object, "getAccuracyRating", Q_RETURN_ARG(QVariant, variantAccuracyRating), Q_ARG(QVariant, teamIndex));
		QMetaObject::invokeMethod(object, "getCriticalRating", Q_RETURN_ARG(QVariant, variantCriticalRating), Q_ARG(QVariant, teamIndex));
		QMetaObject::invokeMethod(object, "getChanceOnHitRating", Q_RETURN_ARG(QVariant, variantChanceOnHitRating), Q_ARG(QVariant, teamIndex));

		//Catch any exceptions and report them.
		if (component->status() != QQmlComponent::Ready)
			emit OutputToGUI(component->errorString());

		//Set ratings based on pet info and QVariants.
		avoidanceRating = currentStage->GetTeam((teamIndex%2)+1)->GetActivePet()->GetAvoidanceRating();
		avoidanceRating = (avoidanceRating > 1) ? 1 : avoidanceRating;
		accuracyRating = variantAccuracyRating.toFloat() + currentStage->GetTeam(teamIndex)->GetActivePet()->GetAccuracyOffset();
		accuracyRating = (accuracyRating > 1) ? 1 : accuracyRating;
		accuracyRating = (accuracyRating < 0) ? 0 : accuracyRating;
		criticalRating = variantCriticalRating.toFloat() + currentStage->GetTeam(teamIndex)->GetActivePet()->GetCriticalStrikeRating();
		criticalRating = (criticalRating > 1) ? 1 : criticalRating;
		criticalRating = (criticalRating < 0) ? 0 : criticalRating;
		chanceOnHitRating = variantChanceOnHitRating.toFloat();

		//Check current team's opponent's pet's avoidance rating and if it is in between 0 and 1.
		//This is important as guaranteed dodge or none will not affect the move outcome in later steps.
		if (avoidanceRating > minAvoidanceThreshold && avoidanceRating < maxAvoidanceThreshold)
		{
			//Determine if ability can miss.
			if (accuracyRating > minHitThreshold && accuracyRating < maxHitThreshold)
			{
				//Determine if the ability can crit.
				if (criticalRating > minCritThreshold && criticalRating < maxCritThreshold)
				{
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//16 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating, true, true, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, criticalRating, 1-chanceOnHitRating, true, true, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, chanceOnHitRating, true, true, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, true, true, false, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, chanceOnHitRating, true, false, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, true, false, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, true, false, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, true, false, false, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, chanceOnHitRating, false, true, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, 1-chanceOnHitRating, false, true, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, chanceOnHitRating, false, true, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, false, true, false, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, chanceOnHitRating, false, false, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, false, false, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, false, false, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, false, false, false, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, criticalRating, 1.00, true, true, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1-criticalRating, 1.00, true, true, false, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, criticalRating, 1.00, true, false, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1-criticalRating, 1.00, true, false, false, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, criticalRating, 1.00, false, true, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1-criticalRating, 1.00, false, true, false, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, criticalRating, 1.00, false, false, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1-criticalRating, 1.00, false, false, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{	
					bool isCritting = (criticalRating <= minCritThreshold) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1.00, chanceOnHitRating, true, true, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1.00, 1-chanceOnHitRating, true, true, isCritting, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1.00, chanceOnHitRating, true, false, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1.00, 1-chanceOnHitRating, true, false, isCritting, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1.00, chanceOnHitRating, false, true, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1.00, 1-chanceOnHitRating, false, true, isCritting, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, chanceOnHitRating, false, false, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, 1-chanceOnHitRating, false, false, isCritting, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, accuracyRating, 1.00, 1.00, true, true, isCritting, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1-accuracyRating, 1.00, 1.00, true, false, isCritting, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, accuracyRating, 1.00, 1.00, false, true, isCritting, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1-accuracyRating, 1.00, 1.00, false, false, isCritting, isProcing);
					}
				}
			}
			else	//We are going to hit no matter what or not at all.
			{
				bool isHitting = (accuracyRating <= minHitThreshold) ? false : true;

				//Determine if the ability can crit.
				if (criticalRating > minCritThreshold && criticalRating < maxCritThreshold)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, criticalRating, chanceOnHitRating, true, isHitting, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, criticalRating, 1-chanceOnHitRating, true, isHitting, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1-criticalRating, chanceOnHitRating, true, isHitting, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1-criticalRating, 1-chanceOnHitRating, true, isHitting, false, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, criticalRating, chanceOnHitRating, false, isHitting, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, criticalRating, 1-chanceOnHitRating, false, isHitting, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, chanceOnHitRating, false, isHitting, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, 1-chanceOnHitRating, false, isHitting, false, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, criticalRating, 1.00, true, isHitting, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1-criticalRating, 1.00, true, isHitting, false, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, criticalRating, 1.00, false, isHitting, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1-criticalRating, 1.00, false, isHitting, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{
					bool isCritting = (criticalRating <= minCritThreshold) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1.00, chanceOnHitRating, true, isHitting, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1.00, 1-chanceOnHitRating, true, isHitting, isCritting, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1.00, chanceOnHitRating, false, isHitting, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1.00, 1-chanceOnHitRating, false, isHitting, isCritting, false);
					}
					else	//Proc is either guaranteed or simply doesn't have one.
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, avoidanceRating, 1.00, 1.00, 1.00, true, isHitting, isCritting, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1-avoidanceRating, 1.00, 1.00, 1.00, false, isHitting, isCritting, isProcing);
					}
				}
			}
		}
		else	//We are either avoiding or not avoiding.
		{
			bool isAvoiding = (avoidanceRating <= minAvoidanceThreshold) ? false : true;

			//Determine if ability can miss.
			if (accuracyRating > minHitThreshold && accuracyRating < maxHitThreshold)
			{
				//Determine if the ability can crit.
				if (criticalRating > minCritThreshold && criticalRating < maxCritThreshold)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//8 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, criticalRating, chanceOnHitRating, isAvoiding, true, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, criticalRating, 1-chanceOnHitRating, isAvoiding, true, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1-criticalRating, chanceOnHitRating, isAvoiding, true, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, true, false, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, criticalRating, chanceOnHitRating, isAvoiding, false, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, criticalRating, 1-chanceOnHitRating, isAvoiding, false, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, chanceOnHitRating, isAvoiding, false, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, false, false, false);
					}
					else
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, criticalRating, 1.00, isAvoiding, true, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1-criticalRating, 1.00, isAvoiding, true, false, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, criticalRating, 1.00, isAvoiding, false, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1-criticalRating, 1.00, isAvoiding, false, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{	
					bool isCritting = (criticalRating <= minCritThreshold) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1.00, chanceOnHitRating, isAvoiding, true, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1.00, 1-chanceOnHitRating, isAvoiding, true, isCritting, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1.00, chanceOnHitRating, isAvoiding, false, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1.00, 1-chanceOnHitRating, isAvoiding, false, isCritting, false);
					}
					else
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, accuracyRating, 1.00, 1.00, isAvoiding, true, isCritting, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1-accuracyRating, 1.00, 1.00, isAvoiding, false, isCritting, isProcing);
					}
				}
			}
			else	//We are going to hit no matter what or not at all.
			{
				bool isHitting = (accuracyRating <= minHitThreshold) ? false : true;
				//Determine if the ability can crit.
				if (criticalRating > minCritThreshold && criticalRating < maxCritThreshold)
				{	
					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{	//4 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, criticalRating, chanceOnHitRating, isAvoiding, isHitting, true, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, criticalRating, 1-chanceOnHitRating, isAvoiding, isHitting, true, false);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1-criticalRating, chanceOnHitRating, isAvoiding, isHitting, false, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1-criticalRating, 1-chanceOnHitRating, isAvoiding, isHitting, false, false);
					}
					else
					{	//2 possible outcomes, does (not) avoid, does (not) hit, does (not) crit, chance on hit does (not) proc.
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, criticalRating, 1.00, isAvoiding, isHitting, true, isProcing);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1-criticalRating, 1.00, isAvoiding, isHitting, false, isProcing);
					}
				}
				else	//Ability is either guaranteed to crit or not crit at all.
				{
					bool isCritting = (criticalRating <= minCritThreshold) ? false : true;

					//Determine if ability has a chance on hit ability that can proc.
					if (chanceOnHitRating > minChanceOnHitThreshold && chanceOnHitRating < maxChanceOnHitThreshold)
					{
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1.00, chanceOnHitRating, isAvoiding, isHitting, isCritting, true);
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1.00, 1-chanceOnHitRating, isAvoiding, isHitting, isCritting, false);
					}
					else
					{
						bool isProcing = (chanceOnHitRating <= minChanceOnHitThreshold) ? false : true;
						heuristic += UseAction(currentStage, depth, alpha, beta, teamIndex, firstCall, 1.00, 1.00, 1.00, 1.00, isAvoiding, isHitting, isCritting, chanceOnHitRating);
					}
				}
			}
		}
	}
	//Pet swap occuring.
	else if (currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction() > 3
			&& currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction() < 7)		
	{
		quint8 tempAction = currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction() - 3;

		//Empty the pet's current action.
		currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
		currentStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);

		//Change to the designated pet.
		currentStage->GetTeam(teamIndex)->SetActivePet(tempAction);

		//Call other teams move or end turn.
		if (firstCall)
			heuristic += ActionOutcomes(currentStage, depth, alpha, beta, (teamIndex%2)+1, !firstCall);
		else
			heuristic += EndTurn(currentStage, depth, alpha, beta);
	}
	//We are either passing or do not have a move.
	else
	{
		//Call other teams move or end turn.
		if (firstCall)
			heuristic += ActionOutcomes(currentStage, depth, alpha, beta, (teamIndex%2)+1, !firstCall);
		else
			heuristic += EndTurn(currentStage, depth, alpha, beta);
	}

	delete currentStage;	//Clean up.

	return heuristic;		//Return the value.
}

//Uses action given certain conditions.
float AI::UseAction(PetStage* stageNode, quint8 depth, float alpha, float beta, quint8 teamIndex, bool firstCall,
						 float avoidanceRating, float hitRating, float critRating, float chanceOnHitRating,
						 bool isAvoiding, bool isHitting, bool isCritting, bool isProcing)
{
	float heuristic = 0.00;		//Used for holding heuristic.

	QVariant variantNumHits;	//Used for acquiring the number of hits.
	quint8 numHits;				//Number of hits.

	PetStage *outcome = new PetStage(*stageNode);
	objectContext->setContextProperty("petStage", outcome);
	object = component->create(objectContext);
	//Parameters are teamIndex, priority, isAvoiding, isHitting, isCritting and isPrcoing.
	QMetaObject::invokeMethod(object, "useAbility", Q_RETURN_ARG(QVariant, variantNumHits), Q_ARG(QVariant, teamIndex), Q_ARG(QVariant, (-1)
								* (outcome->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetRoundsRemaining() - outcome->GetTeam(teamIndex)
								->GetActivePet()->GetAbility(outcome->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->GetAction())->GetRounds()) + 1),
								Q_ARG(QVariant, firstCall), Q_ARG(QVariant, isAvoiding), Q_ARG(QVariant, isHitting), Q_ARG(QVariant, isCritting), Q_ARG(QVariant, isProcing));
	//Catch any exceptions and report them.
	if (component->status() != QQmlComponent::Ready)
		emit OutputToGUI(component->errorString());

	//Convert QVariant for number of hits.
	numHits = variantNumHits.toFloat();

	//Check to see if an active pet is dead.
	QList<PetStage*> possibleStages, tempStages;
	tempStages = IsPetDead(outcome, 1);						//Get the possible outcomes if a pet has died.
	float possibleStagesSize;
	
	//Process each possible outcome of if our team's active pet died and check if the opponent's team has a dead active pet as well.
	while (!tempStages.isEmpty())
	{
		//Take the first stage in the list.
		PetStage *curTempStage = tempStages.takeFirst();

		//Check to see if both pets have died and both teams possible outcomes.
		possibleStages.append(IsPetDead(curTempStage, 2));

		//Delete the stage after it's been used.
		delete curTempStage;
	}

	tempStages.clear();		//Clear the list.

	//Process each possible stage.
	possibleStagesSize = possibleStages.size();
	while (!possibleStages.isEmpty())
	{
		//Take the first stage in the list.
		PetStage *curPossibleStage = possibleStages.takeFirst();

		//If it is the first time this function was called we must still process the other team's action.
		if (firstCall)
			//If there is more than one option divide by the size.
			heuristic += avoidanceRating * hitRating * critRating * ActionOutcomes(curPossibleStage, depth, alpha, beta, (teamIndex%2)+1, false) / possibleStagesSize;
		else
			heuristic += avoidanceRating * hitRating * critRating * EndTurn(curPossibleStage, depth, alpha, beta) / possibleStagesSize;

		//Delete the stage after it's been used.
		delete curPossibleStage;
	}

	possibleStages.clear();		//Clear the list.
					
	delete outcome;				//Delete the base stage.

	return heuristic;			//Return the value.
}

//Apply auras at the end of the turn.
float AI::EndTurn(PetStage* stageNode, quint8 depth, float alpha, float beta)
{
	Move nextTurn;						//Used calling Expectiminimax.
	float heuristic = 0.00;				//What will be returned.
	QList<PetStage*> substituteStages;	//Used for when the pet dies and we have other options.

	for (quint8 i=0; i < 3; i+=1)															//For each team...
		for (quint8 j=0; j < stageNode->GetTeam(i)->GetNumPets()+1; j+=1)					//For each pet...
			for (quint8 k=1; k < stageNode->GetTeam(i)->GetPet(j)->GetNumAuras()+1; k+=1)	//For each aura...
			{
				objectContext->setContextProperty("petStage", stageNode);	
				component->loadUrl(QUrl::fromLocalFile("Scripts/" + QString::number(stageNode->GetTeam(i)->GetPet(j)->GetAura(k)->GetAuraId()) + ".qml"));
				//Catch any exceptions and report them.
				if (component->status() != QQmlComponent::Ready)
					emit OutputToGUI(component->errorString());
				object = component->create(objectContext);
				//Call ApplyAuraEnd; paramters are TeamNumber, PetNumber and AuraDuration.
				QMetaObject::invokeMethod(object, "applyAuraEnd", Q_ARG(QVariant, i), Q_ARG(QVariant, j), Q_ARG(QVariant, k),
					Q_ARG(QVariant, stageNode->GetTeam(i)->GetPet(j)->GetAura(k)->GetDuration()));
				//Catch any exceptions and report them.
				if (component->status() != QQmlComponent::Ready)
					emit OutputToGUI(component->errorString());
			}

	//Check to see if an active pet is dead.
	QList<PetStage*> possibleStages, tempStages;
	tempStages = IsPetDead(stageNode, 1);						//Get the possible outcomes if a pet has died.
	float possibleStagesSize;
	
	//Process each possible outcome of if our team's active pet died and check if the opponent's team has a dead active pet as well.
	while (!tempStages.isEmpty())
	{
		//Take the first stage in the list.
		PetStage *curTempStage = tempStages.takeFirst();

		//Check to see if both pets have died and both teams possible outcomes.
		possibleStages.append(IsPetDead(curTempStage, 2));

		//Delete the stage after it's been used.
		delete curTempStage;
	}

	tempStages.clear();		//Clear the list.

	//Process each possible stage.
	possibleStagesSize = possibleStages.size();
	while (!possibleStages.isEmpty())
	{
		//Take the first stage in the list.
		PetStage *curPossibleStage = possibleStages.takeFirst();

		//Update the round.
		curPossibleStage->RoundUpdate();

		//Call Expectiminimax again, reduce depth by 1 as we are proceeding into the next turn.
		nextTurn = Expectiminimax(curPossibleStage, depth-1, alpha, beta, 1);

		//Add results to heuristic divided by the size of the list.
		heuristic += nextTurn.GetHeuristic() / possibleStagesSize;

		//Delete the stage after it's been used.
		delete curPossibleStage;
	}

	possibleStages.clear();		//Clear the list.

	//Return heuristic.
	return heuristic;
}

//Returns whether or not the pet can attack.
bool AI::CanAttack(Pet* currentPet)
{
	//Pet is asleep, can't attack.
	if (currentPet->HasStatus(Pet::Asleep))
		return false;
	//Pet is Polymorphed, can't attack.
	else if (currentPet->HasStatus(Pet::Polymorphed))
		return false;
	//Pet is Stunned can't attack.
	else if (currentPet->HasStatus(Pet::Stunned))
		return false;
	//Pet can attack.
	else
		return true;
}

//Returns whether or not the pet can swap out.
bool AI::CanSwap(PetStage *stageNode, quint8 teamIndex)
{
	//If the pet is rooted, it can't swap out.
	if (stageNode->GetTeam(teamIndex)->GetActivePet()->HasStatus(Pet::Rooted))
		return false;
	//If the it is not a PvP match, the opponent will never swap.
	else if (teamIndex == 2 && !stageNode->IsPvPBattle())
		return false;
	else
		return true;
}

//Determine if a pet is dead and the possible options that go with that result.
QList<PetStage*> AI::IsPetDead(PetStage *stageNode, quint8 teamIndex)
{
	QList<PetStage*> possibleStages;

	//If the pet died find possible outcomes.
	if (stageNode->GetTeam(teamIndex)->GetActivePet()->IsDead())
	{
		//Pet is dead, remove its current action.
		stageNode->GetTeam(teamIndex)->GetActivePet()->RemoveAuras();
		stageNode->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
		stageNode->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);

		//Attempt to find a new pet to substitute if the team is not dead.
		if (!stageNode->GetTeam(teamIndex)->IsTeamDead())
		{
			//Find a pet that is alive.
			for (quint8 i=1; i < stageNode->GetTeam(teamIndex)->GetNumPets()+1; i+=1)
				if (!stageNode->GetTeam(teamIndex)->GetPet(i)->IsDead())
				{
					PetStage *outcomeStage = new PetStage(*stageNode);
					outcomeStage->GetTeam(teamIndex)->SetActivePet(i);
					outcomeStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetAction(PetAction::None);
					outcomeStage->GetTeam(teamIndex)->GetActivePet()->GetCurrentAction()->SetRoundsRemaining(0);

					//Pet swap has occured; Use Minefield, etc..
					for (quint8 j=1; j < outcomeStage->GetTeam(teamIndex)->GetPet(0)->GetNumAuras()+1; j+=1)
						if (outcomeStage->GetTeam(teamIndex)->GetPet(0)->GetAura(j)->OnSwapIn())
						{
							QMetaObject::invokeMethod(object, "applyAura", Q_ARG(QVariant, teamIndex));					//Use the aura; parameters are teamIndex.
							//Catch any exceptions and report them.
							if (component->status() != QQmlComponent::Ready)
								emit OutputToGUI(component->errorString());
							outcomeStage->GetTeam(teamIndex)->GetPet(0)->RemoveAura(j);									//Remove the aura.
							break;																						//There should not be more than 1.
						}
					possibleStages.append(outcomeStage);																//Append the substitute stage to the QList.

					//If it's not a PvP Battle, the opponent simply moves on to the next available pet.
					if (!outcomeStage->IsPvPBattle())
						break;
				}
		}
	}
	else
		possibleStages.append(new PetStage(*stageNode));

	//TODO: Consider expanding this function to be recursive.

	//Return the list of possible outcomes.
	return possibleStages;
}