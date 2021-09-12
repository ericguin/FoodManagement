#pragma once

#include <QObject>

class ApplicationContext : public QObject
{
    Q_OBJECT

public:
    ApplicationContext();
    
public slots:
    void LoadDatabase(const QString& fpath);
};
