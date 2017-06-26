#ifndef QUERY_H
#define QUERY_H

#include <QObject>


enum RequestType {
    GetOnlineUsers = 0
};


// Абстрактный класс запроса
class Query : public QObject
{
    Q_OBJECT

public:
    explicit Query();
    virtual ~Query() = 0;

    virtual QByteArray execute() = 0;
    virtual quint64 answerBlockSize() = 0;
    virtual void onAnswer(QByteArray answer) = 0;

signals:
    void signalError(QString msg);
};


#endif // QUERY_H
