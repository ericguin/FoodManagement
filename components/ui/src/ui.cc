#include "ui.hh"

#include <QDebug>

ApplicationContext::ApplicationContext()
{
    
}

void ApplicationContext::LoadDatabase(const QString& fpath)
{
    qDebug() << "I'm getting something: " << fpath;
}
