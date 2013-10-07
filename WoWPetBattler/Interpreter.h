#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QObject>
#include <QThread>
#include <QElapsedTimer>
#include <QDebug>
#include <Robot.h>
#include "PetStage.h"

class Interpreter :
	public QThread
{
	Q_OBJECT

public:
	Interpreter(PetStage*, Robot::Window*);
	~Interpreter(void);

signals:
	void OutputToGUI(QString, QString);
	void RunAI();
	void Stop(QString);

public slots:
	void Exit();

protected:
	void run();

private:
	bool Locate();

	volatile bool running;
	const int BUILD;

	PetStage *petStage;
	
	QMutex mutex;
	QElapsedTimer timer;

	Robot::Window *window;
	Robot::Image *image;
	Robot::Point *points;
	Robot::Color *pixels;

	Robot::Bounds addonBar1, addonBar2;

	bool readSuccess, oneTimeNotifier;
	int timeoutCount;

};

#endif
