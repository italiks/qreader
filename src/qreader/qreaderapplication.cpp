#include "qreaderapplication.h"
#include "commandlineparser.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

#include "spdlog/fmt/fmt.h"

template<>
struct fmt::formatter<QString>
{
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const QString& str, FormatContext& ctx)
  {
    return format_to(ctx.out(), "{}", str.toStdString());
  }
};

template<>
struct fmt::formatter<QStringList>
{
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const QStringList& list, FormatContext& ctx)
  {
    auto it = ctx.out();
    if (list.empty()) {
      return format_to(it, "[]");
    }

    it = format_to(it, "[");

    for (const auto& str : list) {
      format_to(it, "\n{},", str);
    }

    it = format_to(it, "\n]");
    return it;
  }
};

template<>
struct fmt::formatter<qreader::CommandLineArguments>
{
  constexpr auto parse(format_parse_context& ctx) { return ctx.begin(); }

  template<typename FormatContext>
  auto format(const qreader::CommandLineArguments& args, FormatContext& ctx)
  {
    return format_to(ctx.out(),
                     "{{ \nProgram: {}\nLogger: {}\nLang: {}\nInput "
                     "files: {}\nUnknown options: {}}}",
                     args.ProgramName,
                     args.Logger,
                     args.Lang,
                     args.Files,
                     args.UnknownOptions);
  }
};

namespace qreader {

void
QReaderApplication::configureLogger() const
{
  spdlog::set_default_logger(m_logger);
  spdlog::set_level(spdlog::level::trace);
  spdlog::set_pattern("[%H:%M:%S %z] [%n] [thread %t] [%^---%l---%$]: %v");
}

QReaderApplication::QReaderApplication(int& argc, char** argv, int)
  : QGuiApplication(argc, argv)
  , m_arguments{ CommandLineParser::Parse(arguments()) }
{
  m_logger = spdlog::stdout_color_mt("main.console.log");
  assert(m_logger);
  configureLogger();

  log().debug("Input arguments: {}", m_arguments);
}

spdlog::logger*
QReaderApplication::logger() const noexcept
{
  return m_logger.get();
}

spdlog::logger&
qreader::QReaderApplication::log()
{
  return *m_logger;
}

}
