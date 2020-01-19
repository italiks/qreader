#ifndef COMMANDLINEARGUMENTS_H
#define COMMANDLINEARGUMENTS_H
#include <QString>
#include <QStringList>

namespace qreader {
struct CommandLineArguments
{
  QString ProgramName;
  QString Lang;
  QString Logger;
  QStringList Files;
  QStringList UnknownOptions;
};
}
#endif // COMMANDLINEARGUMENTS_H
