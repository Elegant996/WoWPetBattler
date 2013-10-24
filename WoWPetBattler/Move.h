#ifndef MOVE_H
#define MOVE_H

#include <QDataStream>

class Move
{
public:
	Move(quint8);
	~Move(void);
	Move(const Move&);

private:
	const quint8 move;
	float heuristic;
};

#endif

