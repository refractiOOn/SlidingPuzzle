import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

RowLayout {
    id: root

    property var gameModel

    Repeater {
        model: 2

        delegate: Button {
            Layout.preferredWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 5

            text: index === 0 ? qsTr("Reset") : qsTr("New Game")
            onClicked: index === 0 ? root.gameModel.currentToInitial() : root.gameModel.newGame()
        }
    }
}
