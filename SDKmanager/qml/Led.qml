import QtQuick 2.0

Item {
    id: root

    property color ledColor: Qt.rgba(1.0, 1.0, 0.0, 1.0);
    property real  depthLight: 1.0
//    anchors.fill: parent

    width: 20
    height: 50

//    Image {
//        id: ledBackground
//        source: "images/led_bg.png"
//        visible: true
//    }

    Image {
        id: ledOn
        source: "images/led_on.png"
        visible: true
    }

    ShaderEffect {
        id: shaderItem
        property variant source: ShaderEffectSource { sourceItem: ledOn; hideSource: true }
        property alias ledColor: root.ledColor
        property alias ledDepth: root.depthLight
        anchors.fill: ledOn

        fragmentShader: "
            varying highp vec2 qt_TexCoord0;
            uniform highp float qt_Opacity;
            uniform highp vec4 ledColor;
            uniform lowp  float ledDepth;
            uniform sampler2D source;
            void main(void) {
                highp vec4 tex = texture2D(source, qt_TexCoord0);
                highp vec4 color = mix(ledColor, tex, ledDepth );
                gl_FragColor = tex * color;
        }
        "

    }

    Behavior on  depthLight {
          NumberAnimation { duration: 500 }
      }

}
