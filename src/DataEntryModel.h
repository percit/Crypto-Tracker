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
    };

    void addEntry(const DataEntry &entry);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    QList<DataEntry> m_data;
};
#endif // DATA_ENTRY_MODEL_H