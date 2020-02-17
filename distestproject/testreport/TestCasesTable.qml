import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12

Item{
    id: item

    property var tableModel

    ListModel{
        id: testCasesTableModel
    }

    //height: headlineTestCases.height + testCasesTable.height
    Layout.fillHeight: true

    ColumnLayout{
        anchors.fill: parent
        spacing: 0

        Rectangle{
            id: headlineTestCases
            color: "steelblue"
            border.color: "grey"

            Text{
                id: textheadlineTestCases
                color: "white"
                text: "Test Cases"
                font.pointSize: 12; font.bold: true
            }
            Layout.fillWidth: true
            height: textheadlineTestCases.height
        }

        TableView  {
            id: testCasesTable

            alternatingRowColors: false

            //width: headlineTestCases.width
            Layout.fillHeight: true
            Layout.fillWidth: true

            TableViewColumn{
                width: 40
                role: "one"
                title: "No"
            }
            TableViewColumn{
                width: 60
                role: "two"
                title: "Result"
            }
            TableViewColumn{
                width: 200
                role: "three"
                title: "Name"
            }
            TableViewColumn{
                width: 250
                role: "four"
                title: "Filename"
            }
            model: tableModel
        }
    }
}


