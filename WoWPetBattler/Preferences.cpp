#include "Preferences.h"

//Constructor
Preferences::Preferences(QWidget *parent)
	: QDialog(parent)
{
	//Set up the UI.
	this->ui.setupUi(this);

	//Set the layout.
	this->setLayout(ui.gridLayout);

	//Set initial size and position of the dialog GUI.
	this->resize(430, 435);
	this->move(size().width() / 2, size().height() / 2);
}

//Destructor
Preferences::~Preferences(void)
{
}

//Handler for the "OK" button.
void Preferences::on_buttonBox_accepted()
{
	//Alert the main window of the changes.
	emit WritePreferences();

	//Close the GUI.
	this->close();
}
