DISTESTEDITOR_VERSION=0.1

include($${3RD_PATH}/mobata/mobata/mobata.pri)
include($${3RD_PATH}/mobata/libs/mobatawidgets/mobatawidgets.pri)

QTC_PLUGIN_NAME = distesteditor

QT += quickwidgets

QTC_LIB_DEPENDS += \
    aggregation \
    extensionsystem \
    languageutils \
    utils

QTC_PLUGIN_DEPENDS += \
    dsleditor
