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
    emit signalLoggout();
}

void Auth::auth()
{
    m_isAuth = true;
    emit signalAuth();
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
