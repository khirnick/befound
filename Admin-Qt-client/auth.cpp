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

void Auth::loggout()
{
    m_isAuth = false;
}
