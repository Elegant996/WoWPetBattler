#ifndef PETABILITY_H
#define PETABILITY_H

#include <QVector>
#include <QtAlgorithms>

class PetAbility
{
public:
	PetAbility(int, int, bool);
	~PetAbility(void);
	PetAbility(const PetAbility&);

	void SetCooldown(int);
	void IsVerified(bool);

	int GetAbilityId();
	int GetCooldown();
	bool IsVerified();

private:
	int abilityId, cooldown;
	bool isVerified;
};

#endif

