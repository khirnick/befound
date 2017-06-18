#include "usertablemodel.h"

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
            ( role != Qt::DisplayRole && role != Qt::EditRole )) {
        return QVariant();
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

