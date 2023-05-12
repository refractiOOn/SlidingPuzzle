import QtQuick

Rectangle {
    id: root

    radius: 10
    color: "#008b8b"
    border.color: "gray"
    border.width: 1

    property string tileNumber: ""

    Text {
        id: tileText
        anchors.centerIn: root

        text: root.tileNumber
        font.pointSize: Math.max(Math.min(root.width, root.height) / 3, 1)
        font.bold: true
    }
}
