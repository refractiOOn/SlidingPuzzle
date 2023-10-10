import QtQuick

GridView {
    id: _root

    model: gameModel
    clip: true

    cellWidth: _root.width / gameModel.boardSize
    cellHeight: _root.height / gameModel.boardSize

    delegate: GameTileDelegate {
        width: _root.cellWidth
        height: _root.cellHeight

        onClicked: {
            gameModel.moveElement(model.index)
        }
    }
}