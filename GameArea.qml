import QtQuick 2.15
import QtQuick.Layouts 1.15
import SlidingPuzzle 1.0

ColumnLayout {
    id: root

    GameBoard {
        id: board

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 90
    }

    GameController {
        id: controller

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.preferredHeight: 10
    }

    GameModel {
        id: model

        Component.onCompleted: {
            board.gameModel = model;
            controller.gameModel = model;
        }
    }
}
