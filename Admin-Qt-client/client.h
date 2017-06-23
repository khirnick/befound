#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

// Класс клиента, синглтон
// он подключается к удаленому серверу, формирует запросы
class Client : public QObject
{
    Q_OBJECT

    QTcpSocket m_socket;
    QHostAddress m_adress;
    quint16 m_port;

private:
    Client();
    Client( const Client&);
    Client& operator=( Client& );

    inline void connectToHost();
public:
    static Client& getInstance();

    void connectToHost(QHostAddress adress, quint16 port);

public slots:
    void slotConnected();
    void slotReadyRead();
    void slotError();

signals:
    void signalConnectToHost(QString msg);
    void signalConnected(QString msg);
    void signalReadyRead(QString msg);
    void signalError(QString msg);
};

#endif // CLIENT_H
