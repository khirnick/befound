/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "map.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *newUser;
    QAction *findUser;
    QAction *newButton;
    QAction *allButtons;
    QAction *auth;
    QAction *settings;
    QAction *exit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter_2;
    QSplitter *splitter;
    Map *map;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_7;
    QTableView *alarmsTable;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_6;
    QTableView *usersTable;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(708, 618);
        newUser = new QAction(MainWindow);
        newUser->setObjectName(QStringLiteral("newUser"));
        findUser = new QAction(MainWindow);
        findUser->setObjectName(QStringLiteral("findUser"));
        newButton = new QAction(MainWindow);
        newButton->setObjectName(QStringLiteral("newButton"));
        allButtons = new QAction(MainWindow);
        allButtons->setObjectName(QStringLiteral("allButtons"));
        auth = new QAction(MainWindow);
        auth->setObjectName(QStringLiteral("auth"));
        settings = new QAction(MainWindow);
        settings->setObjectName(QStringLiteral("settings"));
        exit = new QAction(MainWindow);
        exit->setObjectName(QStringLiteral("exit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        map = new Map(splitter);
        map->setObjectName(QStringLiteral("map"));
        map->setMinimumSize(QSize(400, 400));
        splitter->addWidget(map);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        verticalLayout_7 = new QVBoxLayout(groupBox_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        alarmsTable = new QTableView(groupBox_2);
        alarmsTable->setObjectName(QStringLiteral("alarmsTable"));
        alarmsTable->setAlternatingRowColors(true);
        alarmsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        alarmsTable->setSortingEnabled(true);
        alarmsTable->horizontalHeader()->setCascadingSectionResizes(true);
        alarmsTable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout_7->addWidget(alarmsTable);

        splitter->addWidget(groupBox_2);
        splitter_2->addWidget(splitter);
        groupBox = new QGroupBox(splitter_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_6 = new QVBoxLayout(groupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        usersTable = new QTableView(groupBox);
        usersTable->setObjectName(QStringLiteral("usersTable"));
        usersTable->setAlternatingRowColors(true);
        usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        usersTable->setSortingEnabled(true);
        usersTable->horizontalHeader()->setCascadingSectionResizes(true);
        usersTable->verticalHeader()->setProperty("showSortIndicator", QVariant(true));

        verticalLayout_6->addWidget(usersTable);

        splitter_2->addWidget(groupBox);

        verticalLayout->addWidget(splitter_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 708, 24));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menu->addAction(auth);
        menu->addAction(settings);
        menu->addSeparator();
        menu->addAction(exit);
        menu_2->addAction(newUser);
        menu_2->addAction(findUser);
        menu_3->addAction(newButton);
        menu_3->addAction(allButtons);

        retranslateUi(MainWindow);
        QObject::connect(exit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "BeFOUND - Admin", Q_NULLPTR));
        newUser->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\321\213\320\271", Q_NULLPTR));
        findUser->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", Q_NULLPTR));
        newButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        allButtons->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265 \320\272\320\275\320\276\320\277\320\272\320\270", Q_NULLPTR));
        auth->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\321\200\320\270\320\267\320\260\321\206\320\270\321\217", Q_NULLPTR));
        settings->setText(QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", Q_NULLPTR));
        exit->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264 \320\270\320\267 \320\277\321\200\320\276\320\263\320\260\320\274\320\274\321\213", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\320\242\321\200\320\265\320\262\320\276\320\263\320\260", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270 \320\262 \320\277\320\276\321\205\320\276\320\264\320\265", Q_NULLPTR));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\237\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\320\270", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("MainWindow", "\320\242\321\200\320\265\320\262\320\276\320\266\320\275\321\213\320\265 \320\272\320\275\320\276\320\277\320\272\320\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
