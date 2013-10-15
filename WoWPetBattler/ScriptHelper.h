#ifndef SCRIPTHELPER_H
#define SCRIPTHELPER_H

#include <QScriptEngine>

#include "PetStage.h"

class ScriptHelper
{
public:
	ScriptHelper(void);
	~ScriptHelper(void);

	static QScriptValue JsInt32Property(QScriptContext*, QScriptEngine*);
	static QScriptValue JsFloatProperty(QScriptContext *ctx, QScriptEngine *eng);

	QScriptValue NewJsPetStage(QScriptEngine*, PetStage*);

private:
	static const QScriptValue::PropertyFlags ConstantFlag;
	static const QScriptValue::PropertyFlags GetterSetter;
};

#endif

