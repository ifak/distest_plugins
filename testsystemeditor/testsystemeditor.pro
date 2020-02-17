include($$PWD/../distest_config.pri)

DEFINES += TESTSYSTEMEDITOR_LIBRARY

PROVIDER = ifak

include(testsystemeditor_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

# testsystemeditor files

win32*{
  copyexamples.commands = $(COPY_DIR) \"$$shell_path($$PWD/examples/testsystem)\" \"$$shell_path($$IDE_APP_PATH/examples/testsystem)\"
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
} else {
  copyexamples.commands = $(COPY_DIR) $$PWD/examples/testsystem $$IDE_APP_PATH/examples
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
}

DISTFILES += \
    examples/testsystem/testsystem_example_01.testsystem \
    testsystemeditor.json \
    testsystemeditor.mimetypes.xml \
    testsystemeditor.pluginspec.in

RESOURCES += \
    testsystemeditor.qrc

HEADERS += \
    combuildtestsystemoutlinemodel.hpp \
    testsystemcompletionassist.hpp \
    testsystemdocument.hpp \
    testsystemeditor_global.hpp \
    testsystemeditor.hpp \
    testsystemeditorconstants.hpp \
    testsystemeditorfactory.hpp \
    testsystemeditoroutline.hpp \
    testsystemeditorplugin.hpp \
    testsystemeditorwidget.hpp \
    testsystemhoverhandler.hpp \
    testsystemoutlinemodel.hpp \
    testsystemgraphicdocument.hpp \
    testsystemgraphiceditor.hpp \
    testsystemgraphicfactory.hpp \
    testsystemgraphicwidget.hpp

SOURCES += \
    combuildtestsystemoutlinemodel.cpp \
    testsystemcompletionassist.cpp \
    testsystemdocument.cpp \
    testsystemeditor.cpp \
    testsystemeditorfactory.cpp \
    testsystemeditoroutline.cpp \
    testsystemeditorplugin.cpp \
    testsystemeditorwidget.cpp \
    testsystemhoverhandler.cpp \
    testsystemoutlinemodel.cpp \
    testsystemgraphicdocument.cpp \
    testsystemgraphiceditor.cpp \
    testsystemgraphicfactory.cpp \
    testsystemgraphicwidget.cpp
