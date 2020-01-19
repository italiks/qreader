#include "commandlineparser.h"
#include <QCommandLineParser>
#include <QCoreApplication>

#include <exception>

namespace qreader {
using app = QCoreApplication;

CommandLineParser::CommandLineParser() {}

CommandLineArguments
CommandLineParser::parse(const QStringList& argumentList) const
{
  if (argumentList.empty()) {
    throw std::out_of_range{ "empty argument list was passed to parser" };
  }

  CommandLineArguments arguments;
  arguments.ProgramName = argumentList[0];

  QCommandLineParser parser;
  parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
  parser.setApplicationDescription(
    app::translate("CommandLineParser", "QReader command line arguments"));

  parser.addPositionalArgument(
    "files",
    app ::translate("CommandLineParser", "Files to be opened"),
    "[files...]");

  const auto help = parser.addHelpOption();
  const QCommandLineOption log{ "log",
                                app::translate("CommandLineParser",
                                               "Logger type"),
                                app::translate("CoomandLineParser", "logger"),
                                "debug" };
  const QCommandLineOption lang{ "lang",
                                 app::translate("CommandLineParser",
                                                "UI language"),
                                 app::translate("CommandLineParser", "lang"),
                                 "en" };

  parser.addOption(log);
  parser.addOption(lang);

  const auto success = parser.parse(argumentList);
  if (!success) {
    arguments.UnknownOptions = parser.unknownOptionNames();
  }

  arguments.Files = parser.positionalArguments();
  arguments.Lang = parser.value(lang);
  arguments.Logger = parser.value(log);
  return arguments;
}
}
