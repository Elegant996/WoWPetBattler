#ifndef WOWPETBATTLER_H
#define WOWPETBATTLER_H

#include <QtWidgets/QMainWindow>
#include <QThread>
#include <QtQml>

#include <Process.h>
#include <Screen.h>
#include <Window.h>

#include "UI_WoWPetBattler.h"

#include "AI.h"
#include "Debug.h"
#include "Interpreter.h"
#include "PetStage.h"
#include "Preferences.h"
#include "Recorder.h"

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
	void LoadPreferences();
	void on_actionPreferences_triggered();
	void on_playButton_clicked();

private:
	void SavePreferences();

	Ui::WoWPetBattlerMainWindow ui;
	Preferences *preferences;

	Robot::Window GUIWindow, WoWWindow;
	Robot::Process process;

	PetStage *petStage;
	Interpreter *interpreter;
	AI *ai;

	bool disableAero;

	QQmlEngine engine;
};

#endif // WOWPETBATTLER_H
