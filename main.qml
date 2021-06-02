import QtCharts 2.15
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    width: 1080
    height: 720

    signal addNewHole()
    signal addNewSegment()
    signal addNewProcess()

    signal setup()
    signal compact()

    RowLayout {
        anchors.fill: parent

        StackLayout {
            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height

            currentIndex: controller.stageNumber

            GridLayout {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height

                Label {
                    text: "Total Memory Size:"

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 0
                    Layout.column: 0
                    Layout.margins: 4

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                TextField {
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 0
                    Layout.column: 1
                    Layout.margins: 4
                }

                Label {
                    text: "Holes"

                    Layout.alignment: Qt.AlignRight
                    Layout.preferredWidth: implicitWidth
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 1
                    Layout.column: 0
                    Layout.margins: 4
                }

                Button {
                    text: "Add New Hole"
                    onClicked: root.addNewHole()

                    Layout.alignment: Qt.AlignLeft
                    Layout.preferredWidth: implicitWidth
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 1
                    Layout.column: 1
                    Layout.margins: 4
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

                    model: controller.holeModel

                    delegate: Component {
                        Loader {
                            id: holeTableLoader

                            property string displayValue: display

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

                Button {
                    text: "Setup"
                    onClicked: root.setup()

                    Layout.preferredWidth: parent.width - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 4
                    Layout.column: 0
                    Layout.columnSpan: 2
                    Layout.margins: 4
                }
            }

            GridLayout {
                Layout.preferredWidth: parent.width
                Layout.preferredHeight: parent.height

                Label {
                    text: "Segments"

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 0
                    Layout.column: 0
                    Layout.margins: 4

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Button {
                    text: "Add New Segment"
                    onClicked: root.addNewSegment()

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 0
                    Layout.column: 1
                    Layout.margins: 4
                }

                HorizontalHeaderView {
                    syncView: segmentTable

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: segmentTable.width
                    Layout.preferredHeight: 27
                    Layout.row: 1
                    Layout.column: 0
                    Layout.columnSpan: 2
                }

                TableView {
                    id: segmentTable
                    clip: true

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: 96 * 2 + 64
                    Layout.fillHeight: true
                    Layout.row: 2
                    Layout.column: 0
                    Layout.columnSpan: 2

                    model: controller.segmentModel

                    delegate: Component {
                        Loader {
                            id: segmentTableLoader

                            property string displayValue: display

                            source: switch(column) {
                                    case 0:
                                    case 1:
                                        return "TextCell.qml"
                                    case 2:
                                        return "ButtonCell.qml"
                                    }
                        }
                    }
                }

                Button {
                    text: "Add Process"
                    onClicked: root.addNewProcess()

                    Layout.alignment: Qt.AlignHCenter
                    Layout.preferredWidth: parent.width
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 3
                    Layout.column: 0
                    Layout.columnSpan: 2
                }

                Label {
                    text: "Processes"

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
                    Layout.preferredWidth: 96 * 1 + 64
                    Layout.fillHeight: true
                    Layout.row: 6
                    Layout.column: 0
                    Layout.columnSpan: 2

                    model: controller.processModel

                    delegate: Component {
                        Loader {
                            id: processTableLoader

                            property string displayValue: display

                            source: switch(column) {
                                    case 0:
                                        return "TextCell.qml"
                                    case 1:
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
                    text: "Compact"

                    Layout.preferredWidth: parent.width - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 8
                    Layout.column: 0
                    Layout.columnSpan: 2
                    Layout.margins: 4
                }
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
