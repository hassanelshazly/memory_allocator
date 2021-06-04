import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    implicitWidth: 128
    implicitHeight: holeLabel.implicitHeight
    color: row % 2 == 0 ? "#f2f2f2" : "#ffffff"

    Label {
        id: holeLabel
        anchors { verticalCenter: parent.verticalCenter; left: parent.left }
        padding: 4
        text: display
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            holeLoader.visible = true
            holeLoader.item.forceActiveFocus()
        }
    }

    Loader {
        id: holeLoader
        anchors { verticalCenter: parent.verticalCenter; left: parent.left}
        height: parent.height
        width: parent.width
        visible: false
        sourceComponent: visible ? holeInput : undefined

        Component {
            id: holeInput
            TextField {
                anchors { fill: parent }
                text: display
                onAccepted:{
                    edit = text
                    holeLoader.visible = false
                }

                onActiveFocusChanged: {
                    if (!activeFocus) {
                        holeLoader.visible = false
                    }
                }
            }
        }
    }
}
