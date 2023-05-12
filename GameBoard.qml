import QtQuick
import SlidingPuzzle

GridView {
    id: root
    model: GameModel

    cellHeight: height / GameModel.boardSize
    cellWidth: width / GameModel.boardSize

    delegate: Item {
        id: backgroundDelegate
        width: root.cellWidth
        height: root.cellHeight

        visible: display !== 0

        Tile {
            anchors.fill: backgroundDelegate
            anchors.margins: 5

            tileNumber: display

            MouseArea {
                anchors.fill: parent

                onClicked: GameModel.moveElement(index)
            }
        }
    }
}
