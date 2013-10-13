#include "PetAura.h"

//Constructor
PetAura::PetAura(void)
{
	this->auraId = 0;
	this->name = "";
	this->cooldown = 0;
	this->rounds = 0;
	this->duration = 0;
	this->petTypeId = 0;
	this->isPassive = false;
}

//Destructor
PetAura::~PetAura(void)
{
}

//Copy Constructor
PetAura::PetAura(const PetAura& other)
{
	this->auraId = other.auraId;
	this->name = other.name;
	this->cooldown = other.cooldown;
	this->rounds = other.rounds;
	this->duration = other.duration;
	this->petTypeId = other.petTypeId;
	this->isPassive = other.isPassive;
}

//Sets up the aura for use.
void PetAura::Initialize(int auraId, int duration)
{
	QFile auraJson;
	QDir::setCurrent(QDir::currentPath() + "/Ability");
	auraJson.setFileName(QString::number(auraId) + ".json");
	auraJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString auraJsonContents = auraJson.readAll();
	auraJson.close();
	QDir::setCurrent(QDir::currentPath() + "/..");

	QJsonDocument auraDocument = QJsonDocument::fromJson(auraJsonContents.toUtf8());
	QJsonObject aura = auraDocument.object();

	this->auraId = auraId;
	this->name = aura.value(QString("name")).toString();
	this->cooldown = aura.value(QString("cooldown")).toDouble();
	this->rounds = aura.value(QString("rounds")).toDouble();
	this->duration = (duration == 0) ? -1 : duration;
	this->petTypeId = aura.value(QString("petTypeId")).toDouble();
	this->isPassive = aura.value(QString("isPassive")).toBool();
}

//"Zero-out" the pet aura.
void PetAura::Remove()
{
	this->auraId = 0;
	this->name = "";
	this->cooldown = 0;
	this->rounds = 0;
	this->duration = 0;
	this->petTypeId = 0;
	this->isPassive = false;
}

//Returns the aura id.
int PetAura::GetAuraId()
{
	return this->auraId;
}
