DISTESTPROJECT_VERSION=0.1

isEmpty(3RD_PATH) {
3RD_PATH = $$PWD/../../../3rd
}

MOBATA_LIBRARY_TYPE = staticlib
include($${3RD_PATH}/mobata/mobata/mobata.pri)

MOBATAWIDGETS_LIBRARY_TYPE = staticlib
include($${3RD_PATH}/mobata/libs/mobatawidgets/mobatawidgets.pri)

DSLPARSER_LIBRARY_TYPE = staticlib
include($${3RD_PATH}/mobata/libs/dslparser/dslparser/dslparser.pri)

QJSONRPC_LIBRARY_TYPE = $$MOBATA_LIBRARY_TYPE
include($${3RD_PATH}/mobata/3rd/ifak_qjsonrpc/ifak_qjsonrpc_static.pri)

QT += qml
QT += quickcontrols2
QT += xml
QT += quickwidgets

QTC_PLUGIN_NAME = distestproject

QTC_PLUGIN_DEPENDS += \
    projectexplorer \
    testcaseeditor
