import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import DataEntryModel 1.0

Window {
    visible: true
    width: 210
    height: 1050
    title: qsTr("Hello World")

    Column {
        id: buttonColumn
        anchors{
            bottom: parent.bottom
        }
        spacing: 10
        Button {
            text: "Sort by Name"
            onClicked: {
                dataEntryModel.toggleSort(DataEntryModel.CryptoNameRole)
            }
        }
        Button {
            text: "Sort by Price"
            onClicked: dataEntryModel.toggleSort(DataEntryModel.CryptoPriceRole)
        }
        Button {
            text: "Sort by Market Cap Rank"
            onClicked: dataEntryModel.toggleSort(DataEntryModel.MarketCapRankRole)
        }
        Button {
            text: "Sort by 24h Change"
            onClicked: dataEntryModel.toggleSort(DataEntryModel.Val24hRole)
        }
    }

    ScrollView {
        id: scrollView
        width: 200
        height: 800

        ListView {
            width: 200
            height: 800
            model: dataEntryModel

            delegate: ListEntry {
                cryptoName: model.cryptoName
                cryptoPrice: model.cryptoPrice
                val_1h: model.val1h
                val_24h: model.val24h
                imagePath: model.imagePath
            }
            spacing: 10
        }
    }
}