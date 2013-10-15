#include "ScriptHelper.h"

const QScriptValue::PropertyFlags ScriptHelper::ConstantFlag =
		QScriptValue::ReadOnly | QScriptValue::Undeletable;
const QScriptValue::PropertyFlags ScriptHelper::GetterSetter =
		QScriptValue::PropertyGetter | QScriptValue::PropertySetter;

ScriptHelper::ScriptHelper(void)
{
}


ScriptHelper::~ScriptHelper(void)
{
}

QScriptValue ScriptHelper::JsInt32Property(QScriptContext *ctx, QScriptEngine *eng)
{
	//Retrieve the int32 data object.
	qint32 *value = (qint32*)(qscriptvalue_cast<quintptr>(ctx->callee().data()));

	//Check if value is valid.
	if (value == nullptr)
		return QScriptValue();

	//Check if the value is being set.
	if (ctx->argumentCount() == 1)
		*value = ctx->argument(0).toInt32();

	return *value;
}

QScriptValue ScriptHelper::JsFloatProperty(QScriptContext *ctx, QScriptEngine *eng)
{
	//Retrieve the float data object.
	float *value = (float*)(qscriptvalue_cast<quintptr>(ctx->callee().data()));

	//Check if value is valid.
	if (value = nullptr)
		return QScriptValue();

	//Check if the vlaue is being set.
	if (ctx->argumentCount() == 1)
		*value = ctx->argument(0).toNumber();

	return *value;
}

QScriptValue ScriptHelper::NewJsPetStage(QScriptEngine* engine, PetStage* petStage)
{
	//Create a new object to store the result.
	QScriptValue result = engine->newObject();

	QScriptValue petTeam = engine->newArray(3);
	for (int i=0; i < 3; i+=1)
	{
		petTeam.setProperty(i, &petStage->petTeam.at(i), GetterSetter);
		QScriptValue activePet = engine->newFunction(JsInt32Property);
		activePet.setData((quintptr)&petStage->petTeam.at(i)->activePet);
		petTeam.property(i).setProperty("activePet", activePet, GetterSetter);

		QScriptValue pet = engine->newArray((i==0)?1:3);
		for (int j=0; j < ((i==0)?1:3); j+=1)
		{
			pet.setProperty(j, &petStage->petTeam.at(i)->pet.at(j), GetterSetter);
		}
		petTeam.setProperty("pet", pet, GetterSetter);
	}

	result.setProperty("petTeam", petTeam, GetterSetter);

	//All finished.
	return result;
}
