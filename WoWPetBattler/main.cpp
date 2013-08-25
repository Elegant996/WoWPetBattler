#include "wowpetbattler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WoWPetBattler w;
	w.show();
	return a.exec();
}
