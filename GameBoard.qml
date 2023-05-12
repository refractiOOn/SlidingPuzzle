import QtQuick 2.15

GridView {
    id: root
    model: gameModel

    cellHeight: height / gameModel.boardSize
    cellWidth: width / gameModel.boardSize

    property var gameModel

    delegate: Item {
        id: backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: display !== root.gameModel.tilesNumber

        Tile {
            anchors.fill: backgroundDelegate
            anchors.margins: 5

            tileNumber: display

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    root.gameModel.moveElement(index)
                }
            }
        }
    }
}
