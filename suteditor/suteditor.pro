include($$PWD/../distest_config.pri)

DEFINES += SUTEDITOR_LIBRARY

PROVIDER = ifak

include(suteditor_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250

#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

# suteditor files

DISTFILES += \
    suteditor.json \
    suteditor.mimetypes.xml \
    suteditor.pluginspec.in \
    examples/sut/sut_example_01.sut

RESOURCES += \
    suteditor.qrc

HEADERS += \
    combuildsutoutlinemodel.hpp \
    sutcompletionassist.hpp \
    sutdocument.hpp \
    suteditor_global.hpp \
    suteditor.hpp \
    suteditorconstants.hpp \
    suteditorfactory.hpp \
    suteditoroutline.hpp \
    suteditorplugin.hpp \
    suteditorwidget.hpp \
    suthoverhandler.hpp \
    sutoutlinemodel.hpp \
    sutgraphicdocument.hpp \
    sutgraphiceditor.hpp \
    sutgraphicfactory.hpp \
    sutgraphicwidget.hpp

SOURCES += \
    combuildsutoutlinemodel.cpp \
    sutcompletionassist.cpp \
    sutdocument.cpp \
    suteditor.cpp \
    suteditorfactory.cpp \
    suteditoroutline.cpp \
    suteditorplugin.cpp \
    suteditorwidget.cpp \
    suthoverhandler.cpp \
    sutoutlinemodel.cpp \
    sutgraphicdocument.cpp \
    sutgraphiceditor.cpp \
    sutgraphicfactory.cpp \
    sutgraphicwidget.cpp

win32*{
  copyexamples.commands = $(COPY_DIR) \"$$shell_path($$PWD/examples/sut)\" \"$$shell_path($$IDE_APP_PATH/examples/sut)\"
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
} else {
  copyexamples.commands = $(COPY_DIR) $$PWD/examples/sut $$IDE_APP_PATH/examples
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
}
