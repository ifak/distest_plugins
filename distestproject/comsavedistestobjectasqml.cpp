#include "comsavedistestobjectasqml.hpp"

#include <QStringList>

#include <mobata/memory_leak_start.hpp>

namespace distestproject {

ComSaveDisTestObjectAsQml::ComSaveDisTestObjectAsQml(QObject* object,
                                                     const QString& qmlTypeName,
                                                     const QString& filePath)
  : ComSaveObjectAsQml(object,
                       QStringList()<<QLatin1String("import DisTestDsl 1.0"),
                       qmlTypeName,
                       filePath)
{}


}/// end namespace distestproject
