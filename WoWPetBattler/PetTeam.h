#ifndef PETTEAM_H
#define PETTEAM_H

#include <QList>
#include <QObject>
#include <QQmlListProperty>
#include <QtAlgorithms>

#include "Pet.h"

class PetTeam : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QQmlListProperty<Pet> pets READ GetPets)
	Q_PROPERTY(Pet* activePet READ GetActivePet)
	Q_PROPERTY(int activePetIndex READ GetActivePetIndex WRITE SetActivePet)

public:
	PetTeam(void);
	~PetTeam(void);
	PetTeam(const PetTeam&);

	void RoundUpdate();

	void AddPet();
	void AddPet(int, int, int, int);

	void SetActivePet(int);
	Pet* GetActivePet();
	int GetActivePetIndex();

	int GetNumPets();
	Pet* GetPet(int);
	QQmlListProperty<Pet> GetPets();

private:
	int activePet;
	QList<Pet*> pets;
};

#endif

