#include "ui.hh"

#include <QDebug>
#include <iostream>

ApplicationContext::ApplicationContext()
{
    
}

void ApplicationContext::LoadDatabase(const QString& fpath)
{
    qDebug() << "I'm getting something: " << fpath;
    std::cout << "Yeeted: " << fpath.toStdString() << std::endl;
}

QString ApplicationContext::userName()
{
    return m_userName;
}

void ApplicationContext::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;
    
    std::cout << "yo so the thing did the thing" << userName.toStdString() << std::endl;

    m_userName = userName;
    emit userNameChanged();
}