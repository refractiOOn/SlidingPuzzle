import QtQuick 2.15
import SlidingPuzzle 1.0

GridView {
    id: root
    model: GameModel {
        id: gameModel
    }

    cellHeight: height / gameModel.boardSize
    cellWidth: width / gameModel.boardSize

    delegate: Item {
        id: backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: display !== gameModel.tilesNumber

        Tile {
            anchors.fill: backgroundDelegate
            anchors.margins: 5

            tileNumber: display

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    gameModel.moveElement(index)
                }
            }
        }
    }
}
