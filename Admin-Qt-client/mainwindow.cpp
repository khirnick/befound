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

    m_settingsWindow = new SettingsWindow(this);
    QObject::connect(ui->settings, SIGNAL(triggered(bool)), this, SLOT(settingsWindowShow()));

    ////////////////////// test data ////////////////////////////////
    UserTableModel::Users usersAtTask;
    UserTableModel::UserData user;
    user[UserTableModel::ID] = 1; user[UserTableModel::FULL_NAME] = "КАВ"; user[UserTableModel::PHONE] = 1234567890; user[UserTableModel::STATUS] = 0; user[UserTableModel::COORDS] = "123 123"; user[UserTableModel::EMAIL] = "abc@mail.ru";
    usersAtTask.append(user); usersAtTask.append(user); usersAtTask.append(user);
    user[UserTableModel::STATUS] = 1;
    usersAtTask.append(user); usersAtTask.append(user);
    m_usersAtTaskModel->setUsers(usersAtTask);
    m_usersInAlarm->setUsers(usersAtTask);
    ////////////////////////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingsWindowShow()
{
    m_settingsWindow->show();
}
