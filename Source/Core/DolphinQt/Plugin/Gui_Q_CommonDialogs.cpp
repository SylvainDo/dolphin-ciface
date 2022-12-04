#include "Export.h"
#include "PluginUtil.h"
using namespace PluginUtil;

#include "Interface/dol/Alloc.h"
extern dol_malloc_t interop_malloc;
extern dol_calloc_t interop_calloc;
#include "Interface/dol/Gui_Q_CommonDialogs.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

namespace CommonDialogs
{

constexpr QWidget* toQWidget(void* ptr)
{
  return static_cast<QWidget*>(ptr);
}

QColor toQColor(dol_Gui_Q_Color color)
{
  return QColor::fromRgb(color.r, color.g, color.b, color.a);
}

dol_Gui_Q_Color fromQColor(const QColor& color)
{
  return {.r = color.red(), .g = color.green(), .b = color.blue(), .a = color.alpha()};
}

QStringList toQStringList(const char** values, int numValues)
{
  QStringList list;
  for (int i{}; i < numValues; ++i)
    list << toQString(values[i]);
  return list;
}

char** fromQStringList(const QStringList& list, int* size)
{
  auto a = static_cast<char**>(interop_malloc(sizeof(char*) * list.size()));
  for (qsizetype i{}; i < list.size(); ++i)
    a[i] = dupQString(list[i]);
  *size = static_cast<int>(list.size());
  return a;
}

void about(void* parent, const char* title, const char* text)
{
  QMessageBox::about(toQWidget(parent), toQString(title), toQString(text));
}

int critical(void* parent, const char* title, const char* text, int buttons, int defaultButton)
{
  return static_cast<int>(
      QMessageBox::critical(toQWidget(parent), toQString(title), toQString(text),
                            static_cast<QMessageBox::StandardButtons>(buttons),
                            static_cast<QMessageBox::StandardButton>(defaultButton)));
}

int information(void* parent, const char* title, const char* text, int buttons, int defaultButton)
{
  return static_cast<int>(
      QMessageBox::information(toQWidget(parent), toQString(title), toQString(text),
                               static_cast<QMessageBox::StandardButtons>(buttons),
                               static_cast<QMessageBox::StandardButton>(defaultButton)));
}

int question(void* parent, const char* title, const char* text, int buttons, int defaultButton)
{
  return static_cast<int>(
      QMessageBox::question(toQWidget(parent), toQString(title), toQString(text),
                            static_cast<QMessageBox::StandardButtons>(buttons),
                            static_cast<QMessageBox::StandardButton>(defaultButton)));
}

int warning(void* parent, const char* title, const char* text, int buttons, int defaultButton)
{
  return static_cast<int>(
      QMessageBox::warning(toQWidget(parent), toQString(title), toQString(text),
                           static_cast<QMessageBox::StandardButtons>(buttons),
                           static_cast<QMessageBox::StandardButton>(defaultButton)));
}

dol_Gui_Q_Color getColor(dol_Gui_Q_Color initial, void* parent, const char* title, int options)
{
  return fromQColor(QColorDialog::getColor(toQColor(initial), toQWidget(parent), toQString(title),
                                           static_cast<QColorDialog::ColorDialogOptions>(options)));
}

double getDouble(void* parent, const char* title, const char* label, double value, double minValue,
                 double maxValue, int decimals, bool* ok, double step)
{
  return QInputDialog::getDouble(toQWidget(parent), toQString(title), toQString(label), value,
                                 minValue, maxValue, decimals, ok, {}, step);
}

int getInt(void* parent, const char* title, const char* label, int value, int minValue,
           int maxValue, int step, bool* ok)
{
  return QInputDialog::getInt(toQWidget(parent), toQString(title), toQString(label), value,
                              minValue, maxValue, step, ok);
}

char* getItem(void* parent, const char* title, const char* label, const char** items, int numItems,
              int current, bool editable, bool* ok)
{
  return dupQString(QInputDialog::getItem(toQWidget(parent), toQString(title), toQString(label),
                                          toQStringList(items, numItems), current, editable, ok));
}

char* getMultiLineText(void* parent, const char* title, const char* label, const char* text,
                       bool* ok)
{
  return dupQString(QInputDialog::getMultiLineText(toQWidget(parent), toQString(title),
                                                   toQString(label), toQString(text), ok));
}

char* getText(void* parent, const char* title, const char* label, int echo, const char* text,
              bool* ok)
{
  return dupQString(QInputDialog::getText(toQWidget(parent), toQString(title), toQString(label),
                                          static_cast<QLineEdit::EchoMode>(echo), toQString(text)));
}

char* getExistingDirectory(void* parent, const char* caption, const char* dir, int options)
{
  return dupQString(QFileDialog::getExistingDirectory(toQWidget(parent), toQString(caption),
                                                      toQString(dir),
                                                      static_cast<QFileDialog::Options>(options)));
}

char* getOpenFileName(void* parent, const char* caption, const char* dir, const char* filter,
                      char** selectedFilter, int options)
{
  QString _selectedFilter;
  const auto ret = dupQString(QFileDialog::getOpenFileName(
      toQWidget(parent), toQString(caption), toQString(dir), toQString(filter),
      selectedFilter ? &_selectedFilter : nullptr, static_cast<QFileDialog::Options>(options)));
  if (selectedFilter)
    *selectedFilter = dupQString(_selectedFilter);
  return ret;
}

char** getOpenFileNames(void* parent, const char* caption, const char* dir, const char* filter,
                        char** selectedFilter, int options, int* numPaths)
{
  QString _selectedFilter;
  const auto ret = fromQStringList(
      QFileDialog::getOpenFileNames(toQWidget(parent), toQString(caption), toQString(dir),
                                    toQString(filter), selectedFilter ? &_selectedFilter : nullptr,
                                    static_cast<QFileDialog::Options>(options)),
      numPaths);
  if (selectedFilter)
    *selectedFilter = dupQString(_selectedFilter);
  return ret;
}

char* getSaveFileName(void* parent, const char* caption, const char* dir, const char* filter,
                      char** selectedFilter, int options)
{
  QString _selectedFilter;
  const auto ret = dupQString(QFileDialog::getSaveFileName(
      toQWidget(parent), toQString(caption), toQString(dir), toQString(filter),
      selectedFilter ? &_selectedFilter : nullptr, static_cast<QFileDialog::Options>(options)));
  if (selectedFilter)
    *selectedFilter = dupQString(_selectedFilter);
  return ret;
}

}  // namespace CommonDialogs

EXPORT dol_Gui_Q_CommonDialogs* dol_Gui_Q_CommonDialogs_newInterface()
{
  auto iface =
      static_cast<dol_Gui_Q_CommonDialogs*>(interop_calloc(1, sizeof(dol_Gui_Q_CommonDialogs)));
  iface->about = CommonDialogs::about;
  iface->critical = CommonDialogs::critical;
  iface->information = CommonDialogs::information;
  iface->question = CommonDialogs::question;
  iface->warning = CommonDialogs::warning;
  iface->getColor = CommonDialogs::getColor;
  iface->getDouble = CommonDialogs::getDouble;
  iface->getInt = CommonDialogs::getInt;
  iface->getItem = CommonDialogs::getItem;
  iface->getMultiLineText = CommonDialogs::getMultiLineText;
  iface->getText = CommonDialogs::getText;
  iface->getExistingDirectory = CommonDialogs::getExistingDirectory;
  iface->getOpenFileName = CommonDialogs::getOpenFileName;
  iface->getOpenFileNames = CommonDialogs::getOpenFileNames;
  iface->getSaveFileName = CommonDialogs::getSaveFileName;

  return iface;
}
