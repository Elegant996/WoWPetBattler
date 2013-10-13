#include "PetAbility.h"

//Constructor
PetAbility::PetAbility(void)
{
	this->abilityId = 0;
	this->name = "";
	this->cooldown = 0;
	this->currentCooldown = 0;
	this->rounds = 0;
	this->petTypeId = 0;
	this->isPassive = false;
	this->isVerified = false;
}

//Deconstructor
PetAbility::~PetAbility(void)
{
}

//Copy Constructor
PetAbility::PetAbility(const PetAbility& other)
{
	this->abilityId = other.abilityId;
	this->name = other.name;
	this->cooldown = other.cooldown;
	this->currentCooldown = other.currentCooldown;
	this->rounds = other.rounds;
	this->petTypeId = other.petTypeId;
	this->isPassive = other.isPassive;
	this->isVerified = other.isVerified;
}

//Sets up the ability for use.
void PetAbility::Initialize(int abilityId, int cooldown, bool isVerified)
{
	QFile abilityJson;
	QDir::setCurrent(QDir::currentPath() + "/Ability");
	abilityJson.setFileName(QString::number(abilityId) + ".json");
	abilityJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString abilityJsonContents = abilityJson.readAll();
	abilityJson.close();
	QDir::setCurrent(QDir::currentPath() + "/..");

	QJsonDocument abilityDocument = QJsonDocument::fromJson(abilityJsonContents.toUtf8());
	QJsonObject ability = abilityDocument.object();

	this->abilityId = abilityId;
	this->name = ability.value(QString("name")).toString();
	this->cooldown = ability.value(QString("cooldown")).toDouble();
	this->currentCooldown = cooldown;
	this->rounds = ability.value(QString("rounds")).toDouble();
	this->petTypeId = ability.value(QString("petTypeId")).toDouble();
	this->isPassive = ability.value(QString("isPassive")).toBool();
	this->isVerified = isVerified;
}

//"Zero-out" the pet ability.
void PetAbility::Remove()
{
	this->abilityId = 0;
	this->name = "";
	this->cooldown = 0;
	this->currentCooldown = 0;
	this->rounds = 0;
	this->petTypeId = 0;
	this->isPassive = false;
	this->isVerified = false;
}

//Update the cooldown of the ability.
void PetAbility::SetCooldown(int CD)
{
	this->currentCooldown = CD;
}

//Confirm whether we know this ability is known.
void PetAbility::IsVerified(bool verification)
{
	this->isVerified = verification;
}

//Return ability id.
int PetAbility::GetAbilityId()
{
	return this->abilityId;
}

//Return cooldown status.
int PetAbility::GetCooldown()
{
	return this->currentCooldown;
}

//Return whether or not the ability is verified.
bool PetAbility::IsVerified()
{
	return this->isVerified;
}
