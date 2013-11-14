#include "Preferences.h"

//Constructor
Preferences::Preferences(QWidget *parent)
	: QDialog(parent)
{
	//Set up the UI.
	this->ui.setupUi(this);

	//Set the layout.
	this->setLayout(ui.gridLayout);

	//Load settings.
	this->Load();
}

//Destructor
Preferences::~Preferences(void)
{
}

//Handler for the "OK" button.
void Preferences::on_buttonBox_accepted()
{
	//Save the settings.
	this->Save();

	//Alert the main window of the changes.
	emit LoadPreferences();

	//Close the GUI.
	this->close();
}

//Ensure that the min slider can't pass the max slider without increasing the max slider.
void Preferences::on_minAvoidanceSlider_valueChanged(int value)
{
	if (value > ui.maxAvoidanceSlider->value())
		ui.maxAvoidanceSlider->setValue(value);
}

//Ensure that the max slider can't pass the min slider without increasing the min slider.
void Preferences::on_maxAvoidanceSlider_valueChanged(int value)
{
	if (value < ui.minAvoidanceSlider->value())
		ui.minAvoidanceSlider->setValue(value);
}

//Ensure that the min slider can't pass the max slider without increasing the max slider.
void Preferences::on_minHitSlider_valueChanged(int value)
{
	if (value > ui.maxHitSlider->value())
		ui.maxHitSlider->setValue(value);
}

//Ensure that the max slider can't pass the min slider without increasing the min slider.
void Preferences::on_maxHitSlider_valueChanged(int value)
{
	if (value < ui.minHitSlider->value())
		ui.minHitSlider->setValue(value);
}

//Ensure that the min slider can't pass the max slider without increasing the max slider.
void Preferences::on_minCritSlider_valueChanged(int value)
{
	if (value > ui.maxCritSlider->value())
		ui.maxCritSlider->setValue(value);
}

//Ensure that the max slider can't pass the min slider without increasing the min slider.
void Preferences::on_maxCritSlider_valueChanged(int value)
{
	if (value < ui.minCritSlider->value())
		ui.minCritSlider->setValue(value);
}

//Ensure that the min slider can't pass the max slider without increasing the max slider.
void Preferences::on_minChanceOnHitSlider_valueChanged(int value)
{
	if (value > ui.maxChanceOnHitSlider->value())
		ui.maxChanceOnHitSlider->setValue(value);
}

//Ensure that the max slider can't pass the min slider without increasing the min slider.
void Preferences::on_maxChanceOnHitSlider_valueChanged(int value)
{
	if (value < ui.minChanceOnHitSlider->value())
		ui.minChanceOnHitSlider->setValue(value);
}

//Save Preferences.
void Preferences::Save()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open Preferences group.
	setting.beginGroup("Preferences");

	//Store size and position of the Preferences GUI.
	setting.setValue("preferencesSize", this->size());
	setting.setValue("preferencesPosition", this->pos());

	//Close Preferences group.
	setting.endGroup();

	//Open Thresholds group.
	setting.beginGroup("Thresholds");

	//Store avoidance rating.
	setting.setValue("minAvoidanceThreshold", this->ui.minAvoidanceSlider->value());
	setting.setValue("maxAvoidanceThreshold", this->ui.maxAvoidanceSlider->value());

	//Store hit rating.
	setting.setValue("minHitThreshold", this->ui.minHitSlider->value());
	setting.setValue("maxHitThreshold", this->ui.maxHitSlider->value());

	//Store crit rating.
	setting.setValue("minCritThreshold", this->ui.minCritSlider->value());
	setting.setValue("maxCritThreshold", this->ui.maxCritSlider->value());

	//Store chance on hit rating.
	setting.setValue("minChanceOnHitThreshold", this->ui.minChanceOnHitSlider->value());
	setting.setValue("maxChanceOnHitThreshold", this->ui.maxChanceOnHitSlider->value());

	//Close Thresholds group.
	setting.endGroup();

	//Open Options group.
	setting.beginGroup("Options");

	setting.setValue("DisableAero", this->ui.aeroCheckBox->isChecked());		//Set whether to disable Aero.
	setting.setValue("AutoDecideTies", this->ui.aeroCheckBox->isChecked());		//Set whether to auto decide ties.
	setting.setValue("CanPass", this->ui.aeroCheckBox->isChecked());			//Set whether a pet can pass.
	setting.setValue("PvPEnabled", this->ui.aeroCheckBox->isChecked());			//Set whether PvP is enabled.

	//Close Options group.
	setting.endGroup();
}

//Load Preferences.
void Preferences::Load()
{
	//Grab QSettings.
	QSettings setting("Preferences.ini", QSettings::IniFormat);

	//Open Preferences group.
	setting.beginGroup("Preferences");

	//Fetch size and position of the Preferences GUI.
	this->resize(setting.value("preferencesSize", QSize(430, 440)).toSize());
	this->move(setting.value("preferencesPosition", QPoint(this->size().width() / 2, this->size().height() / 2)).toPoint());

	//Close Preferences group.
	setting.endGroup();

	//Open Thresholds group.
	setting.beginGroup("Thresholds");

	//Fetch avoidance rating.
	this->ui.minAvoidanceSlider->setValue(setting.value("minAvoidanceThreshold", 0).toInt());
	this->ui.maxAvoidanceSlider->setValue(setting.value("maxAvoidanceThreshold", 0).toInt());

	//Fetch hit rating.
	this->ui.minHitSlider->setValue(setting.value("minHitThreshold", 0).toInt());
	this->ui.maxHitSlider->setValue(setting.value("maxHitThreshold", 0).toInt());

	//Fetch crit rating.
	this->ui.minCritSlider->setValue(setting.value("minCritThreshold", 1).toInt());
	this->ui.maxCritSlider->setValue(setting.value("maxCritThreshold", 1).toInt());

	//Fetch chance on hit rating.
	this->ui.minChanceOnHitSlider->setValue(setting.value("minChanceOnHitThreshold", 0).toInt());
	this->ui.maxChanceOnHitSlider->setValue(setting.value("maxChanceOnHitThreshold", 0).toInt());

	//Close Thresholds group.
	setting.endGroup();

	//Open Options group.
	setting.beginGroup("Options");

	this->ui.aeroCheckBox->setChecked(setting.value("DisableAero", true).toBool());		//Fetch whether to disable Aero.
	this->ui.tieCheckBox->setChecked(setting.value("AutoDecideTies", true).toBool());	//Fetch whether to auto decide ties.
	this->ui.passCheckBox->setChecked(setting.value("CanPass", false).toBool());		//Fetch whether a pet can pass.
	this->ui.PvPCheckBox->setChecked(setting.value("PvPEnabled", true).toBool());		//Fetch whether PvP is enabled.

	//Close Options group.
	setting.endGroup();
}
