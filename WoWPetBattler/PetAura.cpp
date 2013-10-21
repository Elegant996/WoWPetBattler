#include "PetAura.h"

//Constructor
PetAura::PetAura(int auraId, int duration, bool isFresh)
	: QObject(NULL)
{
	QFile auraJson;
	auraJson.setFileName("Ability/" + QString::number(auraId) + ".json");
	auraJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString auraJsonContents = auraJson.readAll();
	auraJson.close();

	QJsonDocument auraDocument = QJsonDocument::fromJson(auraJsonContents.toUtf8());
	QJsonObject aura = auraDocument.object();

	this->auraId = auraId;
	this->name = aura.value(QString("name")).toString();
	this->cooldown = aura.value(QString("cooldown")).toDouble();
	this->rounds = aura.value(QString("rounds")).toDouble();
	this->duration = (duration == 0) ? -1 : duration;
	this->petTypeId = aura.value(QString("petTypeId")).toDouble();
	this->isPassive = aura.value(QString("isPassive")).toBool();
	this->isFresh = isFresh;
}

//Destructor
PetAura::~PetAura(void)
{
}

//Copy Constructor
PetAura::PetAura(const PetAura& other)
	: QObject(NULL)
{
	this->auraId = other.auraId;
	this->name = other.name;
	this->cooldown = other.cooldown;
	this->rounds = other.rounds;
	this->duration = other.duration;
	this->petTypeId = other.petTypeId;
	this->isPassive = other.isPassive;
	this->isFresh = other.isFresh;
}

//Update CDs and auras.
void PetAura::RoundUpdate()
{
	if (!isFresh)
		this->duration -= 1;
	else
		isFresh = false;
}
