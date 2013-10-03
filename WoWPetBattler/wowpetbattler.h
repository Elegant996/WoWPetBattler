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
#include "AI.h"

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

	Robot::Window GUIWindow, WoWWindow;
	Robot::Process process;

	PetStage *petStage;

	Interpreter *interpreter;
	QThread *interpreterThread;

	AI *ai;
	QThread *aiThread;
};

#endif // WOWPETBATTLER_H
