import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12


    Item{
        property var barColor : "grey"

        ColumnLayout {
            id: headlineLayout
            anchors.fill: parent
            anchors.margins: 0
            spacing: 0

            Rectangle{
                id: blueBar
                Layout.fillWidth: true
                height: parent.height * 0.9
                color: "steelblue"

                Text {
                    id: bigHeadline
                    text: "Testrun Result Overview - test suite"
                    font.pointSize: 20; font.bold: true
                    color: "white"
                }
        }

        Rectangle{
            id: indicatorBar
            width: parent.width
            Layout.fillWidth: true
            height: parent.height * 0.1
            color: headline.barColor//(testSuccessful) ? "green" :  "red"
        }
    }
    }
