import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Button {
    id: tableButton
    text: displayValue
    onClicked: edit = true

    contentItem: Text {
        text: tableButton.text
        font: tableButton.font
        opacity: enabled ? 1.0 : 0.3
        color: tableButton.down ? "#a8171a" : "#be212b"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 64
        implicitHeight: 0
        opacity: enabled ? 1 : 0.3
        border.color: tableButton.down ? "#a8171a" : "#be212b"
        border.width: 1
        radius: 2
    }
}
