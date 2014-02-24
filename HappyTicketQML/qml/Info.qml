import QtQuick 2.0

Item {
    id: menuPanel

    property int cpuCores: 0
    property int appThread: 0
    property int ticketsNumber: 0
    property string startTime: ""
    property string finishTime: ""
    property string durationTime: ""
    property string cpuModel: ""


    width: parent.width
    height: parent.height

    Rectangle {
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 100
        height: parent.height - 50
        border.color: "#999999"
        border.width: 2
        radius: 10
        smooth: true
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#ffffff" }
            GradientStop { position: 1.0; color: "#dddddd" }
        }

        Column{
            width: parent.width
            y: 16

            Text {
                id: cpuCaption
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 15
                color: "#888888"
                text: qsTr("Кол-во потоков:") + " " + appThread.toString()
            }

            Text {
                id: timeStart
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 15
                color: "#888888"
                text: qsTr("Время старта:") + " " + startTime
            }

            Text {
                id: timeFinish
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 15
                color: "#888888"
                text: qsTr("Время окончания:") + " " + finishTime
            }
            Text {
                id: timeDuration
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 15
                color: "#888888"
                text: qsTr("Время:") + " " + durationTime
            }
            Text {
                id: ticketNum
                anchors.horizontalCenter: parent.horizontalCenter
                font.pixelSize: 15
                color: "#888888"
                text: qsTr("Билетов:") + " " + ticketsNumber.toString()
            }
        }
        Text {
            id: cpuBrand
            height: 50
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            font.pixelSize: 15
            color: "#888888"
            text: qsTr( cpuCores + " CPU:") + " " + cpuModel
        }
    }

    states: [
    State {
        name: "hide"
        PropertyChanges {
            target: menuPanel
            opacity: 0.0
//            y: -menuPanelFrame.height
        }
    }
    ]

    transitions: Transition {
        NumberAnimation {
            properties: "opacity, y"
            duration: 400
        }
    }

}
