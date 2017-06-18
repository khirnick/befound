#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList usersTableHeaders;
    usersTableHeaders << "id" << "ФИО" << "Тел." << "Статус" << "Последние координаты" << "email";
    ui->usersTable->setModel(m_usersAtTaskModel = new UserTableModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
