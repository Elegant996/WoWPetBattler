#include "WoWPetBattler.h"

//Constructor
WoWPetBattler::WoWPetBattler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->petStage = new PetStage();

	this->interpreter = new Interpreter(petStage, ai, &WoWWindow);
	connect(interpreter, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(interpreter, SIGNAL(Stop(QString)), this, SLOT(Stop(QString)));

	this->ai = new AI(petStage);
	this->ai->moveToThread(interpreter);
	connect(ai, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
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
}