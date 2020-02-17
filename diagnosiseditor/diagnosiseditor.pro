include($$PWD/../distest_config.pri)

DEFINES += DIAGNOSISEDITOR_LIBRARY

PROVIDER = ifak

include(diagnosiseditor_dependencies.pri)
include($$APPCREATOR_PATH/src/appcreatorplugin.pri)

win32-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250 -wd4267
win64-msvc*:QMAKE_CXXFLAGS += -wd4251 -wd4290 -wd4250 -wd4267

#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

# diagnosiseditor files

DISTFILES += \
    diagnosiseditor.json \
    diagnosiseditor_dependencies.pri \
    diagnosiseditor.mimetypes.xml \
    examples/diagnosis/denm_cancelation.components \
    examples/diagnosis/denm_cancelation.signals \
    examples/diagnosis/example_diagnosis.diagnosis \
    diagnosiseditor.pluginspec.in

RESOURCES += \
    diagnosiseditor.qrc

HEADERS += \
    combuilddiagnosisoutlinemodel.hpp \
    diagnosiscompletionassist.hpp \
    diagnosisdocument.hpp \
    diagnosiseditor.hpp \
    diagnosiseditor_global.hpp \
    diagnosiseditorconstants.hpp \
    diagnosiseditorfactory.hpp \
    diagnosiseditoroutline.hpp \
    diagnosiseditorplugin.hpp \
    diagnosiseditorwidget.hpp \
    diagnosisgraphicdocument.hpp \
    diagnosisgraphiceditor.hpp \
    diagnosisgraphicfactory.hpp \
    diagnosisgraphicwidget.hpp \
    diagnosishoverhandler.hpp \
    diagnosisoutlinemodel.hpp

SOURCES += \
    combuilddiagnosisoutlinemodel.cpp \
    diagnosiscompletionassist.cpp \
    diagnosisdocument.cpp \
    diagnosiseditor.cpp \
    diagnosiseditorfactory.cpp \
    diagnosiseditoroutline.cpp \
    diagnosiseditorplugin.cpp \
    diagnosiseditorwidget.cpp \
    diagnosisgraphicdocument.cpp \
    diagnosisgraphiceditor.cpp \
    diagnosisgraphicfactory.cpp \
    diagnosisgraphicwidget.cpp \
    diagnosishoverhandler.cpp \
    diagnosisoutlinemodel.cpp

win32*{
  copyexamples.commands = $(COPY_DIR) \"$$shell_path($$PWD/examples/diagnosis)\" \"$$shell_path($$IDE_APP_PATH/examples/diagnosis)\"
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
} else {
  copyexamples.commands = $(COPY_DIR) $$PWD/examples/diagnosis $$IDE_APP_PATH/examples
  QMAKE_EXTRA_TARGETS += copyexamples
  POST_TARGETDEPS += copyexamples
}
