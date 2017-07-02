#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QQueue>
#include <QTimer>
#include "query.h"

// Класс клиента, синглтон
// он подключается к удаленому серверу, формирует запросы
class Client : public QObject
{
    Q_OBJECT

    QTcpSocket m_socket;
    QString m_adress;
    quint16 m_port;
    QQueue<Query*> m_sendedRequests;
    QTimer *m_timer;
    quint64 m_nextBlockSize;

private:
    Client();
    Client( const Client&);
    Client& operator=( Client& );

    inline void connectToHost();
    inline quint16 newQuery();

public:
    static Client& getInstance();

    void connectToHost(QString adress, quint16 port);
    void reconnect();
    bool sendRequest(Query *request);

public slots:
    void slotConnected();
    void slotReadyRead();
    void slotSocketError(QAbstractSocket::SocketError err);
    void error(QString msg);
    void timeout();

signals:
    void signalConnectToHost(QString msg);
    void signalConnected(QString msg);
    void signalError(QString msg);
};

#endif // CLIENT_H
