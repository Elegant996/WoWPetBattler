#ifndef PETSTAGE_H
#define PETSTAGE_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QtAlgorithms>

#include "PetTeam.h"

class PetStage : public QObject
{
	Q_OBJECT
	//Q_PROPERTY(QQmlListProperty<PetTeam> Teams READ GetTeams)

public:
	PetStage(void);
	~PetStage(void);
	PetStage(const PetStage&);

	void Reinitialize();
	void RoundUpdate();

	Q_INVOKABLE PetTeam* GetTeam(int);
	//QQmlListProperty<PetTeam> GetTeams();

	void QueueState(int);
	void InPetBattle(bool);
	void TeamIsAlive(bool);
	void QueueEnabled(bool);
	void CanAccept(bool);
	void PlayerIsGhost(bool);
	void PlayerIsDead(bool);
	void PlayerAffectingCombat(bool);
	void Initialized(bool);
	void SelectPet(bool);
	void SelectAbility(bool);
	void WonLastBattle(bool);
	void IsPvPBattle(bool);

	qint8 QueueState();
	bool InPetBattle();
	bool TeamIsAlive();
	bool QueueEnabled();
	bool CanAccept();
	bool PlayerIsGhost();
	bool PlayerIsDead();
	bool PlayerAffectingCombat();
	bool Initialized();
	bool SelectPet();
	bool SelectAbility();
	bool WonLastBattle();
	bool IsPvPBattle();

private:
	const PetStage *parentStage;
	qint8 queueState;
	bool inPetBattle, teamIsAlive, queueEnabled, canAccept;
	bool playerIsGhost, playerIsDead, playerAffectingCombat;
	bool initialized, selectPet, selectAbility, wonLastBattle;
	bool isPvPBattle;
	QList<PetTeam*> petTeams;
};

#endif