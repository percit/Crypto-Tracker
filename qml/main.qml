import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Rectangle {
        width: 100
        height: 100
        color: "red"
        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            font.pixelSize: 15
            text: "Hello World!"
        }
    }
}
