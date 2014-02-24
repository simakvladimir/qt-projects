import QtQuick 2.0
//import ModuleName 1.0

Item {
    id: root

    width: 300
    height: 400

    Connections {
        target: Wrapper
        onCalculateFinish:{

            busyIndicator.visible = false
            menuPanel.state = ""

            menuPanel.appThread = Wrapper.get_thread_number()
            menuPanel.startTime = Wrapper.get_start_time()
            menuPanel.finishTime = Wrapper.get_finish_time()
            menuPanel.durationTime = Wrapper.get_duration_time()
            menuPanel.ticketsNumber = Wrapper.get_counter()
            menuPanel.cpuModel = Wrapper.get_cpu_brand()
            menuPanel.cpuCores = Wrapper.get_cpu_numbers()
        }
    }

    Image {
        id: main
        source: "content/images/background.jpg"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            menuPanel.state = "hide"
        }
    }


    Column{
        width: parent.width
        y: 16

        Indicator{
            id: cpuInd
            width: parent.width
            caption: "Количество потоков:"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Slider {
            id: cpuNumberSlider
            minimum: 1
            maximum: Wrapper.get_cpu_numbers()
            onValueChanged: cpuInd.value = value;
        }

        Indicator{
            id: digitInd
            width: parent.width
            value: 0
            caption: "Количество знаков:"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Slider {
            id: digitNumberSlider
            step: 2
            minimum: 0
            maximum: 18
            onValueChanged: digitInd.value = value;
        }

        BusyIndicator {
            id: busyIndicator
            size: "medium"
            anchors.horizontalCenter: parent.horizontalCenter
            height: 130
            running: true
            invertedTheme: Math.floor(Math.random()+0.5)
            visible: false
        }

    }

    Button {
        id: buttonMainMenu
        height: 40
        width: parent.width - 200
        y:root.height - 70
        anchors.horizontalCenter: parent.horizontalCenter;
//        anchors.bottom: root.bottom;
//            anchors.bottomMargin: 100
        text: "Начать"
        onClicked: {
            Wrapper.set_thread_number( cpuNumberSlider.value )
            Wrapper.set_digit( digitNumberSlider.value )
            Wrapper.create_range_by_digit( digitNumberSlider.value )
            Wrapper.calculate()
            busyIndicator.visible = true
        }
    }

    Rectangle {
        id: gameViewHider
        anchors.fill: parent
        color: "black"
        opacity: 0.7

        states: [
        State {
            name: "hide"
            when: menuPanel.state == "hide"
            PropertyChanges {
                target: gameViewHider
                opacity: 0.0
            }
        }
        ]

        transitions: Transition {
            NumberAnimation {
                properties: "opacity"
                duration: 400
            }
        }
    }

    // *** Main Menu panel ***
    Info {
        id: menuPanel
        state: "hide"
    }

}
