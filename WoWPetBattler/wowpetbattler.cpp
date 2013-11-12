#include "WoWPetBattler.h"

//Constructor
WoWPetBattler::WoWPetBattler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	if (taskbar.Synchronize())
		move(taskbar.GetBounds().W - size().width() - 15, taskbar.GetBounds().Y - size().height() - 35);

	this->petStage = new PetStage();

	this->interpreter = new Interpreter(petStage, ai, &WoWWindow);
	connect(interpreter, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(interpreter, SIGNAL(OutputToGUI(QString)), this, SLOT(Output("", QString)));
	connect(interpreter, SIGNAL(Stop(QString)), this, SLOT(Stop(QString)));

	this->ai = new AI(petStage);
	this->ai->moveToThread(interpreter);
	connect(ai, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(ai, SIGNAL(OutputToGUI(QString)), this, SLOT(Output("", QString)));

	//Testing data
	petStage->GetTeam(1)->AddPet(1229, 5, 4, 25);
	petStage->GetTeam(1)->GetPet(1)->AddAbility(true, 1, 0);
	petStage->GetTeam(1)->GetPet(1)->AddAbility(true, 1, 0);
	petStage->GetTeam(1)->GetPet(1)->AddAbility(true, 2, 0);

	petStage->GetTeam(1)->AddPet(439, 9, 4, 25);
	petStage->GetTeam(1)->GetPet(2)->AddAbility(true, 1, 0);
	petStage->GetTeam(1)->GetPet(2)->AddAbility(true, 1, 0);
	petStage->GetTeam(1)->GetPet(2)->AddAbility(true, 2, 0);

	petStage->GetTeam(1)->AddPet(519, 7, 4, 25);
	petStage->GetTeam(1)->GetPet(3)->AddAbility(true, 2, 0);
	petStage->GetTeam(1)->GetPet(3)->AddAbility(true, 2, 0);
	petStage->GetTeam(1)->GetPet(3)->AddAbility(true, 1, 0);

	petStage->GetTeam(2)->AddPet(1012, 5, 6, 25);
	petStage->GetTeam(2)->GetPet(1)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(1)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(1)->AddAbility(true, 1, 0);

	petStage->GetTeam(2)->AddPet(1011, 7, 6, 25);
	petStage->GetTeam(2)->GetPet(2)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(2)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(2)->AddAbility(true, 1, 0);

	petStage->GetTeam(2)->AddPet(1010, 8, 6, 25);
	petStage->GetTeam(2)->GetPet(3)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(3)->AddAbility(true, 1, 0);
	petStage->GetTeam(2)->GetPet(3)->AddAbility(true, 1, 0);

	petStage->GetTeam(1)->SetActivePet(1);
	petStage->GetTeam(2)->SetActivePet(1);
}

//Destructor
WoWPetBattler::~WoWPetBattler()
{
	if (interpreter->isRunning())
		interpreter->Exit();

	delete interpreter;
	delete ai;
	delete petStage;
}

//Output to browser.
void WoWPetBattler::Output(QString caption, QString info)
{
	if (!caption.isEmpty())
		ui.statusLabel->setText(caption);
	ui.outputBrowser->append(info);
}

//Stop the bot.
void WoWPetBattler::Stop(QString output)
{
	ui.statusLabel->setText("Stopping");
	ui.outputBrowser->append(output);
	ui.playButton->setChecked(false);

	interpreter->Exit();					//Stop the update thread.

	ui.statusLabel->setText("Not Running");
	ui.outputBrowser->append("Stopped.");

	GUIWindow.SetTopMost(false);			//Stop the GUI from being the top most window.
}

//Handler for play button.
void WoWPetBattler::on_playButton_clicked()
{
	qmlRegisterType<PetStage>();
	qmlRegisterType<PetTeam>();
	qmlRegisterType<PetType>("PetType", 1, 0, "PetType");
	qmlRegisterType<Pet>("PetStatus", 1, 0, "PetStatus");
	qmlRegisterType<PetAction>("PetAction", 1, 0, "PetAction");
	qmlRegisterType<PetAbility>();
	qmlRegisterType<PetAura>();
	qmlRegisterType<PetHelper>("PetHelper", 1, 0, "PetHelper");

	Move testMove;
	testMove = ai->Expectiminimax(petStage, 1, 1);
	qDebug() << "Move: " + QString::number(testMove.GetAction());
	qDebug() << "Heuristic: " + QString::number(testMove.GetHeuristic());

	/*QQmlContext *objectContext = new QQmlContext(engine.rootContext());
	objectContext->setContextProperty("petStage", petStage);	

	QQmlComponent component(&engine, QUrl::fromLocalFile("Scripts/466.qml"));
	QObject *object = component.create(objectContext);

	if (component.status() == 3)
		while (!component.errors().isEmpty())
			qDebug() << component.errors().takeFirst().toString();

	qDebug() << petStage->GetTeam(2)->GetPet(1)->GetHealth();

	QMetaObject::invokeMethod(object, "useAbility", Q_ARG(QVariant, 1), Q_ARG(QVariant, 1), Q_ARG(QVariant, true), Q_ARG(QVariant, false),
								Q_ARG(QVariant, true), Q_ARG(QVariant, false), Q_ARG(QVariant, false));

	qDebug() << petStage->GetTeam(2)->GetPet(1)->GetHealth();

	delete object;

	delete objectContext;*/

	/*	
	if (ui.playButton->isChecked())
	{
		//Make the GUI the top most window while running.
		Robot::Window((Robot::uintptr)winId()).SetTopMost(true);
		GUIWindow.SetTopMost(true);

		//Empty the output browser.
		ui.outputBrowser->setText("");

		//Find the WoW Process.
		//Multiple copies is not permitted at this time so we'll only the grab the first one we find.
		ui.statusLabel->setText("Finding WoW Process");
		Robot::Window::Find("World of Warcraft", &WoWWindow, 1);
		process = WoWWindow.GetProcess();

		//WoW Process could not be located.
		if (process.GetID() == 0)
		{
			ui.statusLabel->setText("Not Running");
			ui.outputBrowser->append("Cannot find WoW process. Check that it is running.");
			ui.playButton->setChecked(false);
			return;
		}

		ui.outputBrowser->append("Found WoW process with ID " + QString::number(process.GetID()) + ".");

		ui.playButton->setChecked(true);
		ui.statusLabel->setText("Starting Interpreter");

		interpreter->start();
		ui.outputBrowser->append("Starting...");
		Robot::Window::SetActive(WoWWindow);
	}
	else
		Stop("Stopping..."); //We have clicked the stop button, so let's stop everything.
	*/
}