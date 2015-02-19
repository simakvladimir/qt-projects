import Qt 4.7

Item {
    id: tile
    width: 80
    height: 80

    function update(){
        var src;
        if (game.cellValueByIndex(index) == 1)
            src = "images/tile_button1.png";
        else if (game.cellValueByIndex(index) == 2)
            src = "images/tile_button2.png"
        else
            src = ""

        cellView.source = src;
    }

    // Tile background rectangle
    Image {
        source: "images/tile_background.png"
//        opacity: {
//            if (highlighted)
//                return 1.0
//            else
//                return 0.6
//        }
        Behavior on opacity {
//            enabled: gameData.moves != 0
            enabled:  true
            NumberAnimation {
                properties:"opacity"
                duration: 500
            }
        }
    }
    // Tile Button
    Image {
        id: cellView
        anchors.centerIn: parent
//        opacity: player1 || player2
//        Behavior on opacity {
//            enabled: true
//            NumberAnimation {
//                properties: "opacity"
//                duration: 1500
//            }
//        }
    }
    MouseArea {
        anchors.fill: parent
        enabled: game.activePlayer != "cpu"
        onClicked: {
            game.enteredIndex = index;
//            explosion.explode()
        }
    }
    Connections{
        target: game
        onDataChanged: {
            update();
//            console.log("fdsf", index)
        }
    }

//    Explosion {
//        id: explosion
//    }
}
