#include "query.h"

#include <QList>
#include "globals.h"

bool Query::checkAnswerType(QDataStream &in, QString queryName)
{
    quint8 answerType;
    in >> answerType;
    switch (answerType) {
    case OK:
        return 1;
        break;
    case Error:
        emit signalError("Ошибка! При запросе " + queryName);
        break;
    case AuthorisationFail:
        emit authorisationFail("Ошибка авторизации! При запросе " + queryName);
        break;
    case PermisionDenied:
        emit permisionDenied("Недостаточно прав! При запросе " + queryName);
        break;
    default:
        emit signalError("Неизвестная ошибка! При запросе " + queryName);
        break;
    }
    return 0;
}

Query::Query()
{
}


QueryGetOnlineUsers::QueryGetOnlineUsers() : Query()
{
}

QueryGetOnlineUsers::~QueryGetOnlineUsers()
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
            emit onlineUsers(users);
        }
    }
}

QueryGetAllUsers::QueryGetAllUsers() : Query()
{
}

QueryGetAllUsers::~QueryGetAllUsers()
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
            emit allUsers(users);
        }
    }
}

QueryGetUserTrack::QueryGetUserTrack(quint64 userID) :
    Query(), m_userID(userID)
{
}

QueryGetUserTrack::~QueryGetUserTrack()
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
            emit userTrack(track);
        }
    }
}
