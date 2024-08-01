#ifndef CRYPTO_API_MANAGER_H
#define CRYPTO_API_MANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include "DataEntryModel.h"

class CryptoApiManager : public QObject
{
    Q_OBJECT
public:
    explicit CryptoApiManager(DataEntryModel *model, QObject *parent = nullptr);

private slots:
    void onDataFetched(QNetworkReply *reply);
    void fetchData();

private:
    QNetworkAccessManager *m_networkManager;
    QTimer m_timer;
    DataEntryModel *m_model;
    const QString apiUrl = "https://api.coingecko.com/api/v3/coins/markets?vs_currency=usd";
};

#endif // CRYPTO_API_MANAGER_H
