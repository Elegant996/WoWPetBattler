#ifndef AI_H
#define AI_H

#include <QObject>
#include <QDebug>
#include <Robot.h>
#include "PetStage.h"

class AI :
	public QObject
{
    Q_OBJECT

public:
	AI(PetStage*);
	~AI(void);

signals:
	void OutputToGUI(QString, QString);

public slots:
	void Run();

private:
	PetStage *petStage;
	Robot::Keyboard keyboard;
};

#endif
