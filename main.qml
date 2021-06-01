import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import dev.unordered_team.os_mem_viz 0.1

Item {
    id: root
    width: 1080
    height: 720

    property var holeModel
    property var processModel

    signal addNewHole()
    signal addNewProcess()

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

                Layout.alignment: Qt.AlignRight
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 1
                Layout.column: 0
            }

            Button {
                text: "Add New Hole"
                padding: 4
                onClicked: root.addNewHole()

                Layout.alignment: Qt.AlignLeft
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 1
                Layout.column: 1
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
                Layout.preferredWidth: 96 * 3 + 64
                Layout.fillHeight: true
                Layout.row: 3
                Layout.column: 0
                Layout.columnSpan: 2

                model: root.holeModel

                delegate: Component {
                    Loader {
                        id: holeTableLoader

                        property string displayValue: display
                        property color buttonColor: "#be212b"
                        property color buttonColorPressed: "#a8171a"

                        source: switch(column) {
                                case 0:
                                case 1:
                                case 2:
                                    return "TextCell.qml"
                                case 3:
                                    return "ButtonCell.qml"
                                }
                    }
                }
            }

            Label {
                text: "Processes"
                padding: 4

                Layout.alignment: Qt.AlignRight
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 4
                Layout.column: 0
            }

            Button {
                text: "Add New Process"
                padding: 4
                onClicked: root.addNewProcess()

                Layout.alignment: Qt.AlignLeft
                Layout.preferredWidth: implicitWidth
                Layout.preferredHeight: implicitHeight
                Layout.row: 4
                Layout.column: 1
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
                Layout.preferredWidth: 96 * 3 + 64 * 2
                Layout.fillHeight: true
                Layout.row: 6
                Layout.column: 0
                Layout.columnSpan: 2

                model: root.processModel

                delegate: Component {
                    Loader {
                        id: processTableLoader

                        property string displayValue: display
                        property color buttonColor: (column == 3) ? "#21be2b" : "#be212b"
                        property color buttonColorPressed: (column == 3) ? "#17a82b" : "#a8171a"

                        source: switch(column) {
                                case 0:
                                case 1:
                                case 2:
                                    return "TextCell.qml"
                                case 3:
                                case 4:
                                    return "ButtonCell.qml"
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
