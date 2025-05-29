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
  EXCEPTION = 100,
  SIGNAL = 200,
  CLI11_EXCEPTION = 300,
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
  using unit::TranslationUnit;

  // For now just compile all translation units, sequentially.
  for(const auto& path : t_settings.m_source_paths) {
    TranslationUnit unit{path};

    unit.execute();
  }
}

//! Log something as an exception.
template<typename T>
inline auto exception(const T t_msg) -> void
{
  using rang::fg;
  using rang::style;

  // Print lovely header.
  std::cerr << style::bold << fg::red << "Exception:\n" << style::reset;

  // Print error message.
  std::cerr << t_msg << std::endl;
}

inline auto uncaught_object() -> void
{
  using rang::fg;
  using rang::style;

  // clang-format off
  std::cerr << style::bold
						<< fg::red
						<< "Uncaught object."
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
  } catch(std::exception& e) {
    exception(e.what());

    return ExitCode::EXCEPTION;
  } catch(...) {
    uncaught_object();

    return ExitCode::EXCEPTION;
  }

  return ExitCode::OK;
}
