#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QSettings>
#include <QSharedPointer>
#include "query.h"
#include "client.h"
#include "auth.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), m_selectedUserID(0)
{
    ui->setupUi(this);
    ui->usersTable->setModel(m_usersAtTaskModel = new UserTableModel);
    ui->alarmsTable->setModel(m_usersInAlarm = new UserTableModel);
    QObject::connect(ui->usersTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectUser(QModelIndex)));
    QObject::connect(ui->alarmsTable, SIGNAL(clicked(QModelIndex)), this, SLOT(selectUser(QModelIndex)));

    m_settingsWindow = new SettingsWindow(this);
    QObject::connect(ui->settings, SIGNAL(triggered(bool)), this, SLOT(settingsWindowShow()));
    QObject::connect(ui->settings, SIGNAL(signalAccept()), this, SLOT(setSettings()));

    m_timer = new QTimer(this);
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(sendRequest()));

    Client &client = Client::getInstance();
    QObject::connect(&client, SIGNAL(signalConnectToHost(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalConnected(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalError(QString)), this, SLOT(printInfo(QString)));

    Auth &auth = Auth::getInstance();
    QObject::connect(ui->auth, SIGNAL(triggered()), &auth, SLOT(showForm()));

    setSettings();

    ////////////////////// test data ////////////////////////////////
#ifdef _DEBUG
    UserTableModel::Users usersAtTask;
    UserTableModel::UserData user;
    user[UserTableModel::ID] = 1; user[UserTableModel::FULL_NAME] = "КАВ"; user[UserTableModel::PHONE] = 1234567890; user[UserTableModel::STATUS] = 0; user[UserTableModel::COORDS] = "123 123"; user[UserTableModel::EMAIL] = "abc@mail.ru";
    usersAtTask.append(user); usersAtTask.append(user); usersAtTask.append(user);
    user[UserTableModel::STATUS] = 1;
    usersAtTask.append(user); usersAtTask.append(user);
    m_usersAtTaskModel->setUsers(usersAtTask);
    m_usersInAlarm->setUsers(usersAtTask);
#endif
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

void MainWindow::setSettings()
{
    QSettings settings;
    m_timer->start(settings.value("server/updatePeriod", Globals::defaultUpdatePeriod).toInt());

    Client &client = Client::getInstance();
    client.connectToHost(settings.value("server/ip", Globals::defaultIP).toString(),
                         settings.value("server/port", Globals::defaultPort).toInt());
}

void MainWindow::sendRequest()
{
    QueryGetOnlineUsers *requestOnlineUsers = new QueryGetOnlineUsers;
    QObject::connect(requestOnlineUsers, SIGNAL(onSuccess(QList<Globals::User>)), this, SLOT(updateUsers(QList<Globals::User>)));
    Client &client = Client::getInstance();
    client.sendRequest(requestOnlineUsers);

    if (m_selectedUserID) {
        QueryGetUserTrack *requestUserTrack = new QueryGetUserTrack(m_selectedUserID);
        QObject::connect(requestUserTrack, SIGNAL(onSuccess(QList<Globals::Coords>)),
                         this, SLOT(updateUserTrack(QList<Globals::Coords>)));
        Client &client = Client::getInstance();
        client.sendRequest(requestUserTrack);
    }
}

void MainWindow::updateUsers(QList<Globals::User> users)
{
    m_usersAtTaskModel->setUsers(users);
    ui->map->drawUsersCoords(users);

    QList<Globals::User> usersInAlarm;
    for (QList<Globals::User>::iterator i = users.begin(); i != users.end(); ++i) {
        if (i->status == Globals::UserStatus::Alarm)
            usersInAlarm.append(*i);
    }
    m_usersInAlarm->setUsers(usersInAlarm);
}

void MainWindow::updateUserTrack(QList<Globals::Coords> track)
{
    if (m_selectedUserID) {
        ui->map->setTrack(&track);
    }
}

void MainWindow::printInfo(QString msg)
{
    ui->statusBar->showMessage(msg, Globals::statusBarTimeout);
}

void MainWindow::selectUser(QModelIndex index)
{
    UserTableModel *model = (UserTableModel*) index.model();
    m_selectedUserID = model->getUserID(index.row());
    sendRequest();
}
