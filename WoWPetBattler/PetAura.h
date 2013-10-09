#ifndef PETAURA_H
#define PETAURA_H

class PetAura
{
public:
	PetAura(int, int);
	~PetAura(void);
	PetAura(const PetAura&);

private:
	int auraId, duration;
};

#endif

