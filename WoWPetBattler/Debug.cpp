#include "Debug.h"

//Returns instance of static class.
Debug* Debug::Instance()
{
	static Debug debug;
	return &debug;
}

//Replacement for default qMessages.
void Debug::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	switch (type)
	{
		case QtDebugMsg:
			emit Instance()->OutputToGUI(QString("Debug: %1").arg(msg));
			break;
		case QtWarningMsg:
			emit Instance()->OutputToGUI(QString("Warning: %1").arg(msg));
			break;
		case QtCriticalMsg:
			emit Instance()->OutputToGUI(QString("Critical: %1 (%2:%3, %4)").arg(msg, QString(context.file), QString::number(context.line), QString(context.function)));
			break;
		case QtFatalMsg:
			emit Instance()->OutputToGUI(QString("Fatal: %1 (%2:%3, %4)").arg(msg, QString(context.file), QString::number(context.line), QString(context.function)));
			abort();
	}
}
