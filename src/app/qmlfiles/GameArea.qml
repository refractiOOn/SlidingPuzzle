import QtQuick
import QtQuick.Controls

Item {
    id: _root

    GameBoard {
        id: _gameBoard

        anchors {
            top: _root.top
            left: _root.left
            right: _root.right
        }
        height: _root.height * 0.85
    }

    Item {
        id: _gameControls

        anchors {
            top: _gameBoard.bottom
            left: _gameBoard.left
            right: _gameBoard.right
            bottom: _root.bottom
        }

        Button {
            anchors {
                top: _gameControls.top
                left: _gameControls.left
                bottom: _gameControls.bottom
                rightMargin: _root.width * 0.02
            }
            width: _root.width * 0.5

            text: qsTr("Reset Game")

            onClicked: {
                gameModel.resetGame()
            }
        }

        Button {
            anchors {
                top: _gameControls.top
                right: _gameControls.right
                bottom: _gameControls.bottom
                leftMargin: _root.width * 0.02
            }
            width: _root.width * 0.5

            text: qsTr("New Game")

            onClicked: {
                _newGameWindow.open()
                // gameModel.newGame()
            }
        }
    }

    Dialog {
        id: _puzzleSolvedWindow

        width: parent.width / 2
        anchors.centerIn: parent

        title: qsTr("The puzzle is solved!")

        standardButtons: Dialog.Yes | Dialog.Cancel

        Text {
            anchors.centerIn: parent
            text: qsTr("Start a new game?")
        }

        onAccepted: {
            _newGameWindow.open()
        }
    }

    Dialog {
        id: _newGameWindow

        width: parent.width / 2
        height: parent.width / 3

        anchors.centerIn: parent

        title: qsTr("New Game")

        standardButtons: Dialog.Yes | Dialog.Cancel

        Item {
            id: _boardSizeSelector

            anchors.fill: parent

            Text {
                id: _boardSizeSelectorLabel

                anchors {
                    top: _boardSizeSelector.top
                    left: _boardSizeSelector.left
                    bottom: _boardSizeSelector.bottom
                }
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: _boardSizeSelector.width * 0.5

                text: "Board size:"
            }

            SpinBox {
                id: _spinBox

                anchors {
                    right: _boardSizeSelector.right
                    verticalCenter: _boardSizeSelector.verticalCenter
                }
                width: _boardSizeSelector.width * 0.5
                height: _boardSizeSelectorLabel.font.pixelSize * 2

                from: 3
                to: 5
                value: 4
            }
        }

        onAccepted: {
            gameModel.setupBoard(_spinBox.value)
            // gameModel.boardSize = _spinBox.value
        }
    }
}