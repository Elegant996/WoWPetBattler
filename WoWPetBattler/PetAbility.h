#ifndef PETABILITY_H
#define PETABILITY_H

class PetAbility
{
public:
	PetAbility(int, int, bool);
	~PetAbility(void);
	PetAbility(const PetAbility&);
	PetAbility& operator=(const PetAbility&);

	void SetCooldown(int);
	void IsVerified(bool);

	int GetAbilityID();
	int GetCooldown();
	bool IsVerified();

private:
	int abilityID, cooldown;
	bool isVerified;
};

#endif

