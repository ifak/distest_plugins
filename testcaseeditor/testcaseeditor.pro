include($$PWD/../distest_config.pri)

DEFINES += TESTCASEEDITOR_LIBRARY

PROVIDER = ifak

include(testcaseeditor_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250 -wd4267
win64-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250 -wd4267

#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

# testcaseeditor files

DISTFILES += \
    testcaseeditor.json \
    testcaseeditor.mimetypes.xml \
    testcaseeditor.pluginspec.in \
    examples/testcase/testcase_example_01.testcase

RESOURCES += \
    testcaseeditor.qrc

HEADERS += \
    combuildtestcaseoutlinemodel.hpp \
    testcasecompletionassist.hpp \
    testcasedocument.hpp \
    testcaseeditor_global.hpp \
    testcaseeditor.hpp \
    testcaseeditorconstants.hpp \
    testcaseeditorfactory.hpp \
    testcaseeditoroutline.hpp \
    testcaseeditorplugin.hpp \
    testcaseeditorwidget.hpp \
    testcasehoverhandler.hpp \
    testcaseoutlinemodel.hpp \
    testcasegraphicdocument.hpp \
    testcasegraphiceditor.hpp \
    testcasegraphicfactory.hpp \
    testcasegraphicwidget.hpp \
    testcasegraphicoutline.hpp \
    testcaseeditorstepsettingspage.hpp \
    testcaseeditorbackgroundsettingspage.hpp \
    testcaseeditorsettingspage.hpp \
    testcasepreviewgraph.hpp

SOURCES += \
    combuildtestcaseoutlinemodel.cpp \
    testcasecompletionassist.cpp \
    testcasedocument.cpp \
    testcaseeditor.cpp \
    testcaseeditorfactory.cpp \
    testcaseeditoroutline.cpp \
    testcaseeditorplugin.cpp \
    testcaseeditorwidget.cpp \
    testcasehoverhandler.cpp \
    testcaseoutlinemodel.cpp \
    testcasegraphicdocument.cpp \
    testcasegraphiceditor.cpp \
    testcasegraphicfactory.cpp \
    testcasegraphicwidget.cpp \
    testcasegraphicoutline.cpp \
    testcaseeditorstepsettingspage.cpp \
    testcaseeditorbackgroundsettingspage.cpp \
    testcaseeditorsettingspage.cpp

win32*{
  copyexamples.commands = $(COPY_DIR) \"$$shell_path($$PWD/examples/testcase)\" \"$$shell_path($$IDE_APP_PATH/examples/testcase)\"
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
} else {
  copyexamples.commands = $(COPY_DIR) $$PWD/examples/testcase $$IDE_APP_PATH/examples
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
}

FORMS += \
    testcaseeditorstepsettings.ui \
    testcaseeditorbackgroundsettings.ui
