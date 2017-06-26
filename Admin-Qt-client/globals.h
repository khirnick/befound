#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

namespace Globals
{
    const QString defaultIP = "127.0.0.1";
    const quint16 defaultPort = 42;
    const int defaultUpdatePeriod = 2;
    const int timeout = 600000;             // Таймаут запросов 10сек
}

#endif // GLOBALS_H
