#include "wowpetbattler.h"

//Constructor
WoWPetBattler::WoWPetBattler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(this, SIGNAL(StopApp(QString)), this, SLOT(Stop(QString)));

	this->petStage = new PetStage();

	this->interpreter = new Interpreter(petStage, &WoWWindow);
	connect(interpreter, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(interpreter, SIGNAL(Stop(QString)), this, SLOT(Stop(QString)));
	connect(this, SIGNAL(StartInterpreter()), interpreter, SLOT(Start()));
	connect(this, SIGNAL(StopInterpreter()), interpreter, SLOT(Stop()));

	this->ai = new AI(petStage, &WoWWindow);
	connect(ai, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(interpreter, SIGNAL(RunAI()), ai, SLOT(Run()));

	interpreterThread = new QThread();
	connect(this, SIGNAL(destroyed()), interpreter, SLOT(deleteLater()));					//Delete the interpreter object if this object is destroyed.
	connect(interpreter, SIGNAL(destroyed()), interpreterThread, SLOT(quit()));				//Stop the thread whenever it is destroyed.
	connect(interpreterThread, SIGNAL(finished()), interpreterThread, SLOT(deleteLater()));	//Clean up the thread.
	interpreter->moveToThread(interpreterThread);
	interpreterThread->start();

	aiThread = new QThread();
	connect(this, SIGNAL(destroyed()), ai, SLOT(deleteLater()));			//Delete the ai object if this object is destroyed.
	connect(ai, SIGNAL(destroyed()), aiThread, SLOT(quit()));				//Stop the thread whenever it is destroyed.
	connect(aiThread, SIGNAL(finished()), aiThread, SLOT(deleteLater()));	//Clean up the thread.
	ai->moveToThread(aiThread);
	aiThread->start();
}

//Destructor
WoWPetBattler::~WoWPetBattler()
{
	if (!ui.playButton->isChecked())
		emit StopInterpreter();			//Stop interpreter to re-enable arrow
	aiThread->quit();					//Quit thread.
	aiThread->wait();					//Wait for thread to terminate.
	interpreterThread->quit();			//Quit thread.
	interpreterThread->wait();			//Wait for thread to terminate.
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

	emit StopInterpreter();					//Stop the interpreter.
	GUIWindow.SetTopMost(false);			//Stop the GUI from being the top most window.
}

//Handler for play button.
void WoWPetBattler::on_playButton_clicked()
{
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

		emit StartInterpreter(); //Start screen reading.
	}
	else
		emit StopApp("Stopping..."); //We have clicked the stop button, so let's stop everything.
}