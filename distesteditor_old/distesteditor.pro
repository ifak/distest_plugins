include($$PWD/../distest_config.pri)

DEFINES += DISTESTEDITOR_LIBRARY

PROVIDER = ifak

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

include(distesteditor_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)
LIBS -=

HEADERS += \
    distesteditor_global.hpp \
    distesteditorconstants.hpp \
    distesteditorplugin.hpp \
    sutdocument.hpp \
    suteditor.hpp \
    suteditorfactory.hpp \
    tsmodelproperty.hpp \
    testsystemdocument.hpp \
    testsystemeditor.hpp \
    testsystemeditorfactory.hpp \
    decldocument.hpp \
    decleditor.hpp \
    decleditorfactory.hpp \
    distestmodeloutline.hpp \
    distestdslautocompleter.hpp \
    distestdslhighlighter.hpp \
    distestdslindenter.hpp \
    distestdslcodeformatter.hpp \
    suteditorhighlighter.hpp \
    testsystemeditorhighlighter.hpp \
    testcasedocument.hpp \
    testcaseeditor.hpp \
    testcaseeditorfactory.hpp \
    testcaseeditorhighlighter.hpp \
    testsuitedocument.hpp \
    testsuiteeditor.hpp \
    testsuiteeditorfactory.hpp \
    testsuiteeditorhighlighter.hpp \
    decleditorwidget.hpp \
    suteditorwidget.hpp \
    testcaseeditorwidget.hpp \
    testsuiteeditorwidget.hpp \
    testsystemeditorwidget.hpp \
    testcasegraphiceditor.hpp \
    testcasegraphicfactory.hpp \
    testcasegraphicwidget.hpp \
    testcasegraphicdocument.hpp \
    sutgraphiceditor.hpp \
    sutgraphicwidget.hpp \
    sutgraphicdocument.hpp \
    testsystemgraphicdocument.hpp \
    testsystemgraphiceditor.hpp \
    testsystemgraphicwidget.hpp \
    sutgraphicfactory.hpp \
    testsystemgraphicfactory.hpp \
    distestrendersettings.hpp \
    distestrendermanager.hpp \
    testreportgraphicfactory.hpp \
    testreportgraphiceditor.hpp \
    testreportgraphicdocument.hpp

SOURCES += \
    distesteditorplugin.cpp \
    tsmodelproperty.cpp \
    sutdocument.cpp \
    suteditor.cpp \
    suteditorfactory.cpp \
    testsystemdocument.cpp \
    testsystemeditor.cpp \
    testsystemeditorfactory.cpp \
    decldocument.cpp \
    decleditor.cpp \
    decleditorfactory.cpp \
    distestmodeloutline.cpp \
    distestdslautocompleter.cpp \
    distestdslhighlighter.cpp \
    distestdslindenter.cpp \
    distestdslcodeformatter.cpp \
    suteditorhighlighter.cpp \
    testsystemeditorhighlighter.cpp \
    testcasedocument.cpp \
    testcaseeditor.cpp \
    testcaseeditorfactory.cpp \
    testcaseeditorhighlighter.cpp \
    testsuitedocument.cpp \
    testsuiteeditor.cpp \
    testsuiteeditorfactory.cpp \
    testsuiteeditorhighlighter.cpp \
    decleditorwidget.cpp \
    suteditorwidget.cpp \
    testsuiteeditorwidget.cpp \
    testsystemeditorwidget.cpp \
    testcasegraphiceditor.cpp \
    testcasegraphicfactory.cpp \
    testcasegraphicwidget.cpp \
    testcasegraphicdocument.cpp \
    testcaseeditorwidget.cpp \
    sutgraphiceditor.cpp \
    sutgraphicwidget.cpp \
    sutgraphicdocument.cpp \
    testsystemgraphicdocument.cpp \
    testsystemgraphiceditor.cpp \
    testsystemgraphicwidget.cpp \
    sutgraphicfactory.cpp \
    testsystemgraphicfactory.cpp \
    distestrendersettings.cpp \
    distestrendermanager.cpp \
    testreportgraphicfactory.cpp \
    testreportgraphiceditor.cpp \
    testreportgraphicdocument.cpp

OTHER_FILES += \
    distesteditor.mimetypes.xml \
    distesteditor.pri \
    distesteditor.pluginspec.in \
    defaultStyleSheets.txt

RESOURCES += \
    distesteditor.qrc
