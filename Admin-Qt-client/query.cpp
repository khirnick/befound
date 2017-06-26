#include "query.h"

#include <QDataStream>
#include <QList>
#include "globals.h"

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
    quint8 answerType;
    in >> answerType;
    if (answerType == 0) {
        QList<Globals::User> users;
        while (!in.atEnd()) {
            // считывание пользователей
            Globals::User user;
            in >> user.id >> user.last_name >> user.first_name >> user.patronymic >>
                    user.email >> user.phone >> user.status >> user.latitude >> user.longitude;
            users.append(user);
            emit onlineUsers(users);
        }

    } else {
        emit signalError("Ошибка! при запросе онлайн пользователей");
    }
}
