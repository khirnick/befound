#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

namespace Globals
{
    const QString defaultIP = "127.0.0.1";
    const quint16 defaultPort = 6000;
    const int defaultUpdatePeriod = 2000;
    const int timeout = 10000;              // Таймаут запросов 10сек
    const int statusBarTimeout = 5000;      // Время показа сообщений в статусбаре

    // Коориднаты при загрузки карты
    const double baseLatitude = 55.765670;
    const double baseLongitude = 37.685922;
    const int baseZoom = 2800;

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
        double latitude;
        double longitude;
    };

    struct Coords {
        double latitude;
        double longitude;
    };

}

#endif // GLOBALS_H
