#include "PetAura.h"

//Constructor
PetAura::PetAura(int auraId, int duration)
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
