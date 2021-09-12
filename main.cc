#include "ui.hh"

#include <QApplication>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlApplicationEngine>

int main(int argc, char** argv)
{
    ApplicationContext ctxt{};

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load("qrc:///main.qml");
    
    engine.rootContext()->setContextProperty("App", &ctxt);

    return app.exec();
}
