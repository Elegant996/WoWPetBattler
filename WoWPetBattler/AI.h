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
	Move Expectiminimax(PetStage*, quint8, quint8);
	Move SelectAction(PetStage*, quint8, quint8);
	quint8 CalculatePriority(PetStage*);
	float ActionOutcomes(PetStage*, quint8, quint8, bool);
	float UseAction(PetStage*, quint8, quint8, bool, float, float, float, float, bool, bool, bool, bool);
	float EndTurn(PetStage*, quint8);

	PetStage *petStage;
	Robot::Keyboard keyboard;

	QQmlEngine *engine;
	QQmlContext *objectContext;
	QQmlComponent *component;
	QObject *object;

	bool tieBreaker;
};

#endif

