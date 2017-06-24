#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

// Класс клиента, синглтон
// он подключается к удаленому серверу, формирует запросы
class Client : public QObject
{
    Q_OBJECT

    static QTcpSocket m_socket;
    static QHostAddress m_adress;
    static quint16 m_port;
    static quint16 m_queriesCount;      // Счетчик запросов

private:
    Client();
    Client( const Client&);
    Client& operator=( Client& );

    inline void connectToHost();
    inline quint16 newConnection();
public:
    static Client& getInstance();

    void connectToHost(QHostAddress adress, quint16 port);

    // Запросы:
    void queryToGetOnlineUsers();
    void queryToGetAllUsers();
    void queryToGetUserTrack();

public slots:
    void slotConnected();
    void slotReadyRead();
    void slotError();

signals:
    void signalConnectToHost(QString msg);
    void signalConnected(QString msg);
    void signalError(QString msg);
};

#endif // CLIENT_H
