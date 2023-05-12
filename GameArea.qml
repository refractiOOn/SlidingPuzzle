import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import SlidingPuzzle 1.0

ColumnLayout {
    id: root

    GameBoard {
        id: board

        gameModel: model

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 85
    }

    GameController {
        id: controller

        gameModel: model

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 15
    }

    Dialog {
        id: notification

        width: parent.width / 3
        anchors.centerIn: parent

        title: qsTr("The puzzle is solved!")

        standardButtons: Dialog.Yes | Dialog.Cancel
        onAccepted: model.newGame()

        Text {
            anchors.centerIn: parent
            text: qsTr("Start a new game?")
        }
    }

    GameModel {
        id: model

        onPuzzleSolvedChanged: {
            if (puzzleSolved === true) {
                notification.open();
            }
        }
    }
}
