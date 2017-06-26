#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include <QSettings>
#include <marble/GeoPainter.h>
#include <marble/GeoDataDocument.h>
#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataLineString.h>
#include <marble/GeoDataTreeModel.h>
#include <marble/MarbleModel.h>
#include "query.h"
#include "client.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->usersTable->setModel(m_usersAtTaskModel = new UserTableModel);
    ui->alarmsTable->setModel(m_usersInAlarm = new UserTableModel);

    ui->map->setProjection(Marble::Mercator);
    ui->map->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    setMapCenter(Globals::baseLongitude, Globals::baseLatitude);

    m_geoDataDocument = new Marble::GeoDataDocument;
    // Add the document to MarbleWidget's tree model
    ui->map->model()->treeModel()->addDocument(m_geoDataDocument);

    m_settingsWindow = new SettingsWindow(this);
    QObject::connect(ui->settings, SIGNAL(triggered(bool)), this, SLOT(settingsWindowShow()));
    QObject::connect(ui->settings, SIGNAL(signalAccept()), this, SLOT(setSettings()));

    m_timer = new QTimer(this);
    QObject::connect(m_timer, SIGNAL(timeout()), this, SLOT(sendRequest()));

    Client &client = Client::getInstance();
    QObject::connect(&client, SIGNAL(signalConnectToHost(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalConnected(QString)), this, SLOT(printInfo(QString)));
    QObject::connect(&client, SIGNAL(signalError(QString)), this, SLOT(printInfo(QString)));

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
    QueryGetOnlineUsers *request = new QueryGetOnlineUsers;
    QObject::connect(request, SIGNAL(onlineUsers(QList<Globals::User>)), this, SLOT(updateUsers(QList<Globals::User>)));
    Client &client = Client::getInstance();
    client.sendRequest(request);
}

void MainWindow::updateUsers(QList<Globals::User> users)
{
    m_usersAtTaskModel->setUsers(users);
    drawUsersCoords(users);

    QList<Globals::User> usersInAlarm;
    for (QList<Globals::User>::iterator i = users.begin(); i != users.end(); ++i) {
        if (i->status == Globals::UserStatus::Alarm)
            usersInAlarm.append(*i);
    }
    m_usersInAlarm->setUsers(usersInAlarm);
}

void MainWindow::printInfo(QString msg)
{
    ui->statusBar->showMessage(msg, Globals::statusBarTimeout);
}

void MainWindow::drawUsersCoords(QList<Globals::User> &users)
{
    m_geoDataDocument->clear();
    for (QList<Globals::User>::iterator i = users.begin(); i != users.end(); ++i) {
        Marble::GeoDataPlacemark *user = new Marble::GeoDataPlacemark(i->last_name + " " + i->first_name);
        user->setId(QString() + i->id);
        user->setCoordinate( i->longitude, i->latitude, 0.0, Marble::GeoDataCoordinates::Degree );
        m_geoDataDocument->append( user );
    }
}

void MainWindow::setMapCenter(double lon, double lat)
{
    ui->map->centerOn(Marble::GeoDataCoordinates(lon, lat, 0, Marble::GeoDataCoordinates::Degree));
    ui->map->setZoom(Globals::baseZoom);
}
