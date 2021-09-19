#include "ui.hh"

#include <QDebug>
#include <QUrl>
#include <QDir>
#include <iostream>

ApplicationContext::ApplicationContext()
{
    
}

void ApplicationContext::LoadDatabase(const QString& fpath)
{
    qDebug() << "Loading database: " << fpath;
    QFileSource s(fpath);
    db.Load(s);
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

QFileSource::QFileSource(QString path)
{
    QUrl url(path);
    if (url.isLocalFile())
    {
        f.setFileName(QDir::toNativeSeparators(url.toLocalFile()));
    }
}

std::string QFileSource::Read()
{
    std::string ret = "";

    if (f.exists() && f.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&f);
        ret = in.readAll().toStdString();
        f.close();
    }
    
    return ret;
}

bool QFileSource::Write(std::string& contents)
{
    if (f.exists() && f.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(&f);
        out << QString::fromStdString(contents);
        f.close();
        return true;
    }
    
    return false;
}