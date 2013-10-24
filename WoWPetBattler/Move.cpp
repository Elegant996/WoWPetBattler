#include "Move.h"

//Constructor
Move::Move(quint8 move)
	: move(move)
{
	this->heuristic = 0;
}

//Destructor
Move::~Move(void)
{
}

//Copy Constructor
Move::Move(const Move& other)
	: move(other.move)
{
	this->heuristic = other.heuristic;
}
