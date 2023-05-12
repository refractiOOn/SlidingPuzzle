import QtQuick

Rectangle {
    id: root

    radius: 10
    color: "lightgreen"
    border.color: "gray"
    border.width: 1

    property string tileNumber: ""

    Text {
        id: tileText
        anchors.centerIn: root

        text: root.tileNumber
        font.pointSize: Math.min(root.width, root.height) / 3
        font.bold: true
    }
}
