/********************************************************************************
** Form generated from reading UI file 'WoWPetBattler.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WOWPETBATTLER_H
#define UI_WOWPETBATTLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WoWPetBattlerMainWindow
{
public:
    QAction *actionPreferences;
    QAction *actionQuit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *playButton;
    QLabel *statusLabel;
    QTextBrowser *outputBrowser;
    QMenuBar *menuBar;
    QMenu *menuSettings;
    QMenu *menuFile;

    void setupUi(QMainWindow *WoWPetBattlerMainWindow)
    {
        if (WoWPetBattlerMainWindow->objectName().isEmpty())
            WoWPetBattlerMainWindow->setObjectName(QStringLiteral("WoWPetBattlerMainWindow"));
        WoWPetBattlerMainWindow->resize(460, 545);
        WoWPetBattlerMainWindow->setMinimumSize(QSize(460, 545));
        WoWPetBattlerMainWindow->setBaseSize(QSize(460, 545));
        actionPreferences = new QAction(WoWPetBattlerMainWindow);
        actionPreferences->setObjectName(QStringLiteral("actionPreferences"));
        actionQuit = new QAction(WoWPetBattlerMainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(WoWPetBattlerMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(0, -1, -1, -1);
        playButton = new QPushButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy);
        playButton->setMinimumSize(QSize(75, 75));
        playButton->setMaximumSize(QSize(75, 75));
        playButton->setSizeIncrement(QSize(0, 0));
        playButton->setBaseSize(QSize(75, 75));
        QIcon icon;
        icon.addFile(QStringLiteral(":/WoWPetBattler/Resources/Play Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral("Resources/Stop Icon.png"), QSize(), QIcon::Normal, QIcon::On);
        playButton->setIcon(icon);
        playButton->setIconSize(QSize(48, 48));
        playButton->setCheckable(true);
        playButton->setChecked(false);

        horizontalLayout->addWidget(playButton);

        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        statusLabel->setFont(font);

        horizontalLayout->addWidget(statusLabel);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        outputBrowser = new QTextBrowser(centralWidget);
        outputBrowser->setObjectName(QStringLiteral("outputBrowser"));

        gridLayout->addWidget(outputBrowser, 1, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        WoWPetBattlerMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WoWPetBattlerMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 460, 21));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        WoWPetBattlerMainWindow->setMenuBar(menuBar);
        QWidget::setTabOrder(playButton, outputBrowser);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuSettings->addAction(actionPreferences);
        menuFile->addAction(actionQuit);

        retranslateUi(WoWPetBattlerMainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), WoWPetBattlerMainWindow, SLOT(deleteLater()));

        QMetaObject::connectSlotsByName(WoWPetBattlerMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WoWPetBattlerMainWindow)
    {
        WoWPetBattlerMainWindow->setWindowTitle(QApplication::translate("WoWPetBattlerMainWindow", "WoW Pet Battler", 0));
        actionPreferences->setText(QApplication::translate("WoWPetBattlerMainWindow", "Preferences...", 0));
        actionQuit->setText(QApplication::translate("WoWPetBattlerMainWindow", "Quit", 0));
        statusLabel->setText(QApplication::translate("WoWPetBattlerMainWindow", "Not Running", 0));
        menuSettings->setTitle(QApplication::translate("WoWPetBattlerMainWindow", "Settings", 0));
        menuFile->setTitle(QApplication::translate("WoWPetBattlerMainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class WoWPetBattlerMainWindow: public Ui_WoWPetBattlerMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOWPETBATTLER_H
