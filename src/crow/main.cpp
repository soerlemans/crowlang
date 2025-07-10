// STL Includes:
#include <fstream>

// Library Includes:
#include <cpptrace/cpptrace.hpp>

// Absolute Includes:
#include "crow/debug/log.hpp"
#include "crow/settings/settings.hpp"
#include "crow/unit/translation_unit.hpp"

// Enums:
enum ExitCode {
  OK = 0,
  IMPROPER_USAGE,

  DIAGNOSTIC_ERROR = 100,
  STDEXCEPT_EXCEPTION = 200,
  STL_EXCEPTION = 300,

  SIGNAL = 400,
  CLI11_EXCEPTION = 500,

  UNCAUGHT_OBJECT = 600
};

//! Do not absorb cpptrace errors on debug builds.
static auto disable_absorb_exceptions() -> void
{
#ifdef DEBUG
  // Do not absorb cpptrace errors on debug build.
  cpptrace::absorb_trace_exceptions(false);
#endif
}

static auto run(settings::Settings t_settings) -> void
{
  using unit::BuildUnit;
  using unit::BuildUnitParams;
  using unit::make_build_unit;
  using unit::TranslationUnit;

  // Init build unit.
  BuildUnitParams params{
    t_settings.m_backend, t_settings.m_interop_backends, {}};
  auto build_unit_ptr{make_build_unit(params)};

  // For now just compile all translation units, sequentially.
  for(const auto& path : t_settings.m_source_paths) {
    TranslationUnit unit{build_unit_ptr, path};

    unit.execute();
  }
}

template<typename T>
  requires std::is_base_of<DiagnosticError, T>::value
inline auto report_error(const T t_err) -> void
{
  using rang::fg;
  using rang::style;

  // Print lovely header.
  std::cerr << style::bold << fg::red;
  std::cerr << "Error:\n" << style::reset;

  // Print error message.
  const std::string_view msg{t_err.what()};
  std::cerr << msg << std::endl;
}

//! Log an stdexcept::exception.
template<typename T>
  requires std::is_base_of<lib::stdexcept::Exception, T>::value
inline auto report_stdexcept(const T t_exception) -> void
{
  using rang::fg;
  using rang::style;

  // Print lovely header.
  std::cerr << style::bold << fg::red;
  std::cerr << "Exception:\n" << style::reset;

  // Print error message.
  const std::string_view msg{t_exception.what()};
  std::cerr << msg << std::endl;
}

//! Log an exception.
template<typename T>
  requires std::is_base_of<std::exception, T>::value
inline auto report_exception(const T t_exception) -> void
{
  using rang::fg;
  using rang::style;

  // Print lovely header.
  std::cerr << style::bold << fg::red;
  std::cerr << "Exception:\n" << style::reset;

  // Print error message.
  const std::string_view msg{t_exception.what()};
  std::cerr << msg << std::endl;
}

inline auto report_uncaught_object() -> void
{
  using rang::fg;
  using rang::style;

  // clang-format off
  std::cerr << style::bold
						<< fg::red
						<< "Unsupported thrown object was caught."
            << style::reset
						<< std::endl;
  // clang-format on
}

// Main:
auto main(const int t_argc, char* t_argv[]) -> int
{
  using settings::CliParams;
  using settings::get_settings;

  // Cli parameters clumped together for later CLI11 parsing.
  CliParams cli_params{
    CLI::App{"Compiler for Crow(lang)", "crow"},
    t_argc, t_argv
  };

  try {
    using debug::LogLevel;
    using debug::set_loglevel;

    disable_absorb_exceptions();

    // Reading of settings happens before setting the loglevel.
    // So for now we should set it to verbose so we can log config reading.
    set_loglevel(LogLevel::VERBOSE);

    // Retrieve settings (CLI/TOML).
    // CliParams cli_params{&app, t_argc, t_argv};
    auto settings{get_settings(cli_params)};
    set_loglevel(settings.m_level);

    run(settings);
  } catch(CLI::ParseError& e) {
    const auto exit_code{cli_params.m_app.exit(e)};
    std::cerr << std::format("CLI11 exit code: {}\n", exit_code);

    return ExitCode::CLI11_EXCEPTION;
  } catch(diagnostic::DiagnosticError& e) {
    report_error(err);

    return ExitCode::DIAGNOSTIC_ERROR;
  } catch(lib::stdexcept::Exception& except) {
    report_stdexcept(e.what());

    return ExitCode::STDEXCEPT_EXCEPTION;
  } catch(std::exception& except) {
    report_exception(except.what());

    return ExitCode::STL_EXCEPTION;
  } catch(...) {
    report_uncaught_object();

    return ExitCode::report_UNCAUGHT_OBJECT;
  }

  return ExitCode::OK;
}
