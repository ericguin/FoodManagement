#pragma once

#include <QObject>
#include <QFile>
#include "database.hh"

class ApplicationContext : public QObject
{
    Q_OBJECT

public:
    ApplicationContext();
    
public slots:
    void LoadDatabase(const QString& fpath);
};

class QFileSource : public Food::Database::Source
{
    
};