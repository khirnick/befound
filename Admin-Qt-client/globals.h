#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

namespace Globals
{
    const QString defaultIP = "127.0.0.1";
    const quint16 defaultPort = 42;
    const int defaultUpdatePeriod = 2;
    const int timeout = 600000;             // Таймаут запросов 10сек

    enum UserStatus {
        Ok = 0,
        Alarm,
        NotConnection,
        Offline
    };

    struct User {
        quint64 id;
        QString first_name;
        QString last_name;
        QString patronymic;
        QString phone;
        QString email;
        quint8 status;
        qreal latitude;
        qreal longitude;
    };
}

#endif // GLOBALS_H
