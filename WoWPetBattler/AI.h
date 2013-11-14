#ifndef AI_H
#define AI_H

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <QtQml>
#include <QObject>
#include <QDebug>
#include <QSettings>

#include <Robot.h>

#include "Move.h"
#include "PetHelper.h"
#include "PetStage.h"

class AI :
	public QObject
{
    Q_OBJECT

public:
	AI(PetStage*, Robot::Window*);
	~AI(void);

	void LoadPreferences();

	void QueueUp();
	void AcceptQueue();

	Move Expectiminimax(PetStage*, quint8, quint8);

signals:
	void OutputToGUI(QString, QString);
	void OutputToGUI(QString);

public slots:
	void Run();

private:
	//Move Expectiminimax(PetStage*, quint8, quint8);
	Move SelectAction(PetStage*, quint8, quint8);
	quint8 CalculatePriority(PetStage*);
	float ActionOutcomes(PetStage*, quint8, quint8, bool);
	float UseAction(PetStage*, quint8, quint8, bool, float, float, float, float, bool, bool, bool, bool);
	float EndTurn(PetStage*, quint8);

	bool CanAttack(Pet*);
	QList<PetStage*> IsPetDead(PetStage*, quint8);

	PetStage *petStage;
	Robot::Window *window;
	Robot::Keyboard keyboard;

	QQmlEngine *engine;
	QQmlContext *objectContext;
	QQmlComponent *component;
	QObject *object;

	float minAvoidanceThreshold, minHitThreshold, minCritThreshold, minChanceOnHitThreshold;
	float maxAvoidanceThreshold, maxHitThreshold, maxCritThreshold, maxChanceOnHitThreshold;

	bool tieBreaker;

	int totalCalls;
};

#endif

