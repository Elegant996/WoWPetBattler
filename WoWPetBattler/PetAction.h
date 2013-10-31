#ifndef PETACTION_H
#define PETACTION_H

#include <QObject>

class PetAction : public QObject
{
	Q_OBJECT
	Q_ENUMS(Action)
	Q_PROPERTY(Action Action READ GetAction WRITE SetAction)
	Q_PROPERTY(qint8 RoundsRemaining READ GetRoundsRemaining WRITE SetRoundsRemaining)
public:
	PetAction();
	~PetAction(void);
	PetAction(const PetAction&);

	enum Action { None, Ability1, Ability2, Ability3,
					Pet1, Pet2, Pet3, Pass };

	void RoundUpdate();

	void SetAction(PetAction::Action);
	void SetRoundsRemaining(qint8);

	PetAction::Action GetAction();
	qint8 GetRoundsRemaining();

private:
	Action action;
	qint8 roundsRemaining;
};

#endif

