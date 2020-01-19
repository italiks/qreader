#include <QCoreApplication>
#include <QStringList>
#include <QtTest>

#include <commandlinearguments.h>
#include <commandlineparser.h>

#include <exception>

// add necessary includes here

enum Pair
{
  Key,
  Value
};

class CommandLineParserTest : public QObject
{
  Q_OBJECT

public:
  CommandLineParserTest();
  ~CommandLineParserTest();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void argument_parsing_test();
  void default_argument_test();
  void empty_argument_test();

private:
  qreader::CommandLineParser m_parser;
};

CommandLineParserTest::CommandLineParserTest() {}

CommandLineParserTest::~CommandLineParserTest() {}

void
CommandLineParserTest::initTestCase()
{
  m_parser = {};
}

void
CommandLineParserTest::cleanupTestCase()
{}

void
CommandLineParserTest::argument_parsing_test()
{
  QStringList arguments{ "test_case1" };
  const QStringList files{ { "test_file0", "test_file1", "test_file2" } };
  const QStringList loggerOption{ { "--log", "debug" } };
  const QStringList langOption{ { "--lang", "en" } };
  const QStringList unknownOptions{ { "-q", "--wer" } };

  arguments.append(files);
  arguments.append(loggerOption);
  arguments.append(langOption);
  arguments.append(unknownOptions);

  qreader::CommandLineArguments parsedArguments = m_parser.parse(arguments);

  QCOMPARE(parsedArguments.ProgramName, "test_case1");
  QCOMPARE(parsedArguments.UnknownOptions.size(), unknownOptions.size());
  QCOMPARE(parsedArguments.Files, files);
  QCOMPARE(parsedArguments.Logger, loggerOption[Pair::Value]);
  QCOMPARE(parsedArguments.Lang, langOption[Pair::Value]);
}

void
CommandLineParserTest::default_argument_test()
{
  QStringList arguments{ "test_case2" };
  const QString defaultLogger{ "debug" };
  const QString defaultLang{ "en" };

  qreader::CommandLineArguments parsedArguments = m_parser.parse(arguments);

  QCOMPARE(parsedArguments.ProgramName, "test_case2");
  QCOMPARE(parsedArguments.Logger, defaultLogger);
  QCOMPARE(parsedArguments.Lang, defaultLang);
}

void
CommandLineParserTest::empty_argument_test()
{
  QVERIFY_EXCEPTION_THROWN(m_parser.parse({}), std::out_of_range);
}

QTEST_MAIN(CommandLineParserTest)

#include "tst_commandlineparser.moc"
