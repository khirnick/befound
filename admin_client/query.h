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
    GetUserData,
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

    virtual quint8 requestType() = 0;
    // отправка данных серверу
    virtual QByteArray execute();
    // чтение ответа от сервера
    virtual void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void authorisationFail(QString msg);
    void permisionDenied(QString msg);
    void onSuccess();
};


class QueryGetAllUsers : public Query
{
    Q_OBJECT

public:
    explicit QueryGetAllUsers();
    virtual quint8 requestType();
    void onAnswer(QByteArray answer);

signals:
    void onSuccess(QList<Globals::User> users);
};


class QueryGetOnlineUsers : public QueryGetAllUsers
{
    Q_OBJECT

public:
    explicit QueryGetOnlineUsers();
    quint8 requestType();
};


class QueryGetUserTrack : public Query
{
    Q_OBJECT

    quint64 m_userID;

public:
    explicit QueryGetUserTrack(quint64 userID);

    quint8 requestType();
    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void onSuccess(QList<Globals::Coords> track);
};


class QueryAuth : public Query
{
    Q_OBJECT

protected:
    inline QByteArray getAuthParams();
    inline QByteArray getAuthParamsWithSize();

public:
    explicit QueryAuth();

    virtual quint8 requestType();
    virtual QByteArray execute();
};

#endif // QUERY_H
