import Qt 4.7

Item {
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
        enabled: game.gameOn
        opacity: {
            if (game.gameOn)
                return 1.0
            else
                return 0.0;
        }
        onClicked: {
            game.start("man", "cpu", 5)
            console.log(game.gameOn)
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
