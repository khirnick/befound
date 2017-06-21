#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("BeFOUND");
    QCoreApplication::setOrganizationDomain("be-found.ru");
    QCoreApplication::setApplicationName("BeFOUND - Admin");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
