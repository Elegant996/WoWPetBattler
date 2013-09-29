#ifndef WOWPETBATTLER_H
#define WOWPETBATTLER_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QDebug> //To be removed.

#include <Process.h>
#include <Screen.h>
#include <Window.h>

#include "ui_wowpetbattler.h"
#include "PetStage.h"
#include "Interpreter.h"

class WoWPetBattler : public QMainWindow
{
	Q_OBJECT

public:
	WoWPetBattler(QWidget *parent = 0);
	~WoWPetBattler();

signals:
	void StopApp(QString);
	void StartInterpreter();
	void StopInterpreter();

public slots:
	void Output(QString, QString);
	void Stop(QString);

private slots:
	void on_playButton_clicked();

private:
	Ui::WoWPetBattlerClass ui;

	Robot::Window window;
	Robot::Process process;

	PetStage *petStage;

	Interpreter *interpreter;
	QThread *interpreterThread;
};

#endif // WOWPETBATTLER_H
