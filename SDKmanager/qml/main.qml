import QtQuick 2.0

Item {
    id: root
    width: 400
    height: 600

    /* C++ interface */
    signal buttonRedLedClicked(bool state)
    signal buttonGreenLedClicked(bool state)
    signal buttonYellowLedClicked(bool state)
    signal buttonTelemetryClicked(bool state)

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

    /* Receive events from Qt C++ */
    Connections{
        target: MainWin
        onSignalUpdateQMLState: {
           redLed.depthLight = RxData.isRedLedOn() ? 0.0: 1.0;
           yellowLed.depthLight = RxData.isYellowLedOn() ? 0.0 : 1.0;
           greenLed.depthLight  = RxData.isGreenLedOn() ? 0.0 : 1.0;

           jumpModem.checked = RxData.isJumperModem();
           jumpRS.checked    = RxData.isJumperRS();
           jumpLock.checked = RxData.isJumperLock();
           jumpMIF.checked  = RxData.isJumperMif();
           jumpPROG.checked = RxData.isJumperProg();
           jumpEXT1.checked = RxData.isJumperExt1();
           jumpEXT2.checked = RxData.isJumperExt2();

           sdkTime.time = RxData.getSDKTime()

           timeoutWnd.y = 650
        }
        onSignalQMLDataTimeOut: {
            timeoutWnd.y = 550
            timeoutWnd.caption = MainWin.getTimeout()
//            MainWin.hide();
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
                    buttonYellowLedClicked(yellowLedSw.checked)
//                    yellowLed.depthLight = checked ? 0.0 : 1.0;
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
                    buttonRedLedClicked(redLedSw.checked)
//                    redLed.depthLight = checked ? 0.0 : 1.0;
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
                    buttonGreenLedClicked(greenLedSw.checked)
//                    greenLed.depthLight = checked ? 0.0 : 1.0;
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
            onCheckedChanged: {
                buttonTelemetryClicked(telemetrySwitch.checked)
//                settings.switchX = checked;
            }
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
        property string time: "00:00:000"
        anchors.left: parent.left
        anchors.leftMargin: 22
        elide: Text.ElideRight
        font.pixelSize: 20
        color: "#202020"
        text: "Время SDK: " + time
    }

    Rectangle {
        id: timeoutWnd
        width: 350
        height: 60
        radius: 10
        anchors.horizontalCenter: parent.horizontalCenter
        y: 650
        property string caption: ""
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#e1e1e1" }
            GradientStop { position: 0.466; color: "#ffffff" }
            GradientStop { position: 1.0; color: "#e0e0e0" }
        }
        border.color: "#808080"
        border.width: 2
        Text{
            text: "Timeout. Данных уже нет " + parent.caption + "\nПроверьте соединение."
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 14
        }
        Behavior on y {
            NumberAnimation { duration: 500 }
        }
        MouseArea {
            width: parent.width
            height: parent.height
            onClicked: {
                timeoutWnd.y = 650;
            }
        }
    }

}
