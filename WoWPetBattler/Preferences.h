#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QDebug>
#include <QSettings>

#include "UI_Preferences.h"

class Preferences :	public QDialog
{
	Q_OBJECT

public:
	Preferences(QWidget *parent = 0);
	~Preferences();

signals:
	void LoadPreferences();

private slots:
	void on_buttonBox_accepted();

	void on_minAvoidanceSlider_valueChanged(int);
	void on_maxAvoidanceSlider_valueChanged(int);

	void on_minHitSlider_valueChanged(int);
	void on_maxHitSlider_valueChanged(int);

	void on_minCritSlider_valueChanged(int);
	void on_maxCritSlider_valueChanged(int);

	void on_minChanceOnHitSlider_valueChanged(int);
	void on_maxChanceOnHitSlider_valueChanged(int);

private:
	void Save();
	void Load();

	Ui::PreferencesDialog ui;
};

#endif // PREFERENCES_H

