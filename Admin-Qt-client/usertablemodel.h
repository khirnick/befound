#ifndef USERTABLEMODEL_H
#define USERTABLEMODEL_H

#include <QAbstractTableModel>

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

class UserTableModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    Users m_users;

public:
    UserTableModel(QObject* parent = 0);
    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;
    QVariant data( const QModelIndex& index, int role ) const;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;

    void setUsers(const Users &users);
};

#endif // USERTABLEMODEL_H
