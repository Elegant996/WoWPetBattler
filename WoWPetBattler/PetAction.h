#ifndef PETACTION_H
#define PETACTION_H

#include <QObject>

class PetAction : public QObject
{
	Q_OBJECT
	Q_PROPERTY(quint16 AbilityId READ GetAbilityId WRITE SetAbilityId)
	Q_PROPERTY(qint8 RoundsRemaining READ GetRoundsRemaining WRITE SetRoundsRemaining)
public:
	PetAction(quint16, qint8);
	~PetAction(void);
	PetAction(const PetAction&);

	void SetAbilityId(quint16);
	void SetRoundsRemaining(qint8);

	quint16 GetAbilityId();
	qint8 GetRoundsRemaining();

private:
	quint16 abilityId;
	qint8 roundsRemaining;
};

#endif

