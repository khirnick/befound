#include "client.h"

#include <QMessageLogger>
#include "globals.h"

Client &Client::getInstance()
{
    static Client  instance;
    return instance;
}

Client::Client()
{
    m_queriesCount = 0;

    connectToHost(Globals::defaultIP, Globals::defaultPort);
    connect(&m_socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(&m_socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));
}

inline void Client::connectToHost()
{
    m_socket.close();
    QString msg = "Подключение к " + m_adress + ":" + m_port;
    QMessageLogger().info(msg);
    emit signalConnectToHost(msg);
    m_socket.connectToHost(m_adress, m_port);
}

quint16 Client::newConnection()
{
    if (!m_socket.isValid()) {
        emit signalError("Ошибка! Нет подключения.");
        connectToHost();
        return 0;
    }
    if (++m_queriesCount == 0) ++m_queriesCount;    // Увеличиваю счетчик и проверяю на ноль
    return m_queriesCount;
}

void Client::connectToHost(QHostAddress adress, quint16 port)
{
    m_adress = adress;
    m_port = port;
    connectToHost();
}

void Client::queryToGetOnlineUsers()
{
    quint16 queryID;
    if (queryID = newConnection()) {

    }
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
