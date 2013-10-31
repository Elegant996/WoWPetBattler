#ifndef PETTEAM_H
#define PETTEAM_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>

#include "Pet.h"

class PetTeam : public QObject
{
	Q_OBJECT
	//Q_PROPERTY(QQmlListProperty<Pet> Pets READ GetPets)
	Q_PROPERTY(Pet* ActivePet READ GetActivePet)
	Q_PROPERTY(quint8 ActivePetIndex READ GetActivePetIndex WRITE SetActivePet)

public:
	PetTeam(void);
	~PetTeam(void);
	PetTeam(const PetTeam&);

	void RoundUpdate();

	bool IsTeamDead();

	void AddPet();
	void AddPet(quint16, quint8, quint8, quint8);

	void SetActivePet(quint8);
	Pet* GetActivePet();
	quint8 GetActivePetIndex();

	int GetNumPets();
	Pet* GetPet(quint8);
	//QQmlListProperty<Pet> GetPets();

private:
	quint8 activePet;
	QList<Pet*> pets;
};

#endif

