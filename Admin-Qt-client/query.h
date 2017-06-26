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

    virtual QByteArray execute() = 0;
    virtual void onAnswer(QByteArray answer) = 0;

signals:
    void signalError(QString msg);
    void authorisationFail(QString msg);
    void permisionDenied(QString msg);
};


class QueryGetOnlineUsers : public Query
{
    Q_OBJECT

public:
    explicit QueryGetOnlineUsers();
    ~QueryGetOnlineUsers();

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void onlineUsers(QList<Globals::User> users);
};


class QueryGetAllUsers : public Query
{
    Q_OBJECT

public:
    explicit QueryGetAllUsers();
    ~QueryGetAllUsers();

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void allUsers(QList<Globals::User> users);
};


class QueryGetUserTrack : public Query
{
    Q_OBJECT

    quint64 m_userID;

public:
    explicit QueryGetUserTrack(quint64 userID);
    ~QueryGetUserTrack();

    QByteArray execute();
    void onAnswer(QByteArray answer);

signals:
    void signalError(QString msg);
    void userTrack(QList<Globals::Coords> track);
};


#endif // QUERY_H
