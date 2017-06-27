#include "query.h"

#include <QList>
#include "globals.h"
#include "client.h"
#include "auth.h"

bool Query::checkAnswerType(QDataStream &in, QString queryName)
{
    quint8 answerType;
    in >> answerType;
    switch (answerType) {
    case OK:
        return 1;
        break;
    case Error:
        emit signalError("Ошибка! При выполнении запроса " + queryName);
        break;
    case AuthorisationFail:
        emit authorisationFail("Ошибка авторизации! При выполнении запроса " + queryName);
        break;
    case PermisionDenied:
        emit permisionDenied("Недостаточно прав! При выполнении запроса " + queryName);
        break;
    default:
        emit signalError("Неизвестная ошибка! При выполнении запроса " + queryName);
        break;
    }
    return 0;
}

Query::Query()
{
    Client &client = Client::getInstance();
    connect(this, SIGNAL(signalError(QString)), &client, SLOT(error(QString)));
    Auth &auth = Auth::getInstance();
    connect(this, SIGNAL(authorisationFail(QString)), &auth, SLOT(authorisationFail(QString)));
    connect(this, SIGNAL(permisionDenied(QString)), &auth, SLOT(permisionDenied(QString)));
}

void Query::onAnswer(QByteArray answer)
{
    QDataStream in(&answer, QIODevice::ReadOnly);
    if (checkAnswerType(in)) {
        emit onSuccess();
    }
}


QueryGetOnlineUsers::QueryGetOnlineUsers() : Query()
{
}

QByteArray QueryGetOnlineUsers::execute()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (quint8) GetOnlineUsers;
    return data;
}

void QueryGetOnlineUsers::onAnswer(QByteArray answer)
{
    QDataStream in(&answer, QIODevice::ReadOnly);
    if (checkAnswerType(in, "выдачи онлайн пользователей")) {
        QList<Globals::User> users;
        while (!in.atEnd()) {
            // считывание пользователей
            Globals::User user;
            in >> user.id >> user.last_name >> user.first_name >> user.patronymic >>
                    user.email >> user.phone >> user.status >> user.latitude >> user.longitude;
            users.append(user);
            emit onSuccess(users);
        }
    }
}

QueryGetAllUsers::QueryGetAllUsers() : Query()
{
}

QByteArray QueryGetAllUsers::execute()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (quint8) GetAllUsers;
    return data;
}

void QueryGetAllUsers::onAnswer(QByteArray answer)
{
    QDataStream in(&answer, QIODevice::ReadOnly);
    if (checkAnswerType(in, "выдачи всех пользователей")) {
        QList<Globals::User> users;
        while (!in.atEnd()) {
            // считывание пользователей
            Globals::User user;
            in >> user.id >> user.last_name >> user.first_name >> user.patronymic >>
                    user.email >> user.phone >> user.status >> user.latitude >> user.longitude;
            users.append(user);
            emit onSuccess(users);
        }
    }
}

QueryGetUserTrack::QueryGetUserTrack(quint64 userID) :
    Query(), m_userID(userID)
{
}

QByteArray QueryGetUserTrack::execute()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (quint8) GetUserTrack << m_userID;
    return data;
}

void QueryGetUserTrack::onAnswer(QByteArray answer)
{
    QDataStream in(&answer, QIODevice::ReadOnly);
    if (checkAnswerType(in, "выдачи трека пользователя")) {
        QList<Globals::Coords> track;
        while (!in.atEnd()) {
            // считывание координат
            Globals::Coords coords;
            in >> coords.latitude >> coords.longitude;
            track.append(coords);
            emit onSuccess(track);
        }
    }
}

QByteArray QueryAuth::getAuthParams()
{
    Auth &auth = Auth::getInstance();
    QByteArray bytes;
    QDataStream out(&bytes, QIODevice::WriteOnly);
    out << auth.getLogin() << "\n" << auth.getPassword() << "\n";
    return bytes;
}

QByteArray QueryAuth::getAuthParamsWithSize()
{
    QByteArray bytes;
    QDataStream out(&bytes, QIODevice::WriteOnly);
    QByteArray authParams = getAuthParams();
    out << (quint64) authParams.size() << authParams;
    return bytes;
}

QueryAuth::QueryAuth() : Query()
{
}

QByteArray QueryAuth::execute()
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << (quint8) Authorisation << getAuthParamsWithSize();
    return data;
}
