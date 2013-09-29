#include "wowpetbattler.h"

WoWPetBattler::WoWPetBattler(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//window = new Robot::Window();

	petStage = new PetStage();
	interpreter = new Interpreter(petStage, &window);
	QObject::connect(interpreter, SIGNAL(OutputToGUI(QString, QString)), this, SLOT(Output(QString, QString)));
	QObject::connect(this, SIGNAL(StopApp(QString)), this, SLOT(Stop(QString)));
	QObject::connect(interpreter, SIGNAL(StopTimeout(QString)), this, SLOT(Stop(QString)));
	QObject::connect(this, SIGNAL(StartInterpreter()), interpreter, SLOT(Start()));
	QObject::connect(this, SIGNAL(StopInterpreter()), interpreter, SLOT(Stop()));

	interpreterThread = new QThread();
	// delete the interpreter obj whenever this obj is destroyed
	connect( this, SIGNAL(destroyed()), interpreter, SLOT(deleteLater()) );
	// stop the thread whenever the interpreter is destroyed
	connect( interpreter, SIGNAL(destroyed()), interpreterThread, SLOT(quit()) );
	// clean up the thread
	connect( interpreterThread, SIGNAL(finished()), interpreterThread, SLOT(deleteLater()) );
	interpreter->moveToThread( interpreterThread );
	interpreterThread->start();
}

WoWPetBattler::~WoWPetBattler()
{
	if (!ui.playButton->isChecked())
		emit StopInterpreter();			//Stop interpreter to re-enable arrow
	interpreterThread->quit();			//Quit thread.
	interpreterThread->wait();			//Wait for thread to terminate.
}

void WoWPetBattler::Output(QString caption, QString info)
{
	if (!caption.isEmpty())
		ui.statusLabel->setText(caption);
	ui.outputBrowser->append(info);
}

void WoWPetBattler::Stop(QString output)
{
	ui.statusLabel->setText("Stopping");
	ui.outputBrowser->append(output);
	ui.playButton->setChecked(false);

	emit StopInterpreter();
}

void WoWPetBattler::on_playButton_clicked()
{
	if (ui.playButton->isChecked())
	{
		//Find the WoW Process.
		//Multiple copies is not permitted at this time so we'll only the grab the first one we find.
		ui.statusLabel->setText("Finding WoW Process");
		Robot::Window::Find("World of Warcraft", &window, 1);
		process = window.GetProcess();

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

		emit StartInterpreter();
	}
	else
		emit StopApp("Stopping..."); //We have clicked the stop button, so let's stop everything.
}