import QtQuick
import QtQuick.Window

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Sliding Puzzle")

    GameBoard {
        id: board
        anchors.fill: parent
    }
}
