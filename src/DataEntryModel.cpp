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
        case Qt::UserRole:
            return entry.cryptoName;
        case Qt::UserRole + 1:
            return entry.cryptoPrice;
        case Qt::UserRole + 2:
            return entry.val_1h;
        case Qt::UserRole + 3:
            return entry.val_24h;
        case Qt::UserRole + 4:
            return entry.imagePath;
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> DataEntryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole] = "cryptoName";
    roles[Qt::UserRole + 1] = "cryptoPrice";
    roles[Qt::UserRole + 2] = "val1h";
    roles[Qt::UserRole + 3] = "val24h";
    roles[Qt::UserRole + 4] = "imagePath";
    return roles;
}