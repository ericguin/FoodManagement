#pragma once

#include <QObject>
#include <QFile>
#include "database.hh"

class ApplicationContext : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)

public:
    ApplicationContext();
    
    QString userName();
    void setUserName(const QString &userName);

public slots:
    void LoadDatabase(const QString& fpath);

signals:
    void userNameChanged();

private:
    QString m_userName;
};

class QFileSource : public Food::Database::Source
{
    
};