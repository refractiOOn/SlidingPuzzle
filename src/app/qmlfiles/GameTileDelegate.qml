import QtQuick
import QtQuick.Controls

Item {
    id: _root

    visible: !model.isBlank

    signal clicked()

    Rectangle {
        id: _background

        anchors.fill: parent
        radius: 10
        border {
            width: 1
            color: "gray"
        }

        color: "#008B8B"
    }

    Text {
        id: _label

        anchors.centerIn: parent
        verticalAlignment: Text.AlignVCenter

        font {
            bold: true
            pointSize: Math.max(Math.min(_root.width, _root.height) / 3, 1)
        }
        text: model.number
    }

    MouseArea {
        id: _mouseArea

        anchors.fill: parent

        hoverEnabled: true
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

        onClicked: {
            _root.clicked()
        }
    }
}