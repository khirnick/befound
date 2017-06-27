#ifndef QUERY_H
#define QUERY_H

#include <QObject>
#include <QList>
#include <QDataStream>
#include "globals.h"


enum RequestType {
    GetOnlineUsers = 0,
    GetAllUsers,
    GetUserTrack,
    Authorisation,
    NewUser,
    SetUser,
    NewButton,
    SetButton,
    DeleteButton,
    UseButton
};

enum answerType {
    OK = 0,
    Error,
    AuthorisationFail,
    PermisionDenied
};


// Абстрактный класс запроса
class Query : public QObject
{
    Q_OBJECT

protected:
    bool checkAnswerType(QDataStream &in, QString queryName = QString());

public:
    explicit Query();
    virtual ~Query() {}

    // отправка данных серверу
    virtual QByteArray execute() = 0;
    // чтение ответа от сервера
    virtual void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void authorisationFail(QString msg);
    void permisionDenied(QString msg);
    void onSuccess();
};


class QueryGetOnlineUsers : public Query
{
    Q_OBJECT

public:
    explicit QueryGetOnlineUsers();

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void onSuccess(QList<Globals::User> users);
};


class QueryGetAllUsers : public Query
{
    Q_OBJECT

public:
    explicit QueryGetAllUsers();

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void onSuccess(QList<Globals::User> users);
};


class QueryGetUserTrack : public Query
{
    Q_OBJECT

    quint64 m_userID;

public:
    explicit QueryGetUserTrack(quint64 userID);

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void onSuccess(QList<Globals::Coords> track);
};


class QueryAuth : public Query
{
    Q_OBJECT

protected:
    QByteArray getAuthParams();
    inline QByteArray getAuthParamsWithSize();

public:
    explicit QueryAuth();

    virtual QByteArray execute();

signals:
    void signalError(QString msg);
};

#endif // QUERY_H
