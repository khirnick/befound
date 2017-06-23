#include "client.h"

#include <QMessageLogger>
#include "globals.h"

Client &Client::getInstance()
{
    static Singleton  instance;
    return instance;
}

Client::Client()
{
    connectToHost(Globals::defaultIP, Globals::defaultPort);
    connect(&m_socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(&m_socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

inline void Client::connectToHost()
{
    QString msg = "Подключение к " + m_adress + ":" + m_port;
    QMessageLogger().info(msg);
    emit signalConnectToHost(msg);
    m_socket.connectToHost(m_adress, m_port);
}

void Client::connectToHost(QHostAddress adress, quint16 port)
{
    m_adress = adress;
    m_port = port;
    connectToHost();
}

void Client::slotConnected()
{
    QString msg = "Успешное подключение к " + m_adress + ":" + m_port;
    QMessageLogger().info(msg);
    emit signalConnected(msg);
}

void Client::slotReadyRead()
{

}

void Client::slotError()
{

}
