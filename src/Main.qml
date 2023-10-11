import QtQuick
import QtQuick.Window
import app

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Sliding Puzzle")

    GameArea {
        id: _gameArea

        anchors.fill: parent
    }
}
