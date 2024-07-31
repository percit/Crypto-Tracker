import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 210
    height: 800
    title: qsTr("Hello World")

    ScrollView {
        width: parent.width
        height: parent.height

        ListView {
            width: parent.width
            height: parent.height
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