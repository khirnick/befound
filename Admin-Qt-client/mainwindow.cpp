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
    QObject::connect(&auth, SIGNAL(signalAuth()), this, SLOT(onAuth()));
    QObject::connect(&auth, SIGNAL(signalLoggout()), this, SLOT(onLoggout()));
    QObject::connect(&client, SIGNAL(signalAuth(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalLoggout(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalAuthorisationFail(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalPermisionDenied(QString)), this, SLOT(printInfo(QString)));
    onLoggout();

    setSettings();

    ////////////////////// test data ////////////////////////////////
#ifdef _DEBUG
    QList<Globals::User> users;
    Globals::User user1 { 1, "Кирьяненко", "Александр", "Владиславович", "8(123)123-12-12", "kiryanenkoav@mail.ru", Globals::UserStatus::Ok, 55.766105, 37.688466 };
    Globals::User user2 { 2, "Хирный", "Никита", "Сергеевич", "8(555)333-22-11", "khirnich@mail.ru", Globals::UserStatus::Ok, 55.771485, 37.680707 };
    Globals::User user3 { 3, "Куклина", "Нина", "", "8(666)788-66-77", "khirnich@mail.ru", Globals::UserStatus::Alarm, 55.762762, 37.689767 };
    Globals::User user4 { 4, "Колотовкин", "Максим", "", "8(552)555-35-35", "maxpro@mail.ru", Globals::UserStatus::Ok, 55.772091, 37.696176 };
    users << user1 << user2 << user3 << user4;
    updateUsers(users);

    m_selectedUserID = 1;
    QList<Globals::Coords> track;
    Globals::Coords c1 { 55.770898, 37.686074 }, c2 { 55.770645, 37.689636 };
    Globals::Coords c3 { 55.770796, 37.690449 }, c4 { 55.769043, 37.691873 };
    Globals::Coords c5 { 55.767790, 37.690591 }, c6 { 55.766105, 37.688466 };
    track << c1 << c2 << c3 << c4 << c5 << c6;
    updateUserTrack(track);
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

void MainWindow::onAuth()
{
    ui->newUser->setEnabled(true);
    ui->findUser->setEnabled(true);
    ui->newButton->setEnabled(true);
    ui->allButtons->setEnabled(true);
}

void MainWindow::onLoggout()
{
    ui->newUser->setDisabled(true);
    ui->findUser->setDisabled(true);
    ui->newButton->setDisabled(true);
    ui->allButtons->setDisabled(true);
}
