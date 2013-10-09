#ifndef PETSTAGE_H
#define PETSTAGE_H

#include <QVector>
#include <QtAlgorithms>

#include "PetTeam.h"

class PetStage
{
public:
	PetStage(void);
	~PetStage(void);
	PetStage(const PetStage&);

	PetTeam* GetTeam(int);

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

	int QueueState();
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

private:
	int queueState;
	bool inPetBattle, teamIsAlive, queueEnabled, canAccept;
	bool playerIsGhost, playerIsDead, playerAffectingCombat;
	bool initialized, selectPet, selectAbility, wonLastBattle;
	QVector<PetTeam*> petTeam;
};

#endif