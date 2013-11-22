#include "WoWPetBattler.h"

//Constructor
WoWPetBattler::WoWPetBattler(QWidget *parent)
	: QMainWindow(parent)
{
	//Set up the UI.
	this->ui.setupUi(this);

	//Load preferences.
	this->LoadPreferences();

	//Initialize the stage.
	this->petStage = new PetStage();

	//Initialize Preferences.
	this->preferences = new Preferences(this);

	//Initialize AI.
	this->ai = new AI(petStage, &WoWWindow);

	//Initialize Interpreter.
	this->interpreter = new Interpreter(petStage, ai, &WoWWindow);

	//Move AI to Interpreter thread.
	this->ai->moveToThread(interpreter);

	//Setup Debug connection.
	connect(Debug::Instance(), SIGNAL(OutputToGUI(QString)), this, SLOT(Output(QString)));

	//Setup Preferences connections.
	connect(this->preferences, SIGNAL(LoadPreferences()), this, SLOT(LoadPreferences()));

	//Setup AI connections.
	connect(this->ai, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(this->ai, SIGNAL(OutputToGUI(QString)), this, SLOT(Output(QString)));

	//Setup Interpreter connections.
	connect(this->interpreter, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	connect(this->interpreter, SIGNAL(OutputToGUI(QString)), this, SLOT(Output(QString)));
	connect(this->interpreter, SIGNAL(Stop(QString)), this, SLOT(Stop(QString)));

	//Create Ability folder if it does not exist.
	if (!QDir("Ability").exists())
		QDir().mkdir("Ability");

	//Create Species folder if it does not exist.
	if (!QDir("Species").exists())
		QDir().mkdir("Scripts");

	//Create Scripts folder if it does not exist.
	if (!QDir("Scripts").exists())
		QDir().mkdir("Scripts");

	//Create BattleRecords folder if it does not exist.
	if (!QDir("BattleRecords").exists())
		QDir().mkdir("BattleRecords");

	//Create PetRecords folder if it does not exist.
	if (!QDir("PetRecords").exists())
		QDir().mkdir("PetRecords");
}

//Destructor
WoWPetBattler::~WoWPetBattler()
{
	//Save preferences.
	this->SavePreferences();

	//Stop the interpreter if it's running.
	if (this->interpreter->isRunning())
		this->interpreter->Exit();

	//Clean up.
	delete interpreter;
	delete ai;
	delete petStage;
	delete preferences;
}

//Output to browser.
void WoWPetBattler::Output(QString caption, QString info)
{
	if (!caption.isEmpty())
		this->ui.statusLabel->setText(caption);
	this->ui.outputBrowser->append(info);
}

//Output to browser without caption.
void WoWPetBattler::Output(QString info)
{
	this->Output("", info);
}

//Stop the bot.
void WoWPetBattler::Stop(QString output)
{
	this->ui.statusLabel->setText("Stopping");
	this->ui.outputBrowser->append(output);
	this->ui.playButton->setChecked(false);

	this->interpreter->Exit();					//Stop the update thread.

	this->ui.statusLabel->setText("Not Running");
	this->ui.outputBrowser->append("Stopped.");

	this->GUIWindow.SetTopMost(false);			//Stop the GUI from being the top most window.
}

//Load preferences for main window.
void WoWPetBattler::LoadPreferences()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open MainWindow group.
	setting.beginGroup("MainWindow");

	//Fetch size and position of the Preferences GUI.
	this->resize(setting.value("mainWindowSize", QSize(460, 545)).toSize());
	this->move(setting.value("mainWindowPosition", QPoint(this->size().width() / 2, this->size().height() / 2)).toPoint());

	//Close MainWindow group.
	setting.endGroup();

	//Open Options group.
	setting.beginGroup("Options");

	//Fetch Aero preferences.
	this->disableAero = setting.value("DisableAero", true).toBool();

	//Close Options group.
	setting.endGroup();
}

//Handler for opening preferences window.
void WoWPetBattler::on_actionPreferences_triggered()
{
	//Show the window if we're currently not running the program.
	if (!this->ui.playButton->isChecked())
	{
		this->preferences->show();
		this->preferences->activateWindow();
		if (this->preferences->isMinimized())
			this->preferences->showNormal();
	}
	else
		this->ui.outputBrowser->append("Please stop the current session to change preferences.");
}

//Handler for play button.
void WoWPetBattler::on_playButton_clicked()
{		
	if (ui.playButton->isChecked())
	{
		//Disable aero if setting demands it.
		if (this->disableAero)
			Robot::Screen::EnableAero(false);

		//Make the GUI the top most window while running.
		Robot::Window((Robot::uintptr)winId()).SetTopMost(true);
		this->GUIWindow.SetTopMost(true);

		//Empty the output browser.
		this->ui.outputBrowser->setText("");

		//Find the WoW Process.
		//Multiple copies is not permitted at this time so we'll only the grab the first one we find.
		ui.statusLabel->setText("Finding WoW Process");
		Robot::Window::Find("World of Warcraft", &WoWWindow, 1);
		this->process = WoWWindow.GetProcess();

		//WoW Process could not be located.
		if (this->process.GetID() == 0)
		{
			this->ui.statusLabel->setText("Not Running");
			this->ui.outputBrowser->append("Cannot find WoW process. Check that it is running.");
			this->ui.playButton->setChecked(false);
			return;
		}

		this->ui.outputBrowser->append("Found WoW process with ID " + QString::number(process.GetID()) + ".");

		this->ui.playButton->setChecked(true);
		this->ui.statusLabel->setText("Starting Interpreter");

		this->interpreter->start();
		this->ui.outputBrowser->append("Starting...");
		Robot::Window::SetActive(WoWWindow);
	}
	else
	{
		this->Stop("Stopping..."); //We have clicked the stop button, so let's stop everything.

		if (this->disableAero)
			Robot::Screen::EnableAero(true);
	}
}

void WoWPetBattler::SavePreferences()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open MainWindow group.
	setting.beginGroup("MainWindow");

	//Store size and position of the MainWindow GUI.
	setting.setValue("mainWindowSize", this->size());
	setting.setValue("mainWindowPosition", this->pos());

	//Close MainWindow group.
	setting.endGroup();
}