
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DataEntryModel.h"
#include <QThread>
#include "CryptoApiManager.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    DataEntryModel model;
    CryptoApiManager *cryptoApiManager = new CryptoApiManager(&model);
    QThread *apiThread = new QThread();

    cryptoApiManager->moveToThread(apiThread);

    QObject::connect(apiThread, &QThread::started, cryptoApiManager, &CryptoApiManager::fetchData);
    QObject::connect(cryptoApiManager, &CryptoApiManager::dataFetched, [&model](const QList<DataEntryModel::DataEntry> &entries) {
        model.updateEntries(entries);
    });
    QObject::connect(cryptoApiManager, &CryptoApiManager::errorOccurred, [](const QString &errorString) {
        qWarning() << "Error occurred:" << errorString;
    });
    QObject::connect(apiThread, &QThread::finished, cryptoApiManager, &QObject::deleteLater);
    QObject::connect(apiThread, &QThread::finished, apiThread, &QObject::deleteLater);

    apiThread->start();


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("dataEntryModel", &model);
    qmlRegisterType<DataEntryModel>("DataEntryModel", 1, 0, "DataEntryModel"); //to run sort functions
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
