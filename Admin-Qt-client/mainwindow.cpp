#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->usersTable->setModel(m_usersAtTaskModel = new UserTableModel);
    ui->alarmsTable->setModel(m_usersInAlarm = new UserTableModel);

    ui->map->setProjection(Marble::Mercator);
    ui->map->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");

    ////////////////////// test data ////////////////////////////////
    Users usersAtTask;
    UserData user;
    user[ID] = 1; user[FULL_NAME] = "КАВ"; user[PHONE] = 1234567890; user[STATUS] = 0; user[COORDS] = "123 123"; user[EMAIL] = "abc@mail.ru";
    usersAtTask.append(user); usersAtTask.append(user); usersAtTask.append(user);
    user[STATUS] = 1;
    usersAtTask.append(user);
    m_usersAtTaskModel->setUsers(usersAtTask);
    m_usersInAlarm->setUsers(usersAtTask);
    ////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}
