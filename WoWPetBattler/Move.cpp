#include "Move.h"

//Constructor
Move::Move()
{
	this->action = PetAction::None;
	this->heuristic = 0;
}

//Destructor
Move::~Move(void)
{
}

//Copy Constructor
Move::Move(const Move& other)
{
	this->action = PetAction::None;
	this->heuristic = other.heuristic;
}

//Set the action.
void Move::SetAction(PetAction::Action action)
{
	this->action = action;
}

//Set the heuristic.
void Move::SetHeuristic(float heuristic)
{
	this->heuristic = heuristic;
}

//Return the action.
PetAction::Action Move::GetAction()
{
	return this->action;
}

//Return the heuristic.
float Move::GetHeuristic()
{
	return this->heuristic;
}
