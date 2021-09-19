#pragma once

#include <QObject>
#include <QFile>
#include "database.hh"

#include <memory>

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
    Food::Database db;
};

class QFileSource : public Food::Database::Source
{
public:
    QFileSource(QString path);
    ~QFileSource() override = default;
    std::string Read() override;
    bool Write(std::string&) override;
private:
    QFile f;
};