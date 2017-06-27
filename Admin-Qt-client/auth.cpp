#include "auth.h"

Auth::Auth()
{
    m_isAuth = false;
}

Auth &Auth::getInstance()
{
    static Auth instance;
    return instance;
}

void Auth::auth(QString login, QString password)
{

}

void Auth::loggout()
{
    m_isAuth = false;
}

void Auth::showForm()
{
    m_form.show();
}
