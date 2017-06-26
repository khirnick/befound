#include "usertablemodel.h"

#include <QBrush>

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
        if (m_users[ index.row() ][ STATUS ] == 1) {
            return QBrush(QColor(255, 36, 0));
        } else {
            return QBrush(Qt::white);
        }
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

UserTableModel::UserData UserTableModel::getUserData(const Globals::User &user)
{
    UserData res;
    res[ID] = user.id;
    res[FULL_NAME] = user.last_name + " " + user.first_name + " " + user.patronymic;
    res[PHONE] = user.phone;
    res[STATUS] = user.status == Globals::UserStatus::Ok?
                "Норм." : user.status == Globals::UserStatus::Alarm?
                    "Тревога" : user.status == Globals::UserStatus::NotConnection ?
                        "Нет соединения" : user.status == Globals::UserStatus::Offline ?
                            "На базе" : "Неизв.";
    res[COORDS] = QString() + user.latitude + " " + user.longitude;
    res[EMAIL] = user.email;
    return res;
}

