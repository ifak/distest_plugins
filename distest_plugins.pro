include($$PWD/../distest_plugins.config)

isEmpty(DISTEST_SUTEDITOR_PLUGIN){
  DISTEST_SUTEDITOR_PLUGIN = yes
}
isEmpty(DISTEST_TESTSYSTEMEDITOR_PLUGIN){
  DISTEST_TESTSYSTEMEDITOR_PLUGIN = yes
}
isEmpty(DISTEST_TESTCASEEDITOR_PLUGIN){
  DISTEST_TESTCASEEDITOR_PLUGIN = yes
}
isEmpty(DISTEST_DISTESTPROJECT_PLUGIN){
  DISTEST_DISTESTPROJECT_PLUGIN = yes
}
isEmpty(DISTEST_DIAGNOSISEDITOR_PLUGIN){
  DISTEST_DIAGNOSISEDITOR_PLUGIN = yes
}

include(distest_config.pri)
include($${APPCREATOR_PATH}/appcreator.pri)

TEMPLATE  = subdirs

contains(DISTEST_SUTEDITOR_PLUGIN, yes){
  SUBDIRS += suteditor
}

contains(DISTEST_TESTSYSTEMEDITOR_PLUGIN, yes){
  SUBDIRS += testsystemeditor
}

contains(DISTEST_TESTCASEEDITOR_PLUGIN, yes){
  SUBDIRS += testcaseeditor
}

contains(DISTEST_DISTESTPROJECT_PLUGIN, yes){
  SUBDIRS += distestproject
  distestproject.depends += testcaseeditor
}

contains(DISTEST_DIAGNOSISEDITOR_PLUGIN, yes){
  SUBDIRS += diagnosiseditor
}
