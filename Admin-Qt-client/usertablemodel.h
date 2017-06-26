#ifndef USERTABLEMODEL_H
#define USERTABLEMODEL_H

#include <QAbstractTableModel>
#include "globals.h"

class UserTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Column {
        ID = 0,
        FULL_NAME,
        PHONE,
        STATUS,
        COORDS,
        EMAIL,
        END
    };

    typedef QHash< Column, QVariant > UserData;
    typedef QList< UserData > Users;

    UserTableModel(QObject* parent = 0);
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

    void setUsers(const Users &users);
    void setUsers(QList<Globals::User> &users);

private:
    Users m_users;

    inline UserData getUserData(const Globals::User &user);
};

#endif // USERTABLEMODEL_H
