#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H
#include "commandlinearguments.h"
#include <QStringList>

namespace qreader {
class CommandLineParser
{
public:
  CommandLineParser();

  CommandLineArguments parse(const QStringList& argumentList) const;
};
}

#endif // COMMANDLINEPARSER_H
