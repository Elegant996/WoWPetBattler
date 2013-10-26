#include "Pet.h"

//Constructors
Pet::Pet()
	: QObject(NULL)
{
	this->name = "Dummy Pet";
	this->speciesId = 0;
	this->breed = 0;
	this->quality = 0;
	this->level = 0;
	this->type = (PetType::Type)0;
	this->baseHealth = 0;
	this->basePower = 0;
	this->baseSpeed = 0;
	this->currentHealth = 0;
	this->currentMaxHealth = 0;
	this->currentPower = 0;
	this->currentSpeed = 0;
	this->accuracyOffset = 0.00;
	this->damageModifier = 1.00;
	this->healingModifier = 1.00;
	this->defenseModifier = 1.00;
	this->bonusDamage = 0;
	this->blockDamage = 0;
	this->bonusHealing = 0;
	this->blockHealing = 0;
	this->racialUsed = false;
	this->attackedThisRound = false;
	this->currentAction = new PetAction(0, 0);
}

Pet::Pet(quint16 speciesId, quint8 breed, quint8 quality, quint8 level)
{
	QFile speciesJson;
	speciesJson.setFileName("Species/" + QString::number(speciesId) + ".json");
	speciesJson.open(QIODevice::ReadOnly | QIODevice::Text);
	QString speciesJsonContents = speciesJson.readAll();
	speciesJson.close();

	QJsonDocument speciesDocument = QJsonDocument::fromJson(speciesJsonContents.toUtf8());
	QJsonObject species = speciesDocument.object();

	this->name = species.value(QString("name")).toString();
	this->speciesId = speciesId;
	this->breed = breed;
	this->type = (PetType::Type)(int)species.value(QString("petTypeId")).toDouble();
	this->quality = quality;
	this->level = level;
	this->baseHealth = species.value(QString("baseHealth")).toDouble();
	this->basePower = species.value(QString("basePower")).toDouble();
	this->baseSpeed = species.value(QString("baseSpeed")).toDouble();
	this->normalMaxHealth = PetStats::CalculateHealth(this->baseHealth, PetBreed::GetHealth(this->breed), this->level, this->quality);
	this->normalPower = PetStats::CalculatePower(this->basePower, PetBreed::GetPower(this->breed), this->level, this->quality);
	this->normalSpeed = PetStats::CalculateSpeed(this->baseSpeed, PetBreed::GetSpeed(this->breed), this->level, this->quality);
	this->lastKnownHealth = 0;
	this->currentHealth = this->normalMaxHealth;
	this->currentMaxHealth = this->currentHealth;
	this->currentPower = this->normalPower;
	this->currentSpeed = this->normalSpeed;
	this->accuracyOffset = 0.00;
	this->damageModifier = 1.00;
	this->healingModifier = 1.00;
	this->defenseModifier = 1.00;
	this->bonusDamage = 0;
	this->blockDamage = 0;
	this->bonusHealing = 0;
	this->blockHealing = 0;
	this->racialUsed = false;
	this->attackedThisRound = false;
	this->currentAction = new PetAction(0, 0);
	this->abilityList = species.value(QString("abilities")).toArray();
	this->petAuras.append(new PetAura(PetType::GetTypeAuraId(type), 0, false));
}

//Deconstructor
Pet::~Pet(void)
{
	delete currentAction;
	qDeleteAll(this->petAbilities);
	this->petAbilities.clear();
	RemoveAuras();
}

//Copy Constructor
Pet::Pet(const Pet& other)
	: QObject(NULL)
{
	this->name = other.name;
	this->speciesId = other.speciesId;
	this->breed = other.breed;
	this->type = other.type;
	this->quality = other.quality;
	this->level = other.level;
	this->baseHealth = other.baseHealth;
	this->basePower = other.basePower;
	this->baseSpeed = other.baseSpeed;
	this->normalMaxHealth = other.normalMaxHealth;
	this->normalPower = other.normalPower;
	this->normalSpeed = other.normalSpeed;
	this->lastKnownHealth = other.lastKnownHealth;
	this->currentHealth = other.currentHealth;
	this->currentMaxHealth = other.currentMaxHealth;
	this->currentPower = other.currentPower;
	this->currentSpeed = other.currentSpeed;
	this->accuracyOffset = other.accuracyOffset;
	this->damageModifier = other.damageModifier;
	this->healingModifier = other.healingModifier;
	this->defenseModifier = other.defenseModifier;
	this->bonusDamage = other.bonusDamage;
	this->blockDamage = other.blockDamage;
	this->bonusHealing = other.bonusHealing;
	this->blockHealing = other.blockHealing;
	this->racialUsed = other.racialUsed;
	this->attackedThisRound = other.attackedThisRound;
	this->currentAction = new PetAction(*other.currentAction);
	this->abilityList = other.abilityList;
	for (int i=0; i < other.petAbilities.size(); i+=1)
		this->petAbilities.append(new PetAbility(*other.petAbilities.at(i)));
	for (int i=0; i < other.petAuras.size(); i+=1)
		this->petAuras.append(new PetAura(*other.petAuras.at(i)));
	for (int i=0; i < other.petStatuses.size(); i+=1)
		this->petStatuses.append(PetStatus(other.petStatuses.at(i)));
}

//Update current action, CDs and auras.
void Pet::RoundUpdate()
{
	//Update the current action.
	this->currentAction->RoundUpdate();

	//Remove all statuses.
	this->petStatuses.clear();

	//Update each ability.
	foreach (PetAbility *petAbility, this->petAbilities)
		petAbility->RoundUpdate();

	//Update each aura.
	foreach (PetAura *petAura, this->petAuras)
		petAura->RoundUpdate();
}

//Adds the status to the list.
void Pet::AddStatus(Pet::PetStatus status)
{
	if (!petStatuses.contains(status))
		petStatuses.append(status);
}

//Return whether or not the pet has a specific status.
bool Pet::HasStatus(Pet::PetStatus petStatus)
{
	return petStatuses.contains(petStatus);
}

//Return the number of status effects on the pet.
int Pet::GetNumStatuses()
{
	return petStatuses.size();
}

//Return the pet's status vector.
Pet::PetStatus Pet::GetStatus(quint8 index)
{
	return (Pet::PetStatus)this->petStatuses.at(index-1);
}

//For QML purposes.
/*QList<int> Pet::GetStatuses()
{
	return petStatuses;
}*/

//Add an ability to the current pet.
void Pet::AddAbility(bool verification, quint8 tier, qint8 cooldown)
{
	this->petAbilities.append(new PetAbility(abilityList[(this->petAbilities.size()+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Replace the ability of the current pet at specified index.
void Pet::ReplaceAbility(quint8 index, bool verification, quint8 tier, qint8 cooldown)
{
	this->petAbilities.replace(index-1, new PetAbility(abilityList[(index+1)+((tier-1)*3)-1].toObject().value(QString("id")).toDouble(), cooldown, verification));
}

//Return the number of abilities known by the pet.
int Pet::GetNumAbilities()
{
	return petAbilities.size();
}

//Return the desired ability at the specified index.
PetAbility* Pet::GetAbility(quint8 index)
{
	return this->petAbilities.at(index-1);
}

//For QML purposes.
/*QQmlListProperty<PetAbility> Pet::GetAbilities()
{
	return QQmlListProperty<PetAbility>(this, petAbilities);
}*/

//Add an aura to the current pet.
void Pet::AddAura(quint16 auraId, qint8 duration, bool isFresh)
{
	//Check to see if petAuras is empty, if not check to see if it exists already and overwrite.
	if (!petAuras.isEmpty())
		for (int i=0; i < this->petAuras.size(); i+=1)
			if (auraId == this->petAuras.at(i)->GetAuraId())
			{
				this->petAuras.at(i)->UpdateAura(duration, isFresh);
				return;
			}

	//If it doesn't exist, add it.
	this->petAuras.append(new PetAura(auraId, duration, isFresh));
}

//Removes all pet auras on the current pet.
void Pet::RemoveAuras()
{
	qDeleteAll(this->petAuras);
	this->petAuras.clear();
}

//Return number of auras on the pet
int Pet::GetNumAuras()
{
	return petAuras.size();
}

//Return the desired aura at the specified index.
PetAura* Pet::GetAura(quint8 index)
{
	return this->petAuras.at(index-1);
}

//For QML purposes.
/*QQmlListProperty<PetAura> Pet::GetAuras()
{
	return QQmlListProperty<PetAura>(this, petAuras);
}*/

//Return whether or not the pet is dead.
bool Pet::IsDead()
{
	return (currentHealth == 0) ? true : false;
}

//Set the pet's last know health.
void Pet::SetLastKnownHealth(quint16 lastKnownHealth)
{
	this->lastKnownHealth = lastKnownHealth;
}

//Set the pet's current health.
void Pet::SetHealth(quint16 health)
{
	this->currentHealth = health;
}

//Set the pet's current max health.
void Pet::SetMaxHealth(quint16 maxHealth)
{
	this->currentMaxHealth = maxHealth;
}

//Set the pet's current power.
void Pet::SetPower(quint16 power)
{
	this->currentPower = power;
}

//Set the pet's current speed.
void Pet::SetSpeed(quint16 speed)
{
	this->currentSpeed = speed;
}

//Set the pet's accuracy offset.
void Pet::SetAccuracyOffset(float accuracyOffset)
{
	this->accuracyOffset = accuracyOffset;
}

//Set the pet's damage modifier.
void Pet::SetDamageModifier(float damageModifier)
{
	this->damageModifier = damageModifier;
}

//Set the pet's healing modifier.
void Pet::SetHealingModifier(float healingModifier)
{
	this->healingModifier = healingModifier;
}

//Set the pet's defense modifier.
void Pet::SetDefenseModifier(float defenseModifier)
{
	this->defenseModifier = defenseModifier;
}

//Set the pet's bonus damage.
void Pet::SetBonusDamage(quint16 bonusDamage)
{
	this->bonusDamage = bonusDamage;
}

//Set the pet's block damage.
void Pet::SetBlockDamage(quint16 blockDamage)
{
	this->blockDamage = blockDamage;
}

//Set the pet's bonus healing.
void Pet::SetBonusHealing(quint16 bonusHealing)
{
	this->bonusHealing = bonusHealing;
}

//Set the pet's block healing.
void Pet::SetBlockHealing(quint16 blockHealing)
{
	this->blockHealing = blockHealing;
}

//Set whether or not the racial has been used.
void Pet::RacialUsed(bool racialUsed)
{
	this->racialUsed = racialUsed;
}

//Set whether or not the pet attacked this round.
void Pet::AttackedThisRound(bool attackedThisRound)
{
	this->attackedThisRound = attackedThisRound;
}

//Return pet's species Id.
quint16 Pet::GetSpeciesId()
{
	return this->speciesId;
}

//Return pet's type.
PetType::Type Pet::GetType()
{
	return this->type;
}

//Return pet's level.
quint8 Pet::GetLevel()
{
	return this->level;
}

//Return pet's normal max health.
quint16 Pet::GetNormalMaxHealth()
{
	return this->normalMaxHealth;
}

//Return pet's normal power.
quint16 Pet::GetNormalPower()
{
	return this->normalPower;
}

//Return pet's normal speed.
quint16 Pet::GetNormalSpeed()
{
	return this->normalSpeed;
}

//Return pet's last known health;
quint16 Pet::GetLastKnownHealth()
{
	return this->lastKnownHealth;
}

//Return pet's current health.
quint16 Pet::GetHealth()
{
	return this->currentHealth;
}
//Return pet's current max health.
quint16 Pet::GetMaxHealth()
{
	return this->currentMaxHealth;
}

//Return pet's current power.
quint16 Pet::GetPower()
{
	return this->currentPower;
}

//Return pet's current speed.
quint16 Pet::GetSpeed()
{
	return this->currentSpeed;
}

//Return the pet's accuracy offset.
float Pet::GetAccuracyOffset()
{
	return this->accuracyOffset;
}

//Return the pet's damage modifier.
float Pet::GetDamageModifier()
{
	return this->damageModifier;
}

//Return the pet's healing modifier.
float Pet::GetHealingModifier()
{
	return this->healingModifier;
}

//Return the pet's defense modifier.
float Pet::GetDefenseModifier()
{
	return this->defenseModifier;
}

//Return the pet's bonus damage.
quint16 Pet::GetBonusDamage()
{
	return this->bonusDamage;
}

//Return the pet's block damage.
quint16 Pet::GetBlockDamage()
{
	return this->blockDamage;
}

//Return the pet's bonus healing.
quint16 Pet::GetBonusHealing()
{
	return this->bonusHealing;
}

//Return the pet's block healing.
quint16 Pet::GetBlockHealing()
{
	return this->blockHealing;
}

//Return the pet's current action.
PetAction* Pet::GetCurrentAction()
{
	return this->currentAction;
}

//Return whether or not the pet's racial has been used.
bool Pet::RacialUsed()
{
	return this->racialUsed;
}

//Return whether or not the pet attacked this round.
bool Pet::AttackedThisRound()
{
	return this->attackedThisRound;
}
