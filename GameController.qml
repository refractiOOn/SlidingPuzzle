import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

RowLayout {
    id: root

    property var gameModel

    Button {
        id: buttonReset

        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 5

        text: qsTr("Reset")
        onClicked: root.gameModel.currentToInitial()
    }

    Button {
        id: buttonNewGame

        Layout.preferredWidth: 50
        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.margins: 5

        text: qsTr("New Game")
        onClicked: root.gameModel.newGame()
    }
}
