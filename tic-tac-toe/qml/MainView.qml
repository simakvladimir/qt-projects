import Qt 4.7

Item {
    id: root

    property int size: 4

    width: 800
    height: 480

    // *** Game View ***
    GameView {
        id: gameView
        // Gameview is disabled when gameViewHider is shown
        enabled: true // gameViewHider.state == "hide"
    }

    Button{
        id: startButton
        text: "Старт"
        anchors.centerIn: parent
        enabled: game.gameOn
        opacity: {
            if (game.gameOn)
                return 1.0
            else
                return 0.0;
        }
        onClicked: {
            game.start("man", "cpu", size)
            console.log(game.gameOn)
        }
    }

    Text {
        id: textView
        font.family: "Helvetica"
        font.pointSize: 20
//        enabled:  !game.gameOn
//        smooth: true
        color: "#000000"
        anchors.centerIn: parent
        text: "Ход ПК"
        opacity: {
            if (game.activePlayer == "AI" && !game.gameOn)
                return 1.0
            else
                return 0.0
        }

    }

    // *** Game View Hider ***
//    Rectangle {
//        id: gameViewHider
//        anchors.fill: parent
//        color: "black"
//        opacity: 0.7

//        states: [
//        State {
//            name: "hide"
//            when: menuPanel.state == "hide"
//            PropertyChanges {
//                target: gameViewHider
//                opacity: 0.0
//            }
//        }
//        ]

//        transitions: Transition {
//            NumberAnimation {
//                properties: "opacity"
//                duration: 400
//            }
//        }
//    }

//    // *** Main Menu panel ***
//    MenuPanel {
//        id: menuPanel
//    }
}
