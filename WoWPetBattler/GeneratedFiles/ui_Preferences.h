/********************************************************************************
** Form generated from reading UI file 'Preferences.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCES_H
#define UI_PREFERENCES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PreferencesDialog
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *thresholdLabel;
    QLabel *optionsLabel;
    QDialogButtonBox *buttonBox;
    QGridLayout *thresholdsGridLayout;
    QSplitter *minChanceOnHitSplitter;
    QLabel *minChanceOnHitLabel;
    QSlider *minChanceOnHitSlider;
    QSplitter *maxChanceOnHitSplitter;
    QLabel *maxChanceOnHitLabel;
    QSlider *maxChanceOnHitSlider;
    QSplitter *minCritSplitter;
    QLabel *minCritLabel;
    QSlider *minCritSlider;
    QSplitter *maxHitSplitter;
    QLabel *maxHitLabel;
    QSlider *maxHitSlider;
    QSplitter *maxAvoidanceSplitter;
    QLabel *maxAvoidanceLabel;
    QSlider *maxAvoidanceSlider;
    QSplitter *minAvoidanceSplitter;
    QLabel *minAvoidanceLabel;
    QSlider *minAvoidanceSlider;
    QSplitter *minHitSplitter;
    QLabel *minHitLabel;
    QSlider *minHitSlider;
    QSplitter *maxCritSplitter;
    QLabel *maxCritLabel;
    QSlider *maxCritSlider;
    QSplitter *depthSplitter;
    QLabel *depthLabel;
    QSlider *depthSlider;
    QGroupBox *groupBox;
    QGridLayout *heuristicGridLayout;
    QVBoxLayout *verticalLayout;
    QRadioButton *currentHealthRadioButton;
    QRadioButton *fixedHealthRadioButton;
    QSplitter *checkBoxSplitter;
    QCheckBox *aeroCheckBox;
    QCheckBox *tieCheckBox;
    QCheckBox *passCheckBox;
    QCheckBox *PvPCheckBox;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(600, 539);
        PreferencesDialog->setMinimumSize(QSize(430, 440));
        PreferencesDialog->setBaseSize(QSize(430, 440));
        layoutWidget = new QWidget(PreferencesDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 581, 521));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(10, 10, 10, 10);
        thresholdLabel = new QLabel(layoutWidget);
        thresholdLabel->setObjectName(QStringLiteral("thresholdLabel"));
        QFont font;
        font.setFamily(QStringLiteral("MS Sans Serif"));
        font.setPointSize(24);
        font.setBold(false);
        font.setWeight(50);
        thresholdLabel->setFont(font);
        thresholdLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(thresholdLabel, 0, 0, 1, 2);

        optionsLabel = new QLabel(layoutWidget);
        optionsLabel->setObjectName(QStringLiteral("optionsLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Sans Serif"));
        font1.setPointSize(20);
        font1.setBold(false);
        font1.setWeight(50);
        optionsLabel->setFont(font1);
        optionsLabel->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(optionsLabel, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 9, 1, 1, 1);

        thresholdsGridLayout = new QGridLayout();
        thresholdsGridLayout->setSpacing(20);
        thresholdsGridLayout->setObjectName(QStringLiteral("thresholdsGridLayout"));
        thresholdsGridLayout->setContentsMargins(10, -1, 10, -1);
        minChanceOnHitSplitter = new QSplitter(layoutWidget);
        minChanceOnHitSplitter->setObjectName(QStringLiteral("minChanceOnHitSplitter"));
        minChanceOnHitSplitter->setOrientation(Qt::Vertical);
        minChanceOnHitLabel = new QLabel(minChanceOnHitSplitter);
        minChanceOnHitLabel->setObjectName(QStringLiteral("minChanceOnHitLabel"));
        minChanceOnHitLabel->setContextMenuPolicy(Qt::NoContextMenu);
        minChanceOnHitLabel->setLayoutDirection(Qt::LeftToRight);
        minChanceOnHitLabel->setAlignment(Qt::AlignCenter);
        minChanceOnHitSplitter->addWidget(minChanceOnHitLabel);
        minChanceOnHitSlider = new QSlider(minChanceOnHitSplitter);
        minChanceOnHitSlider->setObjectName(QStringLiteral("minChanceOnHitSlider"));
        minChanceOnHitSlider->setMinimum(0);
        minChanceOnHitSlider->setMaximum(20);
        minChanceOnHitSlider->setSingleStep(1);
        minChanceOnHitSlider->setPageStep(2);
        minChanceOnHitSlider->setValue(0);
        minChanceOnHitSlider->setSliderPosition(0);
        minChanceOnHitSlider->setOrientation(Qt::Horizontal);
        minChanceOnHitSlider->setTickPosition(QSlider::TicksBelow);
        minChanceOnHitSlider->setTickInterval(10);
        minChanceOnHitSplitter->addWidget(minChanceOnHitSlider);

        thresholdsGridLayout->addWidget(minChanceOnHitSplitter, 3, 0, 1, 1);

        maxChanceOnHitSplitter = new QSplitter(layoutWidget);
        maxChanceOnHitSplitter->setObjectName(QStringLiteral("maxChanceOnHitSplitter"));
        maxChanceOnHitSplitter->setOrientation(Qt::Vertical);
        maxChanceOnHitLabel = new QLabel(maxChanceOnHitSplitter);
        maxChanceOnHitLabel->setObjectName(QStringLiteral("maxChanceOnHitLabel"));
        maxChanceOnHitLabel->setContextMenuPolicy(Qt::NoContextMenu);
        maxChanceOnHitLabel->setLayoutDirection(Qt::LeftToRight);
        maxChanceOnHitLabel->setAlignment(Qt::AlignCenter);
        maxChanceOnHitSplitter->addWidget(maxChanceOnHitLabel);
        maxChanceOnHitSlider = new QSlider(maxChanceOnHitSplitter);
        maxChanceOnHitSlider->setObjectName(QStringLiteral("maxChanceOnHitSlider"));
        maxChanceOnHitSlider->setMinimum(0);
        maxChanceOnHitSlider->setMaximum(20);
        maxChanceOnHitSlider->setSingleStep(1);
        maxChanceOnHitSlider->setPageStep(2);
        maxChanceOnHitSlider->setValue(0);
        maxChanceOnHitSlider->setSliderPosition(0);
        maxChanceOnHitSlider->setOrientation(Qt::Horizontal);
        maxChanceOnHitSlider->setTickPosition(QSlider::TicksBelow);
        maxChanceOnHitSlider->setTickInterval(10);
        maxChanceOnHitSplitter->addWidget(maxChanceOnHitSlider);

        thresholdsGridLayout->addWidget(maxChanceOnHitSplitter, 3, 1, 1, 1);

        minCritSplitter = new QSplitter(layoutWidget);
        minCritSplitter->setObjectName(QStringLiteral("minCritSplitter"));
        minCritSplitter->setOrientation(Qt::Vertical);
        minCritLabel = new QLabel(minCritSplitter);
        minCritLabel->setObjectName(QStringLiteral("minCritLabel"));
        minCritLabel->setContextMenuPolicy(Qt::NoContextMenu);
        minCritLabel->setLayoutDirection(Qt::LeftToRight);
        minCritLabel->setAlignment(Qt::AlignCenter);
        minCritSplitter->addWidget(minCritLabel);
        minCritSlider = new QSlider(minCritSplitter);
        minCritSlider->setObjectName(QStringLiteral("minCritSlider"));
        minCritSlider->setMinimum(0);
        minCritSlider->setMaximum(20);
        minCritSlider->setSingleStep(1);
        minCritSlider->setPageStep(2);
        minCritSlider->setValue(1);
        minCritSlider->setSliderPosition(1);
        minCritSlider->setOrientation(Qt::Horizontal);
        minCritSlider->setTickPosition(QSlider::TicksBelow);
        minCritSlider->setTickInterval(10);
        minCritSplitter->addWidget(minCritSlider);

        thresholdsGridLayout->addWidget(minCritSplitter, 2, 0, 1, 1);

        maxHitSplitter = new QSplitter(layoutWidget);
        maxHitSplitter->setObjectName(QStringLiteral("maxHitSplitter"));
        maxHitSplitter->setOrientation(Qt::Vertical);
        maxHitLabel = new QLabel(maxHitSplitter);
        maxHitLabel->setObjectName(QStringLiteral("maxHitLabel"));
        maxHitLabel->setContextMenuPolicy(Qt::NoContextMenu);
        maxHitLabel->setLayoutDirection(Qt::LeftToRight);
        maxHitLabel->setAlignment(Qt::AlignCenter);
        maxHitSplitter->addWidget(maxHitLabel);
        maxHitSlider = new QSlider(maxHitSplitter);
        maxHitSlider->setObjectName(QStringLiteral("maxHitSlider"));
        maxHitSlider->setMinimum(0);
        maxHitSlider->setMaximum(20);
        maxHitSlider->setSingleStep(1);
        maxHitSlider->setPageStep(2);
        maxHitSlider->setValue(0);
        maxHitSlider->setSliderPosition(0);
        maxHitSlider->setOrientation(Qt::Horizontal);
        maxHitSlider->setTickPosition(QSlider::TicksBelow);
        maxHitSlider->setTickInterval(10);
        maxHitSplitter->addWidget(maxHitSlider);

        thresholdsGridLayout->addWidget(maxHitSplitter, 1, 1, 1, 1);

        maxAvoidanceSplitter = new QSplitter(layoutWidget);
        maxAvoidanceSplitter->setObjectName(QStringLiteral("maxAvoidanceSplitter"));
        maxAvoidanceSplitter->setOrientation(Qt::Vertical);
        maxAvoidanceLabel = new QLabel(maxAvoidanceSplitter);
        maxAvoidanceLabel->setObjectName(QStringLiteral("maxAvoidanceLabel"));
        maxAvoidanceLabel->setContextMenuPolicy(Qt::NoContextMenu);
        maxAvoidanceLabel->setLayoutDirection(Qt::LeftToRight);
        maxAvoidanceLabel->setAlignment(Qt::AlignCenter);
        maxAvoidanceSplitter->addWidget(maxAvoidanceLabel);
        maxAvoidanceSlider = new QSlider(maxAvoidanceSplitter);
        maxAvoidanceSlider->setObjectName(QStringLiteral("maxAvoidanceSlider"));
        maxAvoidanceSlider->setMinimum(0);
        maxAvoidanceSlider->setMaximum(20);
        maxAvoidanceSlider->setSingleStep(1);
        maxAvoidanceSlider->setPageStep(2);
        maxAvoidanceSlider->setValue(0);
        maxAvoidanceSlider->setSliderPosition(0);
        maxAvoidanceSlider->setOrientation(Qt::Horizontal);
        maxAvoidanceSlider->setTickPosition(QSlider::TicksBelow);
        maxAvoidanceSlider->setTickInterval(10);
        maxAvoidanceSplitter->addWidget(maxAvoidanceSlider);

        thresholdsGridLayout->addWidget(maxAvoidanceSplitter, 0, 1, 1, 1);

        minAvoidanceSplitter = new QSplitter(layoutWidget);
        minAvoidanceSplitter->setObjectName(QStringLiteral("minAvoidanceSplitter"));
        minAvoidanceSplitter->setOrientation(Qt::Vertical);
        minAvoidanceLabel = new QLabel(minAvoidanceSplitter);
        minAvoidanceLabel->setObjectName(QStringLiteral("minAvoidanceLabel"));
        minAvoidanceLabel->setContextMenuPolicy(Qt::NoContextMenu);
        minAvoidanceLabel->setLayoutDirection(Qt::LeftToRight);
        minAvoidanceLabel->setAlignment(Qt::AlignCenter);
        minAvoidanceSplitter->addWidget(minAvoidanceLabel);
        minAvoidanceSlider = new QSlider(minAvoidanceSplitter);
        minAvoidanceSlider->setObjectName(QStringLiteral("minAvoidanceSlider"));
        minAvoidanceSlider->setMinimum(0);
        minAvoidanceSlider->setMaximum(20);
        minAvoidanceSlider->setSingleStep(1);
        minAvoidanceSlider->setPageStep(2);
        minAvoidanceSlider->setSliderPosition(0);
        minAvoidanceSlider->setOrientation(Qt::Horizontal);
        minAvoidanceSlider->setTickPosition(QSlider::TicksBelow);
        minAvoidanceSlider->setTickInterval(10);
        minAvoidanceSplitter->addWidget(minAvoidanceSlider);

        thresholdsGridLayout->addWidget(minAvoidanceSplitter, 0, 0, 1, 1);

        minHitSplitter = new QSplitter(layoutWidget);
        minHitSplitter->setObjectName(QStringLiteral("minHitSplitter"));
        minHitSplitter->setOrientation(Qt::Vertical);
        minHitLabel = new QLabel(minHitSplitter);
        minHitLabel->setObjectName(QStringLiteral("minHitLabel"));
        minHitLabel->setContextMenuPolicy(Qt::NoContextMenu);
        minHitLabel->setLayoutDirection(Qt::LeftToRight);
        minHitLabel->setAlignment(Qt::AlignCenter);
        minHitSplitter->addWidget(minHitLabel);
        minHitSlider = new QSlider(minHitSplitter);
        minHitSlider->setObjectName(QStringLiteral("minHitSlider"));
        minHitSlider->setMinimum(0);
        minHitSlider->setMaximum(20);
        minHitSlider->setSingleStep(1);
        minHitSlider->setPageStep(2);
        minHitSlider->setValue(0);
        minHitSlider->setSliderPosition(0);
        minHitSlider->setOrientation(Qt::Horizontal);
        minHitSlider->setTickPosition(QSlider::TicksBelow);
        minHitSlider->setTickInterval(10);
        minHitSplitter->addWidget(minHitSlider);

        thresholdsGridLayout->addWidget(minHitSplitter, 1, 0, 1, 1);

        maxCritSplitter = new QSplitter(layoutWidget);
        maxCritSplitter->setObjectName(QStringLiteral("maxCritSplitter"));
        maxCritSplitter->setOrientation(Qt::Vertical);
        maxCritLabel = new QLabel(maxCritSplitter);
        maxCritLabel->setObjectName(QStringLiteral("maxCritLabel"));
        maxCritLabel->setContextMenuPolicy(Qt::NoContextMenu);
        maxCritLabel->setLayoutDirection(Qt::LeftToRight);
        maxCritLabel->setAlignment(Qt::AlignCenter);
        maxCritSplitter->addWidget(maxCritLabel);
        maxCritSlider = new QSlider(maxCritSplitter);
        maxCritSlider->setObjectName(QStringLiteral("maxCritSlider"));
        maxCritSlider->setMinimum(0);
        maxCritSlider->setMaximum(20);
        maxCritSlider->setSingleStep(1);
        maxCritSlider->setPageStep(2);
        maxCritSlider->setValue(1);
        maxCritSlider->setSliderPosition(1);
        maxCritSlider->setOrientation(Qt::Horizontal);
        maxCritSlider->setTickPosition(QSlider::TicksBelow);
        maxCritSlider->setTickInterval(10);
        maxCritSplitter->addWidget(maxCritSlider);

        thresholdsGridLayout->addWidget(maxCritSplitter, 2, 1, 1, 1);


        gridLayout->addLayout(thresholdsGridLayout, 1, 0, 1, 2);

        depthSplitter = new QSplitter(layoutWidget);
        depthSplitter->setObjectName(QStringLiteral("depthSplitter"));
        depthSplitter->setOrientation(Qt::Vertical);
        depthLabel = new QLabel(depthSplitter);
        depthLabel->setObjectName(QStringLiteral("depthLabel"));
        depthLabel->setContextMenuPolicy(Qt::NoContextMenu);
        depthLabel->setLayoutDirection(Qt::LeftToRight);
        depthLabel->setAlignment(Qt::AlignCenter);
        depthSplitter->addWidget(depthLabel);
        depthSlider = new QSlider(depthSplitter);
        depthSlider->setObjectName(QStringLiteral("depthSlider"));
        depthSlider->setMinimum(1);
        depthSlider->setMaximum(5);
        depthSlider->setSingleStep(1);
        depthSlider->setPageStep(2);
        depthSlider->setValue(3);
        depthSlider->setSliderPosition(3);
        depthSlider->setOrientation(Qt::Horizontal);
        depthSlider->setTickPosition(QSlider::TicksBelow);
        depthSlider->setTickInterval(1);
        depthSplitter->addWidget(depthSlider);
        groupBox = new QGroupBox(depthSplitter);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QFont font2;
        font2.setPointSize(10);
        groupBox->setFont(font2);
        heuristicGridLayout = new QGridLayout(groupBox);
        heuristicGridLayout->setObjectName(QStringLiteral("heuristicGridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        currentHealthRadioButton = new QRadioButton(groupBox);
        currentHealthRadioButton->setObjectName(QStringLiteral("currentHealthRadioButton"));
        currentHealthRadioButton->setChecked(true);

        verticalLayout->addWidget(currentHealthRadioButton);

        fixedHealthRadioButton = new QRadioButton(groupBox);
        fixedHealthRadioButton->setObjectName(QStringLiteral("fixedHealthRadioButton"));

        verticalLayout->addWidget(fixedHealthRadioButton);


        heuristicGridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        depthSplitter->addWidget(groupBox);

        gridLayout->addWidget(depthSplitter, 3, 0, 1, 1);

        checkBoxSplitter = new QSplitter(layoutWidget);
        checkBoxSplitter->setObjectName(QStringLiteral("checkBoxSplitter"));
        checkBoxSplitter->setOrientation(Qt::Vertical);
        aeroCheckBox = new QCheckBox(checkBoxSplitter);
        aeroCheckBox->setObjectName(QStringLiteral("aeroCheckBox"));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Shell Dlg 2"));
        font3.setPointSize(10);
        aeroCheckBox->setFont(font3);
        aeroCheckBox->setChecked(true);
        checkBoxSplitter->addWidget(aeroCheckBox);
        tieCheckBox = new QCheckBox(checkBoxSplitter);
        tieCheckBox->setObjectName(QStringLiteral("tieCheckBox"));
        tieCheckBox->setFont(font3);
        tieCheckBox->setChecked(true);
        checkBoxSplitter->addWidget(tieCheckBox);
        passCheckBox = new QCheckBox(checkBoxSplitter);
        passCheckBox->setObjectName(QStringLiteral("passCheckBox"));
        passCheckBox->setFont(font3);
        passCheckBox->setChecked(false);
        checkBoxSplitter->addWidget(passCheckBox);
        PvPCheckBox = new QCheckBox(checkBoxSplitter);
        PvPCheckBox->setObjectName(QStringLiteral("PvPCheckBox"));
        PvPCheckBox->setFont(font3);
        PvPCheckBox->setChecked(true);
        checkBoxSplitter->addWidget(PvPCheckBox);

        gridLayout->addWidget(checkBoxSplitter, 3, 1, 1, 1);

#ifndef QT_NO_SHORTCUT
        minChanceOnHitLabel->setBuddy(minChanceOnHitSlider);
        maxChanceOnHitLabel->setBuddy(maxChanceOnHitSlider);
        minCritLabel->setBuddy(minCritSlider);
        maxHitLabel->setBuddy(maxHitSlider);
        maxAvoidanceLabel->setBuddy(maxAvoidanceSlider);
        minAvoidanceLabel->setBuddy(minAvoidanceSlider);
        minHitLabel->setBuddy(minHitSlider);
        maxCritLabel->setBuddy(maxCritSlider);
        depthLabel->setBuddy(maxCritSlider);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(minAvoidanceSlider, maxAvoidanceSlider);
        QWidget::setTabOrder(maxAvoidanceSlider, minHitSlider);
        QWidget::setTabOrder(minHitSlider, maxHitSlider);
        QWidget::setTabOrder(maxHitSlider, minCritSlider);
        QWidget::setTabOrder(minCritSlider, maxCritSlider);
        QWidget::setTabOrder(maxCritSlider, minChanceOnHitSlider);
        QWidget::setTabOrder(minChanceOnHitSlider, maxChanceOnHitSlider);
        QWidget::setTabOrder(maxChanceOnHitSlider, aeroCheckBox);
        QWidget::setTabOrder(aeroCheckBox, tieCheckBox);
        QWidget::setTabOrder(tieCheckBox, passCheckBox);
        QWidget::setTabOrder(passCheckBox, PvPCheckBox);
        QWidget::setTabOrder(PvPCheckBox, buttonBox);

        retranslateUi(PreferencesDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), PreferencesDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0));
        thresholdLabel->setText(QApplication::translate("PreferencesDialog", "Thresholds", 0));
        optionsLabel->setText(QApplication::translate("PreferencesDialog", "Options", 0));
        minChanceOnHitLabel->setText(QApplication::translate("PreferencesDialog", "Minimum Chance On Hit %", 0));
        maxChanceOnHitLabel->setText(QApplication::translate("PreferencesDialog", "Maximum Chance On Hit %", 0));
        minCritLabel->setText(QApplication::translate("PreferencesDialog", "Minimum Critical Strike %", 0));
        maxHitLabel->setText(QApplication::translate("PreferencesDialog", "Maximum Hit %", 0));
        maxAvoidanceLabel->setText(QApplication::translate("PreferencesDialog", "Maximum Avoidance %", 0));
        minAvoidanceLabel->setText(QApplication::translate("PreferencesDialog", "Minimum Avoidance %", 0));
        minHitLabel->setText(QApplication::translate("PreferencesDialog", "Minimum Hit %", 0));
        maxCritLabel->setText(QApplication::translate("PreferencesDialog", "Maximum Critical Strike %", 0));
        depthLabel->setText(QApplication::translate("PreferencesDialog", "Turns To Look Ahead (1-5)", 0));
        groupBox->setTitle(QApplication::translate("PreferencesDialog", "Heuristics", 0));
        currentHealthRadioButton->setText(QApplication::translate("PreferencesDialog", "Use Current Health", 0));
        fixedHealthRadioButton->setText(QApplication::translate("PreferencesDialog", "Use Fixed Health", 0));
        aeroCheckBox->setText(QApplication::translate("PreferencesDialog", "Disables Aero (Increases Performance)", 0));
        tieCheckBox->setText(QApplication::translate("PreferencesDialog", "Random When Speeds Are Equal", 0));
        passCheckBox->setText(QApplication::translate("PreferencesDialog", "Consider Passing As A Move", 0));
        PvPCheckBox->setText(QApplication::translate("PreferencesDialog", "Enable PvP Queuing", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCES_H
