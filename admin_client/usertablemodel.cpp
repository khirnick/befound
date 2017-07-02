#include "usertablemodel.h"

#include <QBrush>
#include "globals.h"

UserTableModel::UserTableModel(QObject* parent)
{
    Q_UNUSED( parent )
}

int UserTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return m_users.count();
}

int UserTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED( parent )
    return END;
}

QVariant UserTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() ||
            m_users.count() <= index.row() ||
            ( role != Qt::DisplayRole && role != Qt::BackgroundRole )) {
        return QVariant();
    }

    if (role == Qt::BackgroundRole) {
        if (m_users[ index.row() ][ STATUS ] == Globals::UserStatus::Alarm) {
            return QBrush(QColor(255, 110, 74));
        } else {
            return QBrush(Qt::white);
        }
    }

    if (index.column() == STATUS) {
        return userStatusStr( m_users[ index.row() ][ Column(index.column()) ].toInt() );
    }

    return m_users[ index.row() ][ Column( index.column() ) ];
}

QVariant UserTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole ) {
        return QVariant();
    }

    if( orientation == Qt::Vertical ) {
        return section;
    }

    switch( section ) {
    case ID:
        return "ID";
    case FULL_NAME:
        return "ФИО";
    case PHONE:
        return "Тел.";
    case STATUS:
        return "Статус";
    case COORDS:
        return "Последние координаты";
    case EMAIL:
        return "E-Mail";
    }

    return QVariant();
}

void UserTableModel::setUsers(const Users &users)
{
    if (m_users.count() > 0) {
        beginRemoveRows( QModelIndex(), 0, m_users.count() - 1);
        m_users.clear();
        endRemoveRows();
    }
    beginInsertRows( QModelIndex(), 0, users.count() - 1);
    m_users = users;
    endInsertRows();
}

void UserTableModel::setUsers(QList<Globals::User> &users)
{
    Users _users;
    for (QList<Globals::User>::iterator i = users.begin(); i != users.end(); ++i) {
        _users.append(getUserData(*i));
    }
    setUsers(_users);
}

quint64 UserTableModel::getUserID(int row)
{
    return m_users[row][ID].toInt();
}

UserTableModel::UserData UserTableModel::getUserData(const Globals::User &user)
{
    UserData res;
    res[ID] = user.id;
    res[FULL_NAME] = user.last_name + " " + user.first_name + " " + user.patronymic;
    res[PHONE] = user.phone;
    res[STATUS] = user.status;
    res[COORDS] = QString().number(user.latitude) + " " + QString().number(user.longitude);
    res[EMAIL] = user.email;
    return res;
}

QString UserTableModel::userStatusStr(int status) const
{
    return status == Globals::UserStatus::Ok?
                "Норм." : status == Globals::UserStatus::Alarm?
                    "Тревога" : status == Globals::UserStatus::NotConnection ?
                        "Нет соединения" : status == Globals::UserStatus::Offline ?
                            "На базе" : "Неизв.";
}

