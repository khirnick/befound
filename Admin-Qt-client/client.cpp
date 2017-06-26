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
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotSocketError(QAbstractSocket::SocketError)));

    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(timeout()));
}

inline void Client::connectToHost()
{
    QString msg = QString("Подключение к ") + m_adress + ":" + m_port;
    QMessageLogger().info() << msg;
    emit signalConnectToHost(msg);
    m_socket.connectToHost(m_adress, m_port);
}

void Client::error(QString msg)
{
    QMessageLogger().warning() << msg;
    emit signalError(msg);
    reconnect();
}

void Client::timeout()
{
    m_timer->stop();
    error("Ошибка: Таймаут.");
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
        connect(request, SIGNAL(signalError(QString)), this, SLOT(error(QString)));
        m_socket.write(request.execute());
        if (!m_timer->isActive())
            m_timer->start(Globals::timeout);
    } else {
        error("Ошибка! Нет подключения.");
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
    if (m_socket.bytesAvailable() >= m_sendedRequests.head()->answerBlockSize()) {
        m_timer->start(Globals::timeout);
        Query *request = m_sendedRequests.dequeue();
        QByteArray answer = m_socket.read(request->answerBlockSize());
        request->onAnswer(answer);
        delete request;
    }
}

void Client::slotSocketError(QAbstractSocket::SocketError err)
{
    QString strError =
            "Ошибка: " + (err == QAbstractSocket::HostNotFoundError ?
                             "Хост не был найден." :
                             err == QAbstractSocket::RemoteHostClosedError ?
                                 "Удаленный хост закрыт." :
                                 err == QAbstractSocket::ConnectionRefusedError ?
                                     "Пропало соединение." :
                                     QString(m_socket->errorString())
                                     );
    error(strError);
}
