import QtQuick 2.0

Item {
    id: root
    width: 400
    height: 600
    Rectangle {
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#bfbfbf" }
            GradientStop { position: 0.4; color: "#e0e0e0" }
            GradientStop { position: 1.0; color: "#a0a0a0" }
        }
        border.color: "#808080"
        border.width: 2
    }

    Connections{
        target: MainWin
        onSignalRedLedState: {
           redLed.depthLight = RxData.isRedLedOn() ? 0.0: 1.0;
        }
    }

    Column{
        Row {
            anchors.fill: parent

            Switch {
                id: yellowLedSw
                width: 300
                y: 10
                clip: false
                text: "Желтый диод:"
    //            checked: settings.switchX
                onCheckedChanged: {
                    yellowLed.depthLight = checked ? 0.0 : 1.0;
                }
            }
            Led{
                id:yellowLed
                y: 10
                ledColor: Qt.rgba(1.0, 1.0, 0.0, 1.0);
            }
        }
        Row {
            anchors.fill: parent

            Switch {
                id: redLedSw
                width: 300
                y: 70
                clip: false
                text: "Красный диод:"
    //            checked: settings.switchX
                onCheckedChanged: {
                    redLed.depthLight = checked ? 0.0 : 1.0;
                }
            }
            Led{
                id:redLed
                y: 70
                ledColor: Qt.rgba(1.0, 0.0, 0.0, 1.0);
            }
        }
        Row {
            anchors.fill: parent

            Switch {
                id: greenLedSw
                width: 300
                y: 130
                clip: false
                text: "Зеленый диод:"
    //            checked: settings.switchX
                onCheckedChanged: {
                    greenLed.depthLight = checked ? 0.0 : 1.0;
                }
            }
            Led{
                id:greenLed
                y: 130
                ledColor: Qt.rgba(0.0, 1.0, 0.0, 1.0);
            }
        }
    }
    Switch {
        id: telemetrySwitch
        width: parent.width
        y: 190
        clip: false
        text: "Отправка телеметрии:"
//            checked: settings.switchX
//            onCheckedChanged: {
//                settings.switchX = checked;
//            }
    }
    Text {
        y: 250
        anchors.left: parent.left
        anchors.leftMargin: 22
        elide: Text.ElideRight
        font.pixelSize: 20
        color: "#202020"
        text: "Состояние разъема J2 SDK4"
    }

    Jumper{
        id:jumpModem
        caption: "Modem"
        y: 290
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpRS
        caption: "RS"
        y: 320
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpLock
        caption: "LOCK"
        y: 350
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpMIF
        caption: "MIF"
        y: 380
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpPROG
        caption: "PROG"
        y: 410
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpEXT1
        caption: "EXT1"
        y: 440
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Jumper{
        id:jumpEXT2
        caption: "EXT2"
        y: 470
        height: 30
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Text {
        id: sdkTime
        y: 510
        anchors.left: parent.left
        anchors.leftMargin: 22
        elide: Text.ElideRight
        font.pixelSize: 20
        color: "#202020"
        text: "Время SDK"
    }

}
