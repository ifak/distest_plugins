#include "distestrendermanager.hpp"
#include "distestrendersettings.hpp"

#include <QHash>
#include <stdexcept>
#include <QDebug>

namespace distestproject {

class DisTestRenderManager::Private
{
  friend class DisTestRenderManager;

public:
  Private() : _globalRenderSettings(0)
  {}

  ~Private()
  {
    if (_globalRenderSettings)
    {
      delete _globalRenderSettings;
    }

    foreach (DisTestRenderSettings* renderSettings, _customRenderSettingsMap)
    {
      delete renderSettings;
    }
  }

private:
  DisTestRenderSettings* _globalRenderSettings;
  QHash<QString, DisTestRenderSettings*> _customRenderSettingsMap;
  QHash<QString, bool> _statusMap;
  QHash<QString, QString> _sutDocumentsMap;
  QHash<QString, QString> _testSystemDocumentsMap;
  QHash<QString, QString> _testCaseDocumentsMap;
};

DisTestRenderManager *DisTestRenderManager::m_instance = 0;

DisTestRenderManager::DisTestRenderManager() : _d(new Private())
{}

DisTestRenderManager::~DisTestRenderManager()
{
//  if (m_instance)
//  {
//    delete m_instance;
//    m_instance = 0;
//  }

  delete _d;
}

DisTestRenderManager *DisTestRenderManager::instance()
{
  if (!m_instance)
  {
    static DisTestRenderManager disTestRenderManager;
    m_instance = &disTestRenderManager;//new DisTestRenderManager();
    m_instance->createGlobalRenderSettings();
  }

  return m_instance;
}

void DisTestRenderManager::createGlobalRenderSettings()
{
  if (!this->_d->_globalRenderSettings)
  {
    this->_d->_globalRenderSettings = new DisTestRenderSettings();
    connect(this->_d->_globalRenderSettings, SIGNAL(sutSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(sutSettingsHandler(DisTestRenderSettings*)));
    connect(this->_d->_globalRenderSettings, SIGNAL(testSystemSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(testSystemSettingsHandler(DisTestRenderSettings*)));
    connect(this->_d->_globalRenderSettings, SIGNAL(testCaseSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(testCaseSettingsHandler(DisTestRenderSettings*)));
  }
}

void DisTestRenderManager::removeGlobalRenderSettings()
{
  if (this->_d->_globalRenderSettings)
  {
    disconnect(this->_d->_globalRenderSettings, SIGNAL(sutSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(sutSettingsHandler(DisTestRenderSettings*)));
    disconnect(this->_d->_globalRenderSettings, SIGNAL(testSystemSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(testSystemSettingsHandler(DisTestRenderSettings*)));
    disconnect(this->_d->_globalRenderSettings, SIGNAL(testCaseSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(testCaseSettingsHandler(DisTestRenderSettings*)));
    delete this->_d->_globalRenderSettings;
    this->_d->_globalRenderSettings = 0;
  }
}

DisTestRenderSettings* DisTestRenderManager::globalRenderSettings() const
{
  if (this->_d->_globalRenderSettings)
  {
    return this->_d->_globalRenderSettings;
  }
  else
  {
    throw std::runtime_error("Global render settings are not found.");
  }
}


void DisTestRenderManager::createCustomRenderSettings(const QString &projectID)
{
  if (!this->_d->_customRenderSettingsMap.contains(projectID))
  {
    DisTestRenderSettings *renderSettings = new DisTestRenderSettings();
    this->_d->_customRenderSettingsMap.insert(projectID, renderSettings);
    connect(renderSettings, SIGNAL(sutSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(sutSettingsHandler(DisTestRenderSettings*)));
    connect(renderSettings, SIGNAL(testSystemSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(testSystemSettingsHandler(DisTestRenderSettings*)));
    connect(renderSettings, SIGNAL(testCaseSettingsChanged(DisTestRenderSettings*)),
            this, SLOT(testCaseSettingsHandler(DisTestRenderSettings*)));
  }
}

void DisTestRenderManager::removeCustomRenderSettings(const QString &projectID)
{
  if (this->_d->_customRenderSettingsMap.contains(projectID))
  {
    DisTestRenderSettings *renderSettings = customRenderSettings(projectID);
    disconnect(renderSettings, SIGNAL(sutSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(sutSettingsHandler(DisTestRenderSettings*)));
    disconnect(renderSettings, SIGNAL(testSystemSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(testSystemSettingsHandler(DisTestRenderSettings*)));
    disconnect(renderSettings, SIGNAL(testCaseSettingsChanged(DisTestRenderSettings*)),
               this, SLOT(testCaseSettingsHandler(DisTestRenderSettings*)));
    delete renderSettings;
    this->_d->_customRenderSettingsMap.remove(projectID);
  }
}

DisTestRenderSettings* DisTestRenderManager::customRenderSettings(const QString& projectID) const
{
  if (this->_d->_customRenderSettingsMap.contains(projectID))
  {
    return const_cast<DisTestRenderSettings*>(this->_d->_customRenderSettingsMap.value(projectID));
  }
  else
  {
    throw std::runtime_error("Custom render settings for the project are not found.");
  }
}


void DisTestRenderManager::registerRenderSettings(const QString &projectID, const bool useGlobalSettings)
{
  if (!this->_d->_statusMap.contains(projectID))
  {
    this->_d->_statusMap.insert(projectID, useGlobalSettings);
  }
  else
  {
    const bool oldUseGlobalSettings = this->_d->_statusMap.value(projectID);
    if (oldUseGlobalSettings != useGlobalSettings)
    {
      this->_d->_statusMap[projectID] = useGlobalSettings;
      if (useGlobalSettings)
      {
        emit requestForApplyingNewGlobalSutRenderSettings(projectID);
        emit requestForApplyingNewGlobalTestSystemRenderSettings(projectID);
        emit requestForApplyingNewGlobalTestCaseRenderSettings(projectID);
      }
      else
      {
        emit requestForApplyingNewCustomSutRenderSettings(projectID);
        emit requestForApplyingNewCustomTestSystemRenderSettings(projectID);
        emit requestForApplyingNewCustomTestCaseRenderSettings(projectID);
      }
    }
  }
}

void DisTestRenderManager::deregisterRenderSettings(const QString &projectID)
{
  if (this->_d->_statusMap.contains(projectID))
  {
    this->_d->_statusMap.remove(projectID);
  }
}

bool DisTestRenderManager::isGlobalRendenSettingsUsed(const QString& projectID) const
{
  if (this->_d->_statusMap.contains(projectID))
  {
    return this->_d->_statusMap.value(projectID);
  }
  else
  {
    throw std::runtime_error("The project ID is not registered.");
  }
}

void DisTestRenderManager::assignSutDocument(const QString &projectID, const QString &documentPath)
{
  if (!this->_d->_sutDocumentsMap.contains(documentPath))
  {
    this->_d->_sutDocumentsMap.insert(documentPath, projectID);
  }
  else
  {
    this->_d->_sutDocumentsMap[documentPath] = projectID;
  }
}

void DisTestRenderManager::assignTestSystemDocument(const QString &projectID, const QString &documentPath)
{
  if (!this->_d->_testSystemDocumentsMap.contains(documentPath))
  {
    this->_d->_testSystemDocumentsMap.insert(documentPath, projectID);
  }
  else
  {
    this->_d->_testSystemDocumentsMap[documentPath] = projectID;
  }
}

void DisTestRenderManager::assignTestCaseDocument(const QString &projectID, const QString &documentPath)
{
  if (!this->_d->_testCaseDocumentsMap.contains(documentPath))
  {
    this->_d->_testCaseDocumentsMap.insert(documentPath, projectID);
  }
  else
  {
    this->_d->_testCaseDocumentsMap[documentPath] = projectID;
  }
}

void DisTestRenderManager::removeProjectDocuments(const QString &projectID)
{
  foreach (const QString &sutDocumentPath, this->_d->_sutDocumentsMap)
  {
    if (!projectID.compare(this->_d->_sutDocumentsMap.value(sutDocumentPath)))
    {
      this->_d->_sutDocumentsMap.remove(sutDocumentPath);
    }
  }

  foreach (const QString testSystemDocumentPath, this->_d->_testSystemDocumentsMap)
  {
    if (!projectID.compare(this->_d->_testSystemDocumentsMap.value(testSystemDocumentPath)))
    {
      this->_d->_testSystemDocumentsMap.remove(testSystemDocumentPath);
    }
  }

  foreach (const QString &testCaseDocumentPath, this->_d->_testCaseDocumentsMap)
  {
    if (!projectID.compare(this->_d->_testCaseDocumentsMap.value(testCaseDocumentPath)))
    {
      this->_d->_testCaseDocumentsMap.remove(testCaseDocumentPath);
    }
  }
}

QString DisTestRenderManager::projectIDforSutDocument(const QString& documentPath) const
{
  if (this->_d->_sutDocumentsMap.contains(documentPath))
  {
    return this->_d->_sutDocumentsMap.value(documentPath);
  }
  else
  {
    throw std::runtime_error("No project ID for this SUT document is found.");
  }
}

QString DisTestRenderManager::projectIDforTestSystemDocument(const QString& documentPath) const
{
  if (this->_d->_testSystemDocumentsMap.contains(documentPath))
  {
    return this->_d->_testSystemDocumentsMap.value(documentPath);
  }
  else
  {
    throw std::runtime_error("No project ID for this testsystem document is found.");
  }
}

QString DisTestRenderManager::projectIDforTestCaseDocument(const QString& documentPath) const
{
  if (this->_d->_testCaseDocumentsMap.contains(documentPath))
  {
    return this->_d->_testCaseDocumentsMap.value(documentPath);
  }
  else
  {
    throw std::runtime_error("No project ID for this testcase document is found.");
  }
}

bool DisTestRenderManager::hasRenderSettings(const QString &projectID) const
{
  return this->_d->_statusMap.contains(projectID);
}

const DisTestRenderSettings* DisTestRenderManager::renderSettings(const QString &projectID) const
{
  if (!this->_d->_statusMap.contains(projectID))
  {
    throw std::runtime_error("No render settings information for the project is found.");
  }

  if (this->_d->_statusMap.value(projectID))
  {
    return globalRenderSettings();
  }

  if (!this->_d->_customRenderSettingsMap.contains(projectID))
  {
    throw std::runtime_error("app error");
  }

  return customRenderSettings(projectID);
}

const DisTestRenderSettings* DisTestRenderManager::renderSettingsFromSutDocument(const QString &documentPath) const
{
  if (!this->_d->_sutDocumentsMap.contains(documentPath))
  {
    throw std::runtime_error("The corrsponding render settings cannot be found.");
  }

  QString projectID(this->_d->_sutDocumentsMap.value(documentPath));

  return renderSettings(projectID);
}

const DisTestRenderSettings* DisTestRenderManager::renderSettingsFromTestSystemDocument(const QString &documentPath) const
{
  if (!this->_d->_testSystemDocumentsMap.contains(documentPath))
  {
    throw std::runtime_error("The corrsponding render settings cannot be found.");
  }

  QString projectID(this->_d->_testSystemDocumentsMap.value(documentPath));

  return renderSettings(projectID);
}

const DisTestRenderSettings* DisTestRenderManager::renderSettingsFromTestCaseDocument(const QString &documentPath) const
{
  if (!this->_d->_testCaseDocumentsMap.contains(documentPath))
  {
    throw std::runtime_error("The corrsponding render settings cannot be found.");
  }

  QString projectID(this->_d->_testCaseDocumentsMap.value(documentPath));

  return renderSettings(projectID);
}

void DisTestRenderManager::sutSettingsHandler(DisTestRenderSettings *renderSettings)
{
  if (renderSettings == this->_d->_globalRenderSettings)
  {
    emit requestForApplyingNewGlobalSutRenderSettings();
  }
  else
  {
    bool isCustomRenderSettingFound = false;
    foreach (const QString projectID, this->_d->_customRenderSettingsMap.keys())
    {
      const DisTestRenderSettings *customRenderSettings = this->_d->_customRenderSettingsMap.value(projectID);
      if (customRenderSettings == renderSettings)
      {
        isCustomRenderSettingFound = true;
        emit requestForApplyingNewCustomSutRenderSettings(projectID);
        break;
      }
    }

    if (!isCustomRenderSettingFound)
    {
      qDebug() << "The SUT render settings will not be applied, because the corresponding project ID is not found.";
    }
  }
}

void DisTestRenderManager::testSystemSettingsHandler(DisTestRenderSettings *renderSettings)
{
  if (renderSettings == this->_d->_globalRenderSettings)
  {
    emit requestForApplyingNewGlobalTestSystemRenderSettings();
  }
  else
  {
    bool isCustomRenderSettingFound = false;
    foreach (const QString projectID, this->_d->_customRenderSettingsMap.keys())
    {
      const DisTestRenderSettings *customRenderSettings = this->_d->_customRenderSettingsMap.value(projectID);
      if (customRenderSettings == renderSettings)
      {
        isCustomRenderSettingFound = true;
        emit requestForApplyingNewCustomTestSystemRenderSettings(projectID);
        break;
      }
    }

    if (!isCustomRenderSettingFound)
    {
      qDebug() << "The testsystem render settings will not be applied, because the corresponding project ID is not found.";
    }
  }
}

void DisTestRenderManager::testCaseSettingsHandler(DisTestRenderSettings *renderSettings)
{
  if (renderSettings == this->_d->_globalRenderSettings)
  {
    emit requestForApplyingNewGlobalTestCaseRenderSettings();
  }
  else
  {
    bool isCustomRenderSettingFound = false;
    foreach (const QString projectID, this->_d->_customRenderSettingsMap.keys())
    {
      const DisTestRenderSettings *customRenderSettings = this->_d->_customRenderSettingsMap.value(projectID);
      if (customRenderSettings == renderSettings)
      {
        isCustomRenderSettingFound = true;
        emit requestForApplyingNewCustomTestCaseRenderSettings(projectID);
        break;
      }
    }

    if (!isCustomRenderSettingFound)
    {
      qDebug() << "The testcase render settings will not be applied, because the corresponding project ID is not found.";
    }
  }
}

}

