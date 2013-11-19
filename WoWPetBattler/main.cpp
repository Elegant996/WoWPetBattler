#include <QtWidgets/QApplication>

#include "Debug.h"
#include "WoWPetBattler.h"

//Main function which starts the application.
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	WoWPetBattler mainWindow;
	qInstallMessageHandler(Debug::messageHandler);
	mainWindow.show();
	mainWindow.activateWindow();
	if (mainWindow.isMinimized())
		mainWindow.showNormal();
	return app.exec();
}
