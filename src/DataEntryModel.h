#ifndef DATA_ENTRY_MODEL_H
#define DATA_ENTRY_MODEL_H

#include <QAbstractListModel>
#include <QList>
#include <QString>
#include <QVariant>

class DataEntryModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DataEntryModel(QObject *parent = nullptr);
    ~DataEntryModel();

    struct DataEntry {
        QString cryptoName;
        qreal cryptoPrice;
        int val_1h;
        int val_24h;
        QVariant imagePath;
        int marketCapRank;
    };

    void updateEntries(const QList<DataEntry> &entries);
    void addEntry(const DataEntry &entry);
    Q_INVOKABLE void sortEntries(int role, Qt::SortOrder order = Qt::AscendingOrder);
    Q_INVOKABLE void toggleSort(int role);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    enum Roles {
        CryptoNameRole = Qt::UserRole + 1,
        CryptoPriceRole,
        Val1hRole,
        Val24hRole,
        ImagePathRole,
        MarketCapRankRole
    };
    Q_ENUMS(Roles)
private:
    QList<DataEntry> m_data;
    QHash<int, Qt::SortOrder> m_sortOrders;
};
#endif // DATA_ENTRY_MODEL_H