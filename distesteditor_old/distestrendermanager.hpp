/*
 * This file is part of mobata.
 *
 * mobata is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * mobata is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public License
 * along with mobata.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef DISTESTEDITOR_DISTESTRENDERMANAGER_HPP
#define DISTESTEDITOR_DISTESTRENDERMANAGER_HPP

#include "distesteditor_global.hpp"

#include <QObject>

namespace distesteditor {

class DisTestRenderSettings;

class DISTESTEDITOR_EXPORT DisTestRenderManager : public QObject
{
    Q_OBJECT

public:
    static DisTestRenderManager* createDisTestRenderManager();
    static void removeDisTestRenderManager();
    static DisTestRenderManager* instance();

    void createGlobalRenderSettings();
    void removeGlobalRenderSettings();
    DisTestRenderSettings* globalRenderSettings() const;

    void createCustomRenderSettings(const QString& projectID);
    void removeCustomRenderSettings(const QString& projectID);
    DisTestRenderSettings* customRenderSettings(const QString& projectID) const;

    void registerRenderSettings(const QString& projectID, const bool useGlobalSettings);
    void deregisterRenderSettings(const QString& projectID);
    bool isGlobalRendenSettingsUsed(const QString& projectID) const;

    void assignSutDocument(const QString& projectID, const QString& documentPath);
    void assignTestSystemDocument(const QString& projectID, const QString& documentPath);
    void assignTestCaseDocument(const QString& projectID, const QString& documentPath);
    void removeProjectDocuments(const QString& projectID);
    QString projectIDforSutDocument(const QString& documentPath) const;
    QString projectIDforTestSystemDocument(const QString& documentPath) const;
    QString projectIDforTestCaseDocument(const QString& documentPath) const;

    bool hasRenderSettings(const QString& projectID) const;
    const DisTestRenderSettings* renderSettings(const QString& projectID) const;
    const DisTestRenderSettings* renderSettingsFromSutDocument(const QString& documentPath) const;
    const DisTestRenderSettings* renderSettingsFromTestSystemDocument(const QString& documentPath) const;
    const DisTestRenderSettings* renderSettingsFromTestCaseDocument(const QString& documentPath) const;

signals:
    void requestForApplyingNewGlobalSutRenderSettings(QString projectID = QString());
    void requestForApplyingNewGlobalTestSystemRenderSettings(QString projectID = QString());
    void requestForApplyingNewGlobalTestCaseRenderSettings(QString projectID = QString());
    void requestForApplyingNewCustomSutRenderSettings(QString projectID = QString());
    void requestForApplyingNewCustomTestSystemRenderSettings(QString projectID = QString());
    void requestForApplyingNewCustomTestCaseRenderSettings(QString projectID = QString());

public slots:
    void sutSettingsHandler(DisTestRenderSettings *renderSettings);
    void testSystemSettingsHandler(DisTestRenderSettings *renderSettings);
    void testCaseSettingsHandler(DisTestRenderSettings *renderSettings);

private:
    Q_DISABLE_COPY(DisTestRenderManager)
    class Private;
    Private* _d;

    DisTestRenderManager();
    ~DisTestRenderManager();

    static DisTestRenderManager *m_instance;
};

}

#endif // DISTESTRENDERMANAGER_HPP
