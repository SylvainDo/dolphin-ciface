#pragma once

#include <string>

#include <QString>

namespace PluginUtil
{

char* dupStdString(const std::string& src);
char* dupQString(const QString& str);
QString toQString(const char* str);

}
