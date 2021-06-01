import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import dev.unordered_team.os_mem_viz 0.1

Button {
    id: tableButton
    text: displayValue
    onClicked: console.log(buttonColor)

    contentItem: Text {
        text: tableButton.text
        font: tableButton.font
        opacity: enabled ? 1.0 : 0.3
        color: tableButton.down ? buttonColorPressed : buttonColor
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 64
        implicitHeight: 0
        opacity: enabled ? 1 : 0.3
        border.color: tableButton.down ? "#a8171a" : buttonColor
        border.width: 1
        radius: 2
    }
}
