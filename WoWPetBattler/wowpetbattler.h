#ifndef WOWPETBATTLER_H
#define WOWPETBATTLER_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QDebug> //To be removed.

#include <Process.h>
#include <Screen.h>
#include <Window.h>

#include "UI_WoWPetBattler.h"
#include "PetStage.h"
#include "Interpreter.h"
#include "AI.h"

class WoWPetBattler : public QMainWindow
{
	Q_OBJECT

public:
	WoWPetBattler(QWidget *parent = 0);
	~WoWPetBattler();

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

	AI *ai;
};

#endif // WOWPETBATTLER_H
