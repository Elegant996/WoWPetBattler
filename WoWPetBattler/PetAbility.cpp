#include "PetAbility.h"

//Constructor
PetAbility::PetAbility(quint16 abilityId, qint8 cooldown, bool isVerified)
	: QObject(NULL)
{
	QFile abilityJson;
	abilityJson.setFileName("Ability/" + QString::number(abilityId) + ".json");
	abilityJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString abilityJsonContents = abilityJson.readAll();
	abilityJson.close();

	QJsonDocument abilityDocument = QJsonDocument::fromJson(abilityJsonContents.toUtf8());
	QJsonObject ability = abilityDocument.object();

	this->abilityId = abilityId;
	this->name = ability.value(QString("name")).toString();
	this->cooldown = ability.value(QString("cooldown")).toDouble();
	this->currentCooldown = cooldown;
	this->rounds = ability.value(QString("rounds")).toDouble();
	this->petTypeId = (PetType::Type)(int)ability.value(QString("petTypeId")).toDouble();
	this->isPassive = ability.value(QString("isPassive")).toBool();
	this->isVerified = isVerified;
	this->usedThisTurn = false;
}

//Deconstructor
PetAbility::~PetAbility(void)
{
}

//Copy Constructor
PetAbility::PetAbility(const PetAbility& other)
	: QObject(NULL)
{
	this->abilityId = other.abilityId;
	this->name = other.name;
	this->cooldown = other.cooldown;
	this->currentCooldown = other.currentCooldown;
	this->rounds = other.rounds;
	this->petTypeId = other.petTypeId;
	this->isPassive = other.isPassive;
	this->isVerified = other.isVerified;
	this->usedThisTurn = other.usedThisTurn;
}

//Update CDs and auras.
void PetAbility::RoundUpdate()
{
	if (!usedThisTurn && currentCooldown > 0)
		currentCooldown -= 1;
	else if (usedThisTurn)
		usedThisTurn = false;
}

//Set the abilities cooldown.
void PetAbility::UseAbility()
{
	this->currentCooldown = this->cooldown;
}

//Update the cooldown of the ability.
void PetAbility::SetCooldown(qint8 cooldown)
{
	this->currentCooldown = cooldown;
}

//Confirm whether we know this ability is known.
void PetAbility::IsVerified(bool verification)
{
	this->isVerified = verification;
}

//Return ability Id.
quint16 PetAbility::GetAbilityId()
{
	return this->abilityId;
}

//Return cooldown status.
qint8 PetAbility::GetCooldown()
{
	return this->currentCooldown;
}

//Return the number of rounds the ability will persist for.
qint8 PetAbility::GetRounds()
{
	return this->rounds;
}

//Return whether or not the ability is verified.
bool PetAbility::IsVerified()
{
	return this->isVerified;
}
