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
