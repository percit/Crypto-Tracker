
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataEntryModel.h"
#include "CryptoApiManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    DataEntryModel model;
    // model.addEntry({"Bitcoin", 67589.19, 5, 8, QVariant::fromValue(QStringLiteral("images/btc.jpeg"))});
    // model.addEntry({"Ethereum", 4289.22, -2, 3, QVariant::fromValue(QStringLiteral("path/to/ethereum.png"))});
    // model.addEntry({"Bitcoin", 67589.19, 5, 8, QVariant::fromValue(QStringLiteral("images/btc.jpeg"))});
    // model.addEntry({"Ethereum", 4289.22, -2, 3, QVariant::fromValue(QStringLiteral("path/to/ethereum.png"))});
    // model.addEntry({"Bitcoin", 67589.19, 5, 8, QVariant::fromValue(QStringLiteral("images/btc.jpeg"))});
    // model.addEntry({"Ethereum", 4289.22, -2, 3, QVariant::fromValue(QStringLiteral("path/to/ethereum.png"))});
    // model.addEntry({"Bitcoin", 67589.19, 5, 8, QVariant::fromValue(QStringLiteral("images/btc.jpeg"))});
    // model.addEntry({"Ethereum", 4289.22, -2, 3, QVariant::fromValue(QStringLiteral("path/to/ethereum.png"))});
    // model.addEntry({"Bitcoin", 67589.19, 5, 8, QVariant::fromValue(QStringLiteral("images/btc.jpeg"))});
    // model.addEntry({"Ethereum", 4289.22, -2, 3, QVariant::fromValue(QStringLiteral("path/to/ethereum.png"))});

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("dataEntryModel", &model);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);
    CryptoApiManager apiManager(&model);

    return app.exec();
}
