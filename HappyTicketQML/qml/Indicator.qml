import QtQuick 2.0

Item {
    id: indicator
    property int  value: 1
    property string caption: ""

    height: 60

    Text {
        id: captionText
        anchors.leftMargin: 22
        anchors.left: parent.left
        text: caption
        font.pixelSize: 15
        color: "#FFFFFF"
    }

    Rectangle {
        id: normal
        height: 40
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 22
        anchors.right: parent.right
        anchors.rightMargin: 22

//        anchors.fill: parent
        border.width: 3
        radius: 10
        border.color: "#b3941e"
        smooth: true
        Text {
            id: intValue
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
//            x: 20
            font.family: "Helvetica"
            text: value.toString()
            font.pixelSize: 30
            color: "#202020"
        }
    }
//    }
}
