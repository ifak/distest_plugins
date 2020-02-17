include($$PWD/../distest_config.pri)

DEFINES += DISTESTPROJECT_LIBRARY

PROVIDER = ifak

include(distestproject_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

# distestproject files

SOURCES += \
    distestprojectplugin.cpp \
    distestproject.cpp \
    distestprojectwizard.cpp \
    comsavedistestobjectasqml.cpp \
    combuildtestmodel.cpp \
    helpers.cpp \
    clickablelabel.cpp \
    sutsettings.cpp \
    testcasesettings.cpp \
    testsystemsettings.cpp \
    distestconfiguration.cpp \
    globalrendersettings.cpp \
#    combuildtestreport.cpp \
    distestcasewizard.cpp \
    distestruntime/distestcase.cpp \
    distestruntime/distestcomponent.cpp \
    distestruntime/distestcomponentlocal.cpp \
    distestruntime/distestcomponentlocalservice.cpp \
    distestruntime/localtestcomponent.cpp \
    distestbuildconfiguration.cpp \
    distestrunconfiguration.cpp \
    distestruncontrol.cpp \
    distestruntime/distestresult.cpp \
    testreportbuilder.cpp \
    testreporttablemodel.cpp \
    distestprojectmodel.cpp \
    distestsuite.cpp \
    distestbuildstep.cpp \
    distestcleanbuildstep.cpp \
    distestrendermanager.cpp \
    distestrendersettings.cpp \
    testreportgraphicdocument.cpp \
    testreportgraphiceditor.cpp \
    testreportgraphicfactory.cpp \
    distestmodelbuildstep.cpp \
    distestruntime/distestsuiteruntime.cpp \
    distestruntime/distestruntime.cpp \
    testexecutionview.cpp \
    combuilddistestruntime.cpp

HEADERS += \
    distestprojectconstants.hpp \
    distestprojectplugin.hpp \
    distestproject_global.hpp \
    distestproject.hpp \
    distestprojectwizard.hpp \
    comsavedistestobjectasqml.hpp \
    combuildtestmodel.hpp \
    helpers.hpp \
    clickablelabel.hpp \
    sutsettings.hpp \
    testcasesettings.hpp \
    testsystemsettings.hpp \
    distestconfiguration.hpp \
    globalrendersettings.hpp \
#    combuildtestreport.hpp \
    distestcasewizard.hpp \
    distestruntime/distestcase.hpp \
    distestruntime/distestcomponent.hpp \
    distestruntime/distestcomponentlocal.hpp \
    distestruntime/distestcomponentlocalservice.hpp \
    distestruntime/localtestcomponent.hpp \
    distestbuildconfiguration.hpp \
    distestrunconfiguration.hpp \
    distestruncontrol.hpp \
    distestruntime/distestresult.hpp \
    testreportbuilder.hpp \
    testreporttablemodel.hpp \
    distestprojectmodel.hpp \
    distestsuite.hpp \
    distestbuildstep.hpp \
    distestcleanbuildstep.hpp \
    distestrendermanager.hpp \
    distestrendersettings.hpp \
    testreportgraphicdocument.hpp \
    testreportgraphiceditor.hpp \
    testreportgraphicfactory.hpp \
    distestmodelbuildstep.hpp \
    distestruntime/distestsuiteruntime.hpp \
    distestruntime/distestruntime.hpp \
    testexecutionview.hpp \
    combuilddistestruntime.hpp


OTHER_FILES += \
    distestproject.pluginspec.in \
    project_default.decl \
    project_default.sut \
    project_default_testcase_1.testcase \
    project_default_testcase_2.testcase \
    project_default.testsystem \
    distestproject.json

RESOURCES += \
    distestproject.qrc

DISTFILES += \
    testreport/Headline.qml \
    testreport/StatisticTable.qml \
    testreport/TestCasesTable.qml \
    testreport/Testreport.qml \
    testreport/TestSuiteTable.qml \
    distestproject.mimetypes.xml \
    project_default_newtestcase.testcase

FORMS += \
    sutsettingspage.ui \
    testcasesettingspage.ui \
    testsystemsettingspage.ui \
    distestsettingspropertiespage.ui
