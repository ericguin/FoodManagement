#include "ui.hh"

#include <QApplication>
#include <QQuickItem>
#include <QQmlContext>
#include <QVariant>
#include <QQmlApplicationEngine>

int main(int argc, char** argv)
{
    ApplicationContext ctxt{};

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    engine.rootContext()->setContextProperty("App", &ctxt);
    engine.load("qrc:///main.qml");

    return app.exec();
}
