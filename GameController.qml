import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import SlidingPuzzle

RowLayout {
    id: root

    Button {
        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 5

        text: qsTr("Reset")
        onClicked: GameModel.currentToInitial()
    }

    Button {
        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 5

        text: qsTr("New Game")
        onClicked: GameModel.newGame()
    }
}
