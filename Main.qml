import QtQuick
import QtQuick.Window
import SlidingPuzzle 1.0

Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Sliding Puzzle")

    GameArea {
        id: game
        anchors.fill: parent
    }
}
