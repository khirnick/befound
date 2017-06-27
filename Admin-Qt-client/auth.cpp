#include "auth.h"

#include <QMessageLogger>
#include "client.h"
#include "query.h"

Auth::Auth()
{
    m_isAuth = false;
}

void Auth::authorisationRequest()
{
    QueryAuth *request = new QueryAuth;
    QObject::connect(request, SIGNAL(onSuccess()), this, SLOT(auth()));
    Client &client = Client::getInstance();
    client.sendRequest(request);
}

Auth &Auth::getInstance()
{
    static Auth instance;
    return instance;
}

void Auth::auth(QString login, QString password)
{
    loggout();
    m_login = login;
    m_password = password;
}

bool Auth::isAuth()
{
    return m_isAuth;
}

QString Auth::getLogin()
{
    return m_login;
}

QString Auth::getPassword()
{
    return m_password;
}

void Auth::loggout()
{
    m_isAuth = false;
    QString msg = "Вы вышли из системы";
    QMessageLogger().info() << msg;
    emit signalLoggout(msg);
}

void Auth::auth()
{
    m_isAuth = true;
    QString msg = "Успешная авторизация под логином " + m_login;
    QMessageLogger().info() << msg;
    emit signalAuth(msg);
}

void Auth::authorisationFail(QString msg)
{
    QMessageLogger().warning() << msg;
    emit signalAuthorisationFail(msg);
    loggout();
    m_form.authorisationFail();
}

void Auth::permisionDenied(QString msg)
{
    QMessageLogger().warning() << msg;
    emit signalPermisionDenied(msg);
}

void Auth::showForm()
{
    m_form.show();
}
