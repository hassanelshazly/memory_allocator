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

    Pane {
        anchors.fill: parent
        focusPolicy: Qt.ClickFocus
    }

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
                    id: memorySizeInput
                    text: controller.memorySize
                    validator: IntValidator {bottom: 0; top: 2147483647;}
                    focus: true

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 0
                    Layout.column: 1
                    Layout.margins: 4

                    onEditingFinished: controller.memorySize = memorySizeInput.text
                    Keys.onPressed: {
                        if (event.key == Qt.Key_Escape) {
                            focus = false
                            event.accepted = true;
                        }
                    }
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
                    Layout.preferredWidth: 128 * 2 + 128
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
                                        return "TextCell.qml"
                                    case 2:
                                        return "ButtonCell.qml"
                                    }
                        }
                    }
                }

                Label {
                    text: controller.status

                    Layout.preferredWidth: parent.width - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 4
                    Layout.column: 0
                    Layout.columnSpan: 2
                    Layout.margins: 4

                    horizontalAlignment: Text.AlignHCenter
                }

                Button {
                    text: "Setup"
                    onClicked: root.setup()

                    Layout.preferredWidth: parent.width - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 5
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
                    Layout.preferredWidth: 128 * 2 + 128
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
                    Layout.preferredWidth: parent.width - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 3
                    Layout.column: 0
                    Layout.columnSpan: 2
                    Layout.margins: 4
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
                    Layout.preferredWidth: 128 * 3 + 128
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
                                    case 1:
                                    case 2:
                                        return "TextCell.qml"
                                    case 3:
                                        return "ButtonCell.qml"
                                    }
                        }
                    }
                }

                ComboBox {
                    model: ["First Fit", "Best Fit", "Worst Fit"]

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 7
                    Layout.column: 0
                    Layout.margins: 4

                    currentIndex: controller.allocationType
                    onActivated: controller.allocationType = currentIndex
                }

                Label {
                    text: controller.status

                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredWidth: parent.width / 2 - 16
                    Layout.preferredHeight: implicitHeight
                    Layout.row: 7
                    Layout.column: 1
                    Layout.margins: 4

                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }

                Button {
                    text: "Compact"
                    onClicked: root.compact()

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
            antialiasing: true
            animationOptions: ChartView.AllAnimations
            theme: ChartView.ChartThemeBrownSand
            legend.alignment: Qt.AlignBottom

            Layout.preferredWidth: parent.width / 2
            Layout.preferredHeight: parent.height

            ValueAxis {
                id: addressAxis
                min: 0
                max: controller.memorySize
                tickType: ValueAxis.TicksFixed
                tickCount: 21
                reverse: true
            }

            StackedBarSeries {
                id: timelineSeries
                axisX: BarCategoryAxis { categories: ["Memory"] }
                axisY: addressAxis

                labelsVisible: true
                labelsPosition: AbstractBarSeries.LabelsCenter

                HBarModelMapper {
                    model: controller.timelineModel
                    firstBarSetRow: 0
                    lastBarSetRow: 2147483647
                    firstColumn: 0
                    columnCount: 1
                }

                onCountChanged: {
                    const ids = controller.timelineModel.ids()
                    let holeColor = undefined;
                    for (let i = 0; i < timelineSeries.count; i++) {
                        if (ids[i] === -1) {
                            if (holeColor) {
                                timelineSeries.at(i).color = holeColor;
                            } else {
                                holeColor = timelineSeries.at(i).color
                            }
                        }
                    }
                }
            }
        }
    }
}
