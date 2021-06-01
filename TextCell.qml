import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import dev.unordered_team.os_mem_viz 0.1

Rectangle {
    implicitWidth: 96
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
                    switch(column) {
                    case 0:
                    case 2:
                    case 3:
                        edit = parseInt(text, 10)
                        break;
                    case 1:
                        edit = text
                        break;
                    }
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
