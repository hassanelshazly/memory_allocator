import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import dev.unordered_team.os_mem_viz 0.1

Window {
    width: 800
    height: 600
    visible: true
    title: "Memory Allocation"

    RowLayout {
        anchors.fill: parent

        GridLayout {
            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height

            Label {
                text: "Total Memory Size:"

                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: parent.width / 2 - 16
                Layout.preferredHeight: implicitHeight
                Layout.row: 0
                Layout.column: 0
                Layout.margins: 4

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            TextField {
                Layout.alignment: Qt.AlignCenter
                Layout.preferredWidth: parent.width / 2 - 16
                Layout.preferredHeight: implicitHeight
                Layout.row: 0
                Layout.column: 1
                Layout.margins: 4
            }

            Label {
                text: "Holes"
                padding: 4

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 1
                Layout.column: 0
                Layout.columnSpan: 2
            }

            HorizontalHeaderView {
                syncView: holeTable

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: holeTable.width
                Layout.preferredHeight: 27
                Layout.row: 2
                Layout.column: 0
                Layout.columnSpan: 2
            }

            TableView {
                id: holeTable
                clip: true

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 128 * 3
                Layout.fillHeight: true
                Layout.row: 3
                Layout.column: 0
                Layout.columnSpan: 2

                model: HoleModel {}

                delegate: Rectangle {
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
            }

            Label {
                text: "Processes"
                padding: 4

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 4
                Layout.column: 0
                Layout.columnSpan: 2
            }

            HorizontalHeaderView {
                syncView: processTable

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: processTable.width
                Layout.preferredHeight: 27
                Layout.row: 5
                Layout.column: 0
                Layout.columnSpan: 2
            }

            TableView {
                id: processTable
                clip: true

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 128 * 3
                Layout.fillHeight: true
                Layout.row: 6
                Layout.column: 0
                Layout.columnSpan: 2

                model: ProcessModel {}

                delegate: Rectangle {
                    implicitWidth: 128
                    implicitHeight: processLabel.implicitHeight
                    color: row % 2 == 0 ? "#f2f2f2" : "#ffffff"

                    Label {
                        id: processLabel
                        anchors { verticalCenter: parent.verticalCenter; left: parent.left }
                        padding: 4
                        text: display
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            processLoader.visible = true
                            processLoader.item.forceActiveFocus()
                        }
                    }

                    Loader {
                        id: processLoader
                        anchors { verticalCenter: parent.verticalCenter; left: parent.left}
                        height: parent.height
                        width: parent.width
                        visible: false
                        sourceComponent: visible ? processInput : undefined

                        Component {
                            id: processInput
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
                                    processLoader.visible = false
                                }

                                onActiveFocusChanged: {
                                    if (!activeFocus) {
                                        processLoader.visible = false
                                    }
                                }
                            }
                        }
                    }
                }
            }

            ComboBox {
                model: ["First Fit", "Best Fit", "Worst Fit"]

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: 128 * 3
                Layout.preferredHeight: implicitHeight
                Layout.row: 7
                Layout.column: 0
                Layout.columnSpan: 2
            }

            Button {
                text: "Visualize"

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width / 2 - 16
                Layout.preferredHeight: implicitHeight
                Layout.row: 8
                Layout.column: 0
                Layout.margins: 4
            }

            Button {
                text: "Compact"

                Layout.alignment: Qt.AlignHCenter
                Layout.preferredWidth: parent.width / 2 - 16
                Layout.preferredHeight: implicitHeight
                Layout.row: 8
                Layout.column: 1
                Layout.margins: 4
            }
        }

        ChartView {
            title: "Memory"
            legend.alignment: Qt.AlignBottom
            antialiasing: true

            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height

            StackedBarSeries {
                axisX: BarCategoryAxis { categories: ["Memory"] }
                BarSet { label: "B Text"; values: [5] }
                BarSet { label: "B Heap"; values: [15] }
                BarSet { label: "B Stack"; values: [10] }
            }
        }
    }
}
