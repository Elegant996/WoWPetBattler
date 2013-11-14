#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QDebug>

#include "UI_Preferences.h"

class Preferences :	public QDialog
{
	Q_OBJECT

public:
	Preferences(QWidget *parent = 0);
	~Preferences();

signals:
	void WritePreferences();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::PreferencesDialog ui;
};

#endif // PREFERENCES_H

