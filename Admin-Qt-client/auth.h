#ifndef AUTH_H
#define AUTH_H

#include <QObject>

// Класс логгера, синглтон
class Auth : public QObject
{
    Q_OBJECT

    QString m_login;
    QString m_password;
    bool m_isAuth;

private:
    Auth();
    Auth( const Auth&);
    Auth& operator=( Auth& );

public:
    static Auth& getInstance();
    void auth(QString login, QString password);
    void auth();

signals:
    void authorisation(QString login, QString password);

public slots:
    void loggout();

};

#endif // AUTH_H
