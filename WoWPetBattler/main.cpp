#include "wowpetbattler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication prog(argc, argv);
	WoWPetBattler window;
	window.show();
	return prog.exec();
}
