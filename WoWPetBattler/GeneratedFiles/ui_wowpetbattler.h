/********************************************************************************
** Form generated from reading UI file 'wowpetbattler.ui'
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WoWPetBattlerClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTextBrowser *outputBrowser;
    QLabel *statusLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WoWPetBattlerClass)
    {
        if (WoWPetBattlerClass->objectName().isEmpty())
            WoWPetBattlerClass->setObjectName(QStringLiteral("WoWPetBattlerClass"));
        WoWPetBattlerClass->resize(461, 545);
        centralWidget = new QWidget(WoWPetBattlerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 40, 71, 71));
        QIcon icon;
        icon.addFile(QStringLiteral(":/WoWPetBattler/Play Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(48, 48));
        outputBrowser = new QTextBrowser(centralWidget);
        outputBrowser->setObjectName(QStringLiteral("outputBrowser"));
        outputBrowser->setGeometry(QRect(20, 160, 421, 331));
        statusLabel = new QLabel(centralWidget);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setGeometry(QRect(180, 50, 261, 51));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        statusLabel->setFont(font);
        WoWPetBattlerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WoWPetBattlerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 461, 21));
        WoWPetBattlerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WoWPetBattlerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WoWPetBattlerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        WoWPetBattlerClass->insertToolBarBreak(mainToolBar);
        statusBar = new QStatusBar(WoWPetBattlerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WoWPetBattlerClass->setStatusBar(statusBar);

        retranslateUi(WoWPetBattlerClass);

        QMetaObject::connectSlotsByName(WoWPetBattlerClass);
    } // setupUi

    void retranslateUi(QMainWindow *WoWPetBattlerClass)
    {
        WoWPetBattlerClass->setWindowTitle(QApplication::translate("WoWPetBattlerClass", "WoWPetBattler", 0));
        statusLabel->setText(QApplication::translate("WoWPetBattlerClass", "Finding Addon", 0));
    } // retranslateUi

};

namespace Ui {
    class WoWPetBattlerClass: public Ui_WoWPetBattlerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WOWPETBATTLER_H
