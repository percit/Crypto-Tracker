#include "CryptoApiManager.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

CryptoApiManager::CryptoApiManager(DataEntryModel *model, QObject *parent)
    : QObject(parent), m_networkManager(new QNetworkAccessManager(this)), m_model(model)
{
    connect(m_networkManager, &QNetworkAccessManager::finished,
            this, &CryptoApiManager::onDataFetched);
    connect(&m_timer, &QTimer::timeout, this, &CryptoApiManager::fetchData);

    m_timer.start(20000); //3000 is 3 seconds, but free api allows limit up to 5 calls a minute
}

void CryptoApiManager::fetchData()
{
    emit requestStarted();
    QUrl url(apiUrl);
    QNetworkRequest request(url);
    m_networkManager->get(request);
}

void CryptoApiManager::onDataFetched(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
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
            entry.val_24h = obj["price_change_percentage_24h_in_currency"].toInt();
            entry.imagePath = obj["image"].toString();
            entry.marketCapRank = obj["market_cap_rank"].toInt();
            entries.append(entry);
        }

        emit dataFetched(entries);
    } else {
        emit errorOccurred(reply->errorString());
    }
    reply->deleteLater();
}