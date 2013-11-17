#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
#include <QDebug>

#include <Bounds.h>
#include <Color.h>
#include <Image.h>
#include <Point.h>
#include <Window.h>

#include "AI.h"
#include "PetStage.h"
#include "Recorder.h"

class Interpreter : public QThread
{
	Q_OBJECT

public:
	Interpreter(PetStage*, AI*, Robot::Window*);
	~Interpreter(void);

signals:
	void OutputToGUI(QString, QString);
	void OutputToGUI(QString);
	void RunAI();
	void Stop(QString);

public slots:
	void Exit();

protected:
	void run();

private:
	void LoadPreferences();

	bool Locate();
	void SetupPetTeams();
	void UpdateHealthPools();
	void UpdateAbilities();
	void UpdateAuras();

	volatile bool running, queueEnabled;
	const quint8 build;

	PetStage *petStage;
	AI* ai;
	
	QMutex mutex;
	QElapsedTimer timer;

	Robot::Window *window;
	Robot::Image *image;
	Robot::Point *points;
	Robot::Color *pixels;

	Robot::Bounds addonBar1, addonBar2;

	bool readSuccess, oneTimeNotifier;
	quint8 timeoutCount;

};

#endif
