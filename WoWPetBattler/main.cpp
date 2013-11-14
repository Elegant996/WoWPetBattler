#include <QtWidgets/QApplication>

#include "WoWPetBattler.h"

QPointer<WoWPetBattler> mainWindow;		//QPointer to allow us gain access to the QTextBrowser.

//Replacement for default qMessages.
void qMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	switch (type)
	{
	case QtDebugMsg:
		mainWindow->Output(QString("Debug: %1").arg(msg));
		break;
	case QtWarningMsg:
		mainWindow->Output(QString("Warning: %1 (%2:%3, %4)").arg(msg, QString(context.file), QString::number(context.line), QString(context.function)));
		break;
	case QtCriticalMsg:
		mainWindow->Output(QString("Critical: %1 (%2:%3, %4)").arg(msg, QString(context.file), QString::number(context.line), QString(context.function)));
		break;
	case QtFatalMsg:
		mainWindow->Output(QString("Fatal: %1 (%2:%3, %4)").arg(msg, QString(context.file), QString::number(context.line), QString(context.function)));
		abort();
	}
}

//Main function which starts the application.
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	mainWindow = new WoWPetBattler;
	qInstallMessageHandler(qMessageHandler);
	mainWindow->show();
	return app.exec();
}
