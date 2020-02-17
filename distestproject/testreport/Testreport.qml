import QtQuick 2.7
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.12
import QtQml 2.2

Item {
  id: window
  visible: true
  width: 800
  height: 600

  //    property bool rearrangeTables: (window.width < testSuiteTable.testSuiteTableColumn1Width + testSuiteTable.testSuiteTableColumn2Width + statisticTable.statisticTableColumn1Width + statisticTable.statisticTableColumn2Width)
  //                             ? true
  //                             : false
  //    property bool testSuiteTableIsMinimal: (1/3 * window.width < testSuiteTable.testSuiteTableColumn1Width + testSuiteTable.testSuiteTableColumn2Width)
  //                                           ? true
  //                                           : false


  ColumnLayout{
    anchors.fill: parent

    anchors.margins: 3
    spacing: 5

    Headline{
      id: headline

      Layout.fillWidth: true
      height: 50

      barColor: (handler.getFailedCount() > 0) ?  "red" : "green"
    }

    Item{
      RowLayout{
        anchors.fill: parent
        anchors.margins: 0
        spacing: 5

        TestSuiteTable{
          id: testSuiteTable

          tableModel: testSuiteModel
          Layout.maximumWidth: 250
          Layout.fillWidth: true
          height:250
        }
        StatisticTable{
          id: statisticTable

          tableModel: statisticModel

          Layout.fillWidth: true
          height:250

          successCount: handler.getSucceededCount()
          failCount: handler.getFailedCount()
          excludetCount: handler.getExcludetCount()
          notExecutedCount: handler.getNotExecutedCount()

        }


      }
      Layout.fillWidth: true
      height: statisticTable.height //(rearrangeTables) ? testSuiteTable.height + statisticTable.height : statisticTable.height

    }



    TestCasesTable{
      id: testCasesTable

      tableModel: testCasesModel

      Layout.fillWidth: true
      Layout.fillHeight: true
    }
  }
}


