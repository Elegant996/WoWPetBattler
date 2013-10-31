#ifndef AI_H
#define AI_H

#include <QtQml>
#include <QObject>
#include <QDebug>

#include <Robot.h>

#include "Move.h"
#include "PetStage.h"

class AI :
	public QObject
{
    Q_OBJECT

public:
	AI(PetStage*);
	~AI(void);

	void QueueUp();
	void AcceptQueue();

signals:
	void OutputToGUI(QString, QString);
	void OutputToGUI(QString);

public slots:
	void Run();

private:
	Move Expectiminimax(PetStage*, int);
	Move temp(PetStage*, int, int);
	quint8 CalculatePriority();

	QQmlEngine *engine;
	QQmlContext *objectContext;
	QQmlComponent *component;
	QObject *object;

	PetStage *petStage;
	Robot::Keyboard keyboard;
};

#endif

