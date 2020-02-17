#include "helpers.hpp"

#include <projectexplorer/projectexplorer.h>
#include <projectexplorer/session.h>
#include <projectexplorer/projectnodes.h>

#include "distestproject.hpp"

#include <QFontDatabase>

#include <mobata/memory_leak_start.hpp>

namespace distestproject
{

ProjectExplorer::Project* Helpers::projectForFile(const QString& fileName)
{
  using namespace ProjectExplorer;

  ProjectExplorerPlugin* pePlugin= ProjectExplorerPlugin::instance();
  Q_ASSERT(pePlugin);

  SessionManager* sessionManager=pePlugin->session();
  if(!sessionManager)
    return 0;

  return sessionManager->projectForFile(fileName);
}

ProjectExplorer::Node* Helpers::nodeForFile(const QString& fileName,
                                            ProjectExplorer::Project* project)
{
  using namespace ProjectExplorer;

  ProjectExplorerPlugin* pePlugin= ProjectExplorerPlugin::instance();
  Q_ASSERT(pePlugin);

  SessionManager* sessionManager=pePlugin->session();
  if(!sessionManager)
    return 0;

  return sessionManager->nodeForFile(fileName, project);
}

void Helpers::changeLabelColor(ClickableLabel *label, const QColor &color)
{
  QPalette colorChooserPalette = label->palette();
  colorChooserPalette.setColor(QPalette::Window, color);
  label->setAutoFillBackground(true);
  label->setPalette(colorChooserPalette);
  label->update();
}

unsigned int Helpers::availableFontSettingsState(const QFont &font)
{
  const bool isBoldChecked = font.bold();
  const bool isItalicChecked = font.italic();

  bool isNormalStyleSupported = false;
  bool isBoldStyleSupported = false;
  bool isItalicStyleSupported = false;
  bool isBoldItalicStyleSupported = false;

  QFontDatabase fdb;
  QStringList styleList = fdb.styles(font.family());

  foreach (const QString& style, styleList)
  {
    QStringList styleItemList = style.split(QString::fromLatin1(" "));
    QString& stupidStyle = styleItemList.last();
    if (!stupidStyle.compare(QString::fromLatin1("Bold")))
    {
      if (!isBoldStyleSupported)
      {
        isBoldStyleSupported = true;
      }
    }
    else if (!stupidStyle.compare(QString::fromLatin1("Italic")))
    {
      const int itemCount = styleItemList.count();
      if (1 == itemCount)
      {
        if (!isItalicStyleSupported)
        {
          isItalicStyleSupported = true;
        }
      }
      else
      {
        if (!styleItemList.at(itemCount - 2).compare(QString::fromLatin1("Bold")))
        {
          if (!isBoldItalicStyleSupported)
          {
            isBoldItalicStyleSupported = true;
          }
        }
        else
        {
          if (!isItalicStyleSupported)
          {
            isItalicStyleSupported = true;
          }
        }
      }
    }
    else
    {
      isNormalStyleSupported = true;
    }
  }

  //* settingState : status variable (bit-sequence : 76543210)
  // bit0 : Bold settable, bit1 : Italic settable, bit2-3 : not used
  // bit4 : Bold checked,  bit5 : Italic checked,  bit6-7 : not used
  unsigned int settingState = 0x00;
  bool isCheckedStateValid = true;
  if (!isBoldChecked && !isItalicChecked)
  {
    if (!isNormalStyleSupported)
    {
      isCheckedStateValid = false;
    }
  }
  else if (isBoldChecked && !isItalicChecked)
  {
    if (!isBoldStyleSupported)
    {
      isCheckedStateValid = false;
    }
    else
    {
      settingState = 0x10;
    }
  }
  else if (!isBoldChecked && isItalicChecked)
  {
    if (!isItalicStyleSupported)
    {
      isCheckedStateValid = false;
    }
    else
    {
      settingState = 0x20;
    }
  }
  else
  {
    if (!isBoldItalicStyleSupported)
    {
      isCheckedStateValid = false;
    }
    else
    {
      settingState = 0x30;
    }
  }

  if (!isCheckedStateValid)
  {
    if (isBoldChecked && isItalicChecked)
    {
      if (isItalicStyleSupported)
      {
        settingState = 0x20;
      }
      else if (isBoldStyleSupported)
      {
        settingState = 0x10;
      }
      else
      {
        settingState = 0x00;
      }
    }
    else
    {
      if (isNormalStyleSupported)
      {
        settingState = 0x00;
      }
      else if (isBoldStyleSupported)
      {
        settingState = 0x10;
      }
      else if (isItalicStyleSupported)
      {
        settingState = 0x20;
      }
      else
      {
        settingState = 0x30;
      }
    }
  }

  if (0x00 == settingState)
  {
    if (isBoldStyleSupported)
    {
      settingState+=0x01;
    }

    if (isItalicStyleSupported)
    {
      settingState+=0x02;
    }
  }
  else if (0x10 == settingState)
  {
    if (isNormalStyleSupported)
    {
      settingState+=0x01;
    }

    if (isBoldItalicStyleSupported)
    {
      settingState+=0x02;
    }
  }
  else if (0x20 == settingState)
  {
    if (isBoldItalicStyleSupported)
    {
      settingState+=0x01;
    }

    if (isNormalStyleSupported)
    {
      settingState+=0x02;
    }
  }
  else
  {
    if (isItalicStyleSupported)
    {
      settingState+=0x01;
    }

    if (isBoldStyleSupported)
    {
      settingState+=0x02;
    }
  }

  return settingState;
}

}// end namespace distestproject
