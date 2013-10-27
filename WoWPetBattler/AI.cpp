#include "AI.h"

//Constructor
AI::AI(PetStage *petStage)
{
	qmlRegisterType<PetStage>();
	qmlRegisterType<PetTeam>();
	qmlRegisterType<PetType>("PetType", 1, 0, "PetType");
	qmlRegisterType<Pet>("PetStatus", 1, 0, "PetStatus");
	qmlRegisterType<PetAbility>();
	qmlRegisterType<PetAura>();

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

	return Move(0);
}