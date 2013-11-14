#ifndef WOWPETBATTLER_H
#define WOWPETBATTLER_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QDebug> //To be removed.
#include <QtQml>

#include <Process.h>
#include <Screen.h>
#include <Window.h>

#include "UI_WoWPetBattler.h"
#include "PetStage.h"
#include "Preferences.h"
#include "Interpreter.h"
#include "AI.h"

class WoWPetBattler : public QMainWindow
{
	Q_OBJECT

public:
	WoWPetBattler(QWidget *parent = 0);
	~WoWPetBattler();

	void qDebugMessageHandler(QtMsgType, const QMessageLogContext&, const QString&);

public slots:
	void Output(QString, QString);
	void Output(QString);
	void Stop(QString);

private slots:
	void on_actionPreferences_triggered();
	void on_playButton_clicked();

private:
	Ui::WoWPetBattlerMainWindow ui;
	Preferences *preferences;

	Robot::Taskbar taskbar;
	Robot::Window GUIWindow, WoWWindow;
	Robot::Process process;

	PetStage *petStage;

	Interpreter *interpreter;

	AI *ai;

	QQmlEngine engine;
};

#endif // WOWPETBATTLER_H
