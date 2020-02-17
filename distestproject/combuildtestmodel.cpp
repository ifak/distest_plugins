#include "combuildtestmodel.hpp"

#include <mobata/utils/functors.hpp>
#include <mobata/model/ts/ts.hpp>

#include <dslparser/importreader/combuildimportreadermodel.hpp>
#include <dslparser/testsystem/combuildtestsystemmodel.hpp>
#include <dslparser/testcase/combuildtestcasemodel.hpp>

#include "distestproject.hpp"
#include "distestprojectconstants.hpp"
#include "distestprojectmodel.hpp"
#include "distestsuite.hpp"
#include "helpers.hpp"

#include <coreplugin/editormanager/editormanager.h>

#include <QQmlEngine>
#include <QQmlComponent>

#include <QDebug>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

using ProjectExplorer::BaseError;

class ComBuildTestModel::Private
{
  friend class ComBuildTestModel;

  DisTestProject* _disTestProject;

  Private(DisTestProject* disTestProject)
    : _disTestProject(disTestProject)
  {}
};

ComBuildTestModel::ComBuildTestModel(DisTestProject* disTestProject, QObject* parent)
  : QObject(parent), _d(new Private(disTestProject))
{}

ComBuildTestModel::~ComBuildTestModel()
{
  delete this->_d;
}

bool ComBuildTestModel::execute(QString* errorMessage)
{
  Q_ASSERT(this->_d->_disTestProject);

  DisTestProjectModel* disTestProjectModel=const_cast<DisTestProjectModel*>(this->_d->_disTestProject->disTestProjectModel());
  Q_ASSERT(disTestProjectModel);

  disTestProjectModel->reset();

  bool result = true;

  DisTestSuite* newTestSuite = new DisTestSuite;
  //first building of test systems
  for(const QString& testSystemFileName : this->_d->_disTestProject->testSystemFiles())
  {
    QFileInfo testSystemFileInfo(testSystemFileName);
    if(!testSystemFileInfo.exists())
    {
      BaseError error;
      error.setDescription(tr("there is no test system file '%1' available!").arg(testSystemFileName));
      error.setUrl(QUrl(testSystemFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }

    QFile testSystemFile(testSystemFileName);
    if(!testSystemFile.open(QFile::ReadOnly | QFile::Text))
    {
      BaseError error;
      error.setDescription(tr("test system file '%1' could not be opened!").arg(testSystemFileName));
      error.setUrl(QUrl(testSystemFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }

    QString testSystemText(QLatin1String(testSystemFile.readAll()));
    testSystemFile.close();

#if 0
    //detect imported sut file
    dslparser::importreader::ComBuildImportReaderModel importReaderCommand(testSystemText,
                                                                           testSystemFileInfo.absolutePath()+QStringLiteral("/"));
    if(!importReaderCommand.execute(errorMessage))
    {
      for(const dslparser::DslError& dslError : importReaderCommand.errors())
        this->_d->_disTestProject->addDslError(dslError, testSystemFileName);
      result=false;
      continue;
    }

    QString importedSutFilePath=importReaderCommand.importedFiles().value(QStringLiteral("sut"));
    if(importedSutFilePath.isEmpty())
    {
      BaseError error;
      error.setDescription(tr("there is no imported sut file within test system file '%1' available!").arg(testSystemFileName));
      error.setUrl(QUrl(testSystemFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }
#endif

    //DisTestSuite* newTestSuite = new DisTestSuite;
    newTestSuite = new DisTestSuite;
    newTestSuite->setTestSystemFilePath(testSystemFileName);
    Q_ASSERT(newTestSuite->sutItem());
    Q_ASSERT(newTestSuite->testSystemItem());

    dslparser::testsystem::ComBuildTestSystemModel buildTestSystemCommand(testSystemText,
                                                                          newTestSuite->testSystemItem(),
                                                                          testSystemFileInfo.absolutePath()+QStringLiteral("/"));
    if(!buildTestSystemCommand.execute(errorMessage))
    {
      for(const dslparser::DslError& dslError : buildTestSystemCommand.errors())
        this->_d->_disTestProject->addDslError(dslError, testSystemFileName);
      delete newTestSuite;
      result =false;
      continue;
    }
    else
    {
//      newTestSuite->setSutFilePath(importedSutFilePath);
      disTestProjectModel->addDisTestSuite(newTestSuite);
    }

  }

  //now we build the test cases...
  int counter=1;
  for(const QString& testCaseFileName : this->_d->_disTestProject->testCaseFiles())
  {
    QFileInfo testCaseFileInfo(testCaseFileName);
    if(!testCaseFileInfo.exists())
    {
      BaseError error;
      error.setDescription(tr("there is no test case file '%1' available!").arg(testCaseFileName));
      error.setUrl(QUrl(testCaseFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }

    QFile testCaseFile(testCaseFileName);
    if(!testCaseFile.open(QFile::ReadOnly | QFile::Text))
    {
      BaseError error;
      error.setDescription(tr("test case file '%1' could not be opened!").arg(testCaseFileName));
      error.setUrl(QUrl(testCaseFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }

    QString testCaseText(QLatin1String(testCaseFile.readAll()));
    testCaseFile.close();

#if 0
    //detect imported test system file
    dslparser::importreader::ComBuildImportReaderModel importReaderCommand(testCaseText,
                                                                           testCaseFileInfo.absolutePath()+QStringLiteral("/"));
    if(!importReaderCommand.execute(errorMessage))
    {
      for(const dslparser::DslError& dslError : importReaderCommand.errors())
        this->_d->_disTestProject->addDslError(dslError, testCaseFileName);
      result=false;
      continue;
    }

    QString importedTestSystemFilePath=importReaderCommand.importedFiles().value(QStringLiteral("testsystem"));
    if(importedTestSystemFilePath.isEmpty())
    {
      BaseError error;
      error.setDescription(tr("there is no imported test system file within test case file '%1' available!").arg(testCaseFileName));
      error.setUrl(QUrl(testCaseFileName));
      this->_d->_disTestProject->addError(error);

      utils::AddPtrString(errorMessage)<<error.description();
      result = false;
      continue;
    }
#endif

    //TODO: find test suite for test case
    DisTestSuite* testSuite = disTestProjectModel->disTestSuites().first(); //letzte testsuite verwenden todo-> aktuelle annahme nur 1 Testsuite
    //DisTestSuite* testSuite = disTestProjectModel->disTestSuite(importedTestSystemFilePath);
    if(testSuite)
    {
      model::ts::TestCaseItem* newTestCase = new model::ts::TestCaseItem(QString(QStringLiteral("test_case_%1")).arg(counter));
      QString errorString;
      if(!testSuite->addTestCase(testCaseFileName, newTestCase, &errorString))
      {
        BaseError error;
        error.setDescription(errorString);
        error.setUrl(QUrl(testCaseFileName));
        this->_d->_disTestProject->addError(error);

        utils::AddPtrString(errorMessage)<<errorString;
        delete newTestCase;
        newTestCase=nullptr;
        result = false;
        continue;
      }

//      dslparser::testcase::ComBuildTestCaseModel buildTestCase(testCaseText, newTestCase,
//                                                               testCaseFileInfo.absolutePath()+QStringLiteral("/"));
//      if(!buildTestCase.execute(errorMessage))
//      {
//        for(const dslparser::DslError& dslError : buildTestCase.errors())
//          this->_d->_disTestProject->addDslError(dslError, testCaseFileName);
//        testSuite->removeTestCase(testCaseFileName);
//        result =false;
//        continue;
//      }
    }
    else
    {
      testSuite = new DisTestSuite;
      model::ts::TestCaseItem* newTestCase = new model::ts::TestCaseItem(QString(QStringLiteral("test_case_%1")).arg(counter));
      QString errorString;
      if(!testSuite->addTestCase(testCaseFileName, newTestCase, &errorString))
      {
        BaseError error;
        error.setDescription(errorString);
        error.setUrl(QUrl(testCaseFileName));
        this->_d->_disTestProject->addError(error);

        utils::AddPtrString(errorMessage)<<errorString;
        delete newTestCase;
        newTestCase=nullptr;
        result = false;
        continue;
      }

//      dslparser::testcase::ComBuildTestCaseModel buildTestCase(testCaseText, newTestCase,
//                                                               testCaseFileInfo.absolutePath()+QStringLiteral("/"));
//      if(!buildTestCase.execute(errorMessage))
//      {
//        for(const dslparser::DslError& dslError : buildTestCase.errors())
//          this->_d->_disTestProject->addDslError(dslError, testCaseFileName);
//        delete testSuite;
//        testSuite=nullptr;
//        result =false;
//        continue;
//      }

//      testSuite->setSutFilePath(buildTestCase.importedSutFile());
//      testSuite->setTestSystemFilePath(buildTestCase.importedTestSystemFile());
//      disTestProjectModel->addDisTestSuite(testSuite);
    }

    disTestProjectModel->updateDisTestSuite(testSuite);

    ++counter;
  }

  return result;
}

} // namespace distestproject
