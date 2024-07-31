import QtQuick 2.12
import QtQuick.Shapes 1.15

Shape {
    id: root
    width: 200
    height: 100
    property string cryptoName: "BTC"
    property real cryptoPrice: 67589.19
    property int val_1h: 5
    property int val_24h: 8
    property var imagePath: "qrc:/images/btc.jpeg"

    Image {
        source: imagePath
        width: 35
        height: 35
        anchors {
            left: parent.left; leftMargin: 10
            verticalCenter: root.verticalCenter
        }
    }

    Column {
        anchors {
            left: parent.left; leftMargin: 60
            verticalCenter: root.verticalCenter
        }
        spacing: 5
        Text {
            text: root.cryptoName
            font.pointSize: 7
        }
        Text {
            text: "Current price: " + root.cryptoPrice + " USD"
            font.pointSize: 7
        }
        Text {
            text: "1h: " + root.val_1h + "%"
            color: root.val_1h >= 0 ? "green" : "red"
            font.pointSize: 7
        }
        Text {
            text: "24h: " + root.val_24h + "%"
            color: root.val_24h >= 0 ? "green" : "red"
            font.pointSize: 7
        }
    }

    ShapePath {
        strokeColor: "black"
        strokeWidth: 2
        fillColor: "white"
        startX: 0
        startY: 0

        PathMove { x: 0; y: 0 }
        PathLine { x: 170; y: 0 }
        PathLine { x: 200; y: 30 }
        PathLine { x: 200; y: 100 }
        PathLine { x: 30; y: 100 }
        PathLine { x: 0; y: 70 }
        PathLine { x: 0; y: 0 }
    }
}