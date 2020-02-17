import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3


Item {
    id: item

    property var tableModel
    property int testSuiteTableColumn1Width: 45
    property int testSuiteTableColumn2Width: 200

//    height: textHeadlineTestSuite.height + testSuiteTable.height

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Rectangle{
            id: headlineTestSuite
            color: "steelblue"
            border.color: "grey"

            Text{
                id: textHeadlineTestSuite
                text: "Test Suite"
                color: "white"
                font.pointSize: 12; font.bold: true
            }
            Layout.fillWidth: true
            height: textHeadlineTestSuite.height
        }

        TableView  {
            id: testSuiteTable

            headerVisible: false
            alternatingRowColors: false

            TableViewColumn{
                width: testSuiteTableColumn1Width
                role: "0"
                title: "  "
            }
            TableViewColumn{
                width: testSuiteTableColumn2Width
                role: "1"
                title: "   "
            }


            model: tableModel

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
