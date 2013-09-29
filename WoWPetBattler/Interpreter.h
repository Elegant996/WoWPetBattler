#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QElapsedTimer>
#include <QWaitCondition>
#include <QDebug> //To be removed.
#include <QThread> //To be removed.
#include <Robot.h>
#include "PetStage.h"

class Interpreter :
	public QObject
{
    Q_OBJECT

public:
	//
    explicit Interpreter(QObject *parent = 0);
	Interpreter(PetStage*, Robot::Window*);
	~Interpreter();
    //bool IsWorkRunning();

signals:
	void OutputToGUI(QString, QString);
	void StopTimeout(QString);

public slots:
	void Start();
	void Stop();

private slots:
	void Interpret();
	void Testing();

private:
	bool Locate();

	const int BUILD;
    volatile bool running; //, stopped;

    QMutex mutex;
	QElapsedTimer timer;
    QWaitCondition waitCondition;

	Robot::Window *window;
	Robot::Image *image;
	Robot::Point *points;
	Robot::Color *pixels;

	Robot::Bounds addonBar1, addonBar2;

	bool readSuccess, oneTimeNotifier;
	int timeoutCount;

	PetStage *petStage;
};

#endif
