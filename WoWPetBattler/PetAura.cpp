#include "PetAura.h"

//Constructor
PetAura::PetAura(quint16 auraId, qint8 duration, bool isFresh)
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
	this->petTypeId = (PetType::Type)(int)aura.value(QString("petTypeId")).toDouble();
	this->isPassive = aura.value(QString("isPassive")).toBool();
	this->isFresh = isFresh;
	this->isObject = false;
	this->onSwapIn = false;
	this->charges = 0;
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
	this->isObject = other.isObject;
	this->onSwapIn = other.onSwapIn;
	this->charges = other.charges;
}

//Update CDs and auras.
void PetAura::RoundUpdate()
{
	if (!isFresh && duration != -1)
		this->duration -= 1;
	else
		isFresh = false;
}

//Update the aura. Used when recasted.
void PetAura::UpdateAura(int duration, bool isFresh)
{
	this->duration = (duration == 0) ? -1 : duration;
	this->isFresh = isFresh;
}

//Set whether or not the aura is an object.
void PetAura::IsObject(bool isObject)
{
	this->isObject = isObject;
}

//Set whether or not the aura takes effect on a pet swap in.
void PetAura::OnSwapIn(bool onSwapIn)
{
	this->onSwapIn = onSwapIn;
}

//Set the number of charges left on the aura.
void PetAura::SetCharges(quint8 charges)
{
	this->charges = charges;
}

//Return the name of the aura.
QString PetAura::GetName()
{
	return this->name;
}

//Return the id of the aura.
quint16 PetAura::GetAuraId()
{
	return this->auraId;
}

//Return the number of charges left on the aura.
quint8 PetAura::GetCharges()
{
	return this->charges;
}

//Return whether or not the aura is an object.
bool PetAura::IsObject()
{
	return this->isObject;
}

//Return whether or not the aura takes effect on a pet swap in.
bool PetAura::OnSwapIn()
{
	return this->onSwapIn;
}