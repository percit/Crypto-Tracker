#include "CryptoApiManager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CryptoApiManager::CryptoApiManager(DataEntryModel *model, QObject *parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this)), m_model(model)
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &CryptoApiManager::onDataFetched);

    connect(&m_timer, &QTimer::timeout,
            this, &CryptoApiManager::fetchData);

    m_timer.start(3000);
    fetchData();
}

void CryptoApiManager::fetchData()
{
    QUrl url(apiUrl);
    QNetworkRequest request(url);
    m_networkManager->get(request);
}

void CryptoApiManager::onDataFetched(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonArray jsonArray = jsonDoc.array();

    QList<DataEntryModel::DataEntry> entries;
    for (const QJsonValue &value : jsonArray) {
        QJsonObject obj = value.toObject();
        DataEntryModel::DataEntry entry;
        entry.cryptoName = obj["name"].toString();
        entry.cryptoPrice = obj["current_price"].toDouble();
        entry.val_1h = obj["price_change_percentage_1h_in_currency"].toInt();
        entry.val_24h = obj["price_change_percentage_24h"].toInt();
        entry.imagePath = obj["image"].toString();
        entries.append(entry);
    }

    m_model->updateEntries(entries);
    reply->deleteLater();
}