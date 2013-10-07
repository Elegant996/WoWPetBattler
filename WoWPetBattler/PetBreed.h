#ifndef PETBREED_H
#define PETBREED_H

class PetBreed
{
public:
	static float GetHealth(int);
	static float GetPower(int);
	static float GetSpeed(int);

private:
	static float health[];
	static float power[];
	static float speed[];
};

#endif

