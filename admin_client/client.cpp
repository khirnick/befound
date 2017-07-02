#include "client.h"

#include <QMessageLogger>
#include <QSettings>
#include "globals.h"

Client &Client::getInstance()
{
    static Client  instance;
    return instance;
}

Client::Client()
{
    QSettings settings;
    connectToHost(settings.value("server/ip", Globals::defaultIP).toString(),
                  settings.value("server/port", Globals::defaultPort).toInt());
    connect(&m_socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(&m_socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotSocketError(QAbstractSocket::SocketError)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

inline void Client::connectToHost()
{
    QString msg = QString("Подключение к ") + m_adress + ":" + m_port;
    QMessageLogger().info() << msg;
    emit signalConnectToHost(msg);

    m_nextBlockSize = 0;

    m_socket.connectToHost(m_adress, m_port);
}

void Client::error(QString msg)
{
    QMessageLogger().warning() << msg;
    emit signalError(msg);
    m_socket.close();
    //reconnect();
}

void Client::timeout()
{
    m_timer->stop();
    error("Ошибка: Таймаут.");
    reconnect();
}

void Client::connectToHost(QString adress, quint16 port)
{
    m_adress = adress;
    m_port = port;
    reconnect();
}

void Client::reconnect()
{
    m_socket.close();
    for (QQueue<Query*>::iterator i = m_sendedRequests.begin(); i != m_sendedRequests.end(); ++i)
        delete *i;
    m_sendedRequests.clear();
    connectToHost();
}

bool Client::sendRequest(Query *request)
{
    if (m_socket.isValid()) {
        m_sendedRequests.enqueue(request);        
        m_socket.write(request->execute());
        if (!m_timer->isActive())
            m_timer->start(Globals::timeout);
        return 1;
    } else {
        error("Ошибка! Нет подключения.");
        reconnect();
        return 0;
    }
}

void Client::slotConnected()
{
    QString msg = "Успешное подключение к " + m_adress + ":" + m_port;
    QMessageLogger().info() << msg;
    emit signalConnected(msg);
}

void Client::slotReadyRead()
{
    while (m_nextBlockSize == 0 && m_socket.bytesAvailable() >= sizeof(quint64) ||
           m_nextBlockSize > 0 && m_socket.bytesAvailable() >= m_nextBlockSize) {
        if (m_nextBlockSize == 0 && m_socket.bytesAvailable() >= sizeof(quint64)) {
            // Считываю размер ответа
            QByteArray answer = m_socket.read(sizeof(quint64));
            QDataStream in(&answer, QIODevice::ReadOnly);
            in >> m_nextBlockSize;
        }
        if (m_nextBlockSize > 0 && m_socket.bytesAvailable() >= m_nextBlockSize) {
            m_timer->start(Globals::timeout);
            Query *request = m_sendedRequests.dequeue();
            request->onAnswer(m_socket.read(m_nextBlockSize));
            delete request;
            m_nextBlockSize = 0;
        }
    }
}

void Client::slotSocketError(QAbstractSocket::SocketError err)
{
    QString strError =
            QString("Ошибка: ") + (err == QAbstractSocket::HostNotFoundError ?
                                       "Хост не был найден." :
                                       err == QAbstractSocket::RemoteHostClosedError ?
                                           "Удаленный хост закрыт." :
                                           err == QAbstractSocket::ConnectionRefusedError ?
                                               "Пропало соединение." :
                                               m_socket.errorString()
                                               );
    error(strError);
}
