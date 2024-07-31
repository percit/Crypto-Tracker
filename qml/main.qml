import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListEntry {
        anchors.centerIn: parent
        cryptoName: "BTC"
        cryptoPrice: 67589.19
        val_1h: 5
        val_24h: 8
        imagePath: "qrc:/images/btc.jpeg"
    }
}
