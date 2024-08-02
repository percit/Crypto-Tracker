#include "DataEntryModel.h"

DataEntryModel::DataEntryModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

DataEntryModel::~DataEntryModel()
{
}

void DataEntryModel::addEntry(const DataEntry &entry)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(entry);
    endInsertRows();
}

void DataEntryModel::updateEntries(const QList<DataEntry> &entries)
{
    beginResetModel();
    m_data = entries;
    endResetModel();
    emit dataUpdated(); //for chaging color
}

void DataEntryModel::sortEntries(int role, Qt::SortOrder order)
{
    auto compare = [role, order](const DataEntry &a, const DataEntry &b) -> bool {
        switch (role) {
            case CryptoNameRole:
                return order == Qt::AscendingOrder ? a.cryptoName < b.cryptoName : a.cryptoName > b.cryptoName;
            case CryptoPriceRole:
                return order == Qt::AscendingOrder ? a.cryptoPrice < b.cryptoPrice : a.cryptoPrice > b.cryptoPrice;
            case MarketCapRankRole:
                return order == Qt::AscendingOrder ? a.marketCapRank < b.marketCapRank : a.marketCapRank > b.marketCapRank;
            case Val24hRole:
                return order == Qt::AscendingOrder ? a.val_24h < b.val_24h : a.val_24h > b.val_24h;
            default:
                return false;
        }
    };
    std::sort(m_data.begin(), m_data.end(), compare);

    emit dataChanged(index(0), index(rowCount() - 1));
}

void DataEntryModel::toggleSort(int role)
{
    if (!m_sortOrders.contains(role)) {
        m_sortOrders[role] = Qt::AscendingOrder;
    }

    Qt::SortOrder currentOrder = m_sortOrders[role];
    Qt::SortOrder newOrder = (currentOrder == Qt::AscendingOrder) ? Qt::DescendingOrder : Qt::AscendingOrder;
    sortEntries(role, newOrder);
    m_sortOrders[role] = newOrder;
}

int DataEntryModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant DataEntryModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size() || index.row() < 0)
        return QVariant();

    const DataEntry &entry = m_data.at(index.row());

    switch (role) {
        case Qt::DisplayRole:
            return entry.cryptoName;
        case CryptoNameRole:
            return entry.cryptoName;
        case CryptoPriceRole:
            return entry.cryptoPrice;
        case Val1hRole:
            return entry.val_1h;
        case Val24hRole:
            return entry.val_24h;
        case ImagePathRole:
            return entry.imagePath;
        case MarketCapRankRole:
            return entry.marketCapRank;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> DataEntryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CryptoNameRole] = "cryptoName";
    roles[CryptoPriceRole] = "cryptoPrice";
    roles[Val1hRole] = "val1h";
    roles[Val24hRole] = "val24h";
    roles[ImagePathRole] = "imagePath";
    roles[MarketCapRankRole] = "marketCapRank";
    return roles;
}