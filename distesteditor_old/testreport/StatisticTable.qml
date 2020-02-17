import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import QtCharts 2.2

Item {
    id: item

    property var tableModel
    property int successCount
    property int failCount
    property int excludetCount
    property int notExecutedCount
    property int statisticTableColumn1Width: 70
    property int statisticTableColumn2Width: 60

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Rectangle{
            id: headlineStatistic
            color: "steelblue"
            border.color: "grey"
            Text{
                id: textHeadlineStatistic
                text: "Statistics"
                color: "white"
                font.pointSize: 12; font.bold: true
            }

            Layout.fillWidth: true
            height: textHeadlineStatistic.height
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
            RowLayout{
                anchors.fill: parent
                spacing: 0

                TableView  {
                    id: statisticTable

                    headerVisible: false
                    alternatingRowColors: false

                    Layout.maximumWidth: 220
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    TableViewColumn{
                        width: statisticTableColumn1Width
                        role: "0"
                        title: "column1"
                    }
                    TableViewColumn{
                        width: statisticTableColumn2Width
                        role: "1"
                        title: "column2"
                    }
                    model: tableModel
                }
                Rectangle{
                    border.color: "grey"
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    width: 300//item.height - headlineStatistic.height

                    ChartView{
                        id: chart
                        width: parent.width - 5
                        height: parent.height
                        //theme: ChartView.ChartThemeLight
                        antialiasing: true
                        anchors.margins: 0
                        //legend.visible: false
                        legend.alignment: Qt.AlignRight

                        PieSeries {
                            id: pieSeries
                            PieSlice { label: "Succeeded"; value: successCount; color: "green"; }
                            PieSlice { label: "Failed"; value: failCount; color: "red"; }
                            PieSlice { label: "Not Executed"; value: notExecutedCount; color: "orange"; }
                            PieSlice { label: "Excludet"; value: excludetCount; color: "#00CD00"; }//"grey
                        }
                    }
                }

            }
        }

    }
}
