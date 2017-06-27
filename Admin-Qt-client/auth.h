#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include "authform.h"

// Класс логгера, синглтон
class Auth : public QObject
{
    Q_OBJECT

    QString m_login;
    QString m_password;
    bool m_isAuth;
    AuthForm m_form;

private:
    Auth();
    Auth( const Auth&);
    Auth& operator=( Auth& );

    inline void authorisationRequest();

public:
    static Auth& getInstance();

    void auth(QString login, QString password);
    bool isAuth();
    QString getLogin();
    QString getPassword();

signals:
    void signalAuth();
    void signalLoggout();
    void signalAuthorisationFail(QString msg);
    void signalPermisionDenied(QString msg);

public slots:
    void loggout();
    void auth();
    void authorisationFail(QString msg = QString("Ошибка авторизации!"));
    void permisionDenied(QString msg = QString("Недостаточно прав!"));
    void showForm();

};

#endif // AUTH_H
