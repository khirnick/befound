/****************************************************************************
** Meta object code from reading C++ file 'query.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Admin-Qt-client/query.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'query.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Query_t {
    QByteArrayData data[4];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Query_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Query_t qt_meta_stringdata_Query = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Query"
QT_MOC_LITERAL(1, 6, 11), // "signalError"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 3) // "msg"

    },
    "Query\0signalError\0\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Query[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void Query::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Query *_t = static_cast<Query *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Query::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Query::signalError)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Query::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Query.data,
      qt_meta_data_Query,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Query::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Query::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Query.stringdata0))
        return static_cast<void*>(const_cast< Query*>(this));
    return QObject::qt_metacast(_clname);
}

int Query::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Query::signalError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_QueryGetOnlineUsers_t {
    QByteArrayData data[7];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QueryGetOnlineUsers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QueryGetOnlineUsers_t qt_meta_stringdata_QueryGetOnlineUsers = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QueryGetOnlineUsers"
QT_MOC_LITERAL(1, 20, 11), // "signalError"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "msg"
QT_MOC_LITERAL(4, 37, 11), // "onlineUsers"
QT_MOC_LITERAL(5, 49, 20), // "QList<Globals::User>"
QT_MOC_LITERAL(6, 70, 5) // "users"

    },
    "QueryGetOnlineUsers\0signalError\0\0msg\0"
    "onlineUsers\0QList<Globals::User>\0users"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QueryGetOnlineUsers[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void QueryGetOnlineUsers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QueryGetOnlineUsers *_t = static_cast<QueryGetOnlineUsers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->onlineUsers((*reinterpret_cast< QList<Globals::User>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QueryGetOnlineUsers::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QueryGetOnlineUsers::signalError)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QueryGetOnlineUsers::*_t)(QList<Globals::User> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QueryGetOnlineUsers::onlineUsers)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QueryGetOnlineUsers::staticMetaObject = {
    { &Query::staticMetaObject, qt_meta_stringdata_QueryGetOnlineUsers.data,
      qt_meta_data_QueryGetOnlineUsers,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QueryGetOnlineUsers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QueryGetOnlineUsers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QueryGetOnlineUsers.stringdata0))
        return static_cast<void*>(const_cast< QueryGetOnlineUsers*>(this));
    return Query::qt_metacast(_clname);
}

int QueryGetOnlineUsers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Query::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QueryGetOnlineUsers::signalError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QueryGetOnlineUsers::onlineUsers(QList<Globals::User> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_QueryGetAllUsers_t {
    QByteArrayData data[7];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QueryGetAllUsers_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QueryGetAllUsers_t qt_meta_stringdata_QueryGetAllUsers = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QueryGetAllUsers"
QT_MOC_LITERAL(1, 17, 11), // "signalError"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 3), // "msg"
QT_MOC_LITERAL(4, 34, 8), // "allUsers"
QT_MOC_LITERAL(5, 43, 20), // "QList<Globals::User>"
QT_MOC_LITERAL(6, 64, 5) // "users"

    },
    "QueryGetAllUsers\0signalError\0\0msg\0"
    "allUsers\0QList<Globals::User>\0users"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QueryGetAllUsers[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void QueryGetAllUsers::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QueryGetAllUsers *_t = static_cast<QueryGetAllUsers *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->allUsers((*reinterpret_cast< QList<Globals::User>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QueryGetAllUsers::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QueryGetAllUsers::signalError)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QueryGetAllUsers::*_t)(QList<Globals::User> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QueryGetAllUsers::allUsers)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject QueryGetAllUsers::staticMetaObject = {
    { &Query::staticMetaObject, qt_meta_stringdata_QueryGetAllUsers.data,
      qt_meta_data_QueryGetAllUsers,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QueryGetAllUsers::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QueryGetAllUsers::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QueryGetAllUsers.stringdata0))
        return static_cast<void*>(const_cast< QueryGetAllUsers*>(this));
    return Query::qt_metacast(_clname);
}

int QueryGetAllUsers::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Query::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void QueryGetAllUsers::signalError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QueryGetAllUsers::allUsers(QList<Globals::User> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
