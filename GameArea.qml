import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import SlidingPuzzle

ColumnLayout {
    id: root

    GameBoard {
        id: board

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 85
    }

    GameController {
        id: controller

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 15
    }

    Dialog {
        id: notification

        width: parent.width / 2
        anchors.centerIn: parent

        title: qsTr("The puzzle is solved!")

        standardButtons: Dialog.Yes | Dialog.Cancel
        onAccepted: GameModel.newGame()

        Text {
            anchors.centerIn: parent
            text: qsTr("Start a new game?")
        }
    }

//    GameModel.onPuzzleSolvedChanged: {
//        if (GameModel.puzzleSolved) {
//            notification.open();
//        }
//    }

    Connections {
        target: GameModel
        onPuzzleSolvedChanged: {
            if (GameModel.puzzleSolved) {
                notification.open();
            }
        }
    }
}
