#ifndef QREADERAPPLICATION_H
#define QREADERAPPLICATION_H
#include "commandlinearguments.h"
#include <QGuiApplication>
#include <memory>

namespace spdlog {
class logger;
}

namespace qreader {
using LoggerPtr = std::shared_ptr<spdlog::logger>;

class QReaderApplication : public QGuiApplication
{
public:
  QReaderApplication(int& argc, char** argv, int = ApplicationFlags);

  spdlog::logger* logger() const noexcept;

private:
  void configureLogger() const;

  spdlog::logger& log();

  CommandLineArguments m_arguments;
  LoggerPtr m_logger;
};
}

#endif // QREADERAPPLICATION_H
