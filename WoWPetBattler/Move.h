#ifndef MOVE_H
#define MOVE_H

class Move
{
public:
	Move(int);
	~Move(void);
	Move(const Move&);

private:
	const int move;
	float heuristic;
};

#endif

