import QtQuick 2.0

Item {
    id: name

    height: 62
    width: 100

    property bool checked: false
    property string caption: "jumper"


    Rectangle {
        id:jumpOff
        width: parent.width
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#e1e1e1" }
            GradientStop { position: 0.466; color: "#ef1919" }
            GradientStop { position: 1.0; color: "#e0e0e0" }
        }
        border.color: "#808080"
        border.width: 2
    }

    Rectangle {
        id: jumpOn
        width: parent.width
        height: parent.height
        color: "green"
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#e1e1e1" }
            GradientStop { position: 0.466; color: "#44e82a" }
            GradientStop { position: 1.0; color: "#e0e0e0" }
        }
        border.color: "#808080"
        border.width: 2

        opacity: checked ? 1.0 : 0.0

        Behavior on opacity {
            NumberAnimation { duration: 200 }
        }
    }

    Text {
        id: jumpName
        color: "#180000"
        text: caption
        font.pointSize: 14
        style: Text.Outline
        font.underline: false
        font.bold: false
        font.italic: false
        font.family: "Verdana"
        styleColor: "#fdfdfd"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
    }

//    MouseArea{
//        width: 1000
//        height: 1000
//        onClicked: {
//            checked = !checked;
//        }
//    }
}


