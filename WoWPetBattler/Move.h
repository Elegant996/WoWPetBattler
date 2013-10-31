#ifndef MOVE_H
#define MOVE_H

#include <QDataStream>

#include "PetAction.h"

class Move
{
public:
	Move();
	~Move(void);
	Move(const Move&);

	void SetAction(PetAction::Action);
	void SetHeuristic(float);

	PetAction::Action GetAction();
	float GetHeuristic();

private:
	PetAction::Action action;
	float heuristic;
};

#endif

